// zfsystem.cpp: implementation of the zip file system classes.
//
// Copyright (C) 2004 Tanguy Fautr�.
// For conditions of distribution and use,
// see copyright notice in zfsystem.h
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "zfsystem.h"

#include "fileio.h"		// I/O facilities



namespace zip_file_system {

using namespace std;




//////////////////////////////////////////////////////////////////////
// Static variables initialization
//////////////////////////////////////////////////////////////////////

const filesystem * izfstream::pDefaultFS = NULL;



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

filesystem::filesystem(const char * BasePath, const char * FileExt, bool DefaultFS)
	: m_BasePath(BasePath), m_FileExt(FileExt)
{
	using io_facilities::search_iterator;

	// Init m_BasePath and be sure the base path finish with a '/' or a '\'
	if (! m_BasePath.empty()) {
		string::iterator c = --(m_BasePath.end());
		if ((*c != '/') && (*c != '\\'))
			m_BasePath += '/';
	}

	// Search all *.zip files (or whatever the ZipExt specify as the file extension)
	vector<string> ZipFiles;

	for (search_iterator ZSrch = (m_BasePath + "*." + m_FileExt).c_str(); ZSrch != ZSrch.end(); ++ZSrch)
		ZipFiles.push_back(ZSrch.Name());

	// Open each zip files that have been found, in alphabetic order
	sort(ZipFiles.begin(), ZipFiles.end());

	for (vector<string>::const_iterator ZipIt = ZipFiles.begin(); ZipIt != ZipFiles.end(); ++ZipIt)
		InsertZip(ZipIt->c_str(), ZipIt - ZipFiles.begin());

	// Should we make this the default File System for ifile?
	if (DefaultFS)
		MakeDefault();
}



//////////////////////////////////////////////////////////////////////
// File System Member Functions
//////////////////////////////////////////////////////////////////////

void filesystem::Open(izfstream & File, const char * Filename) const
{
	// Close the file if it was opened;
	File.close();

	// Generate the path and see if the file is zipped or not
	string FullPath = m_BasePath + Filename;

	// File is not zipped
	if (FileNotZipped(FullPath.c_str())) {

		// Link the izfile object with an opened filebuf
		filebuf * FileBuf = new filebuf;
		FileBuf->open(FullPath.c_str(), ios::binary | ios::in);

		if (FileBuf->is_open()) {
			delete File.rdbuf(FileBuf);
			File.clear(ios::goodbit);
			File.m_FilePath = Filename;
			File.m_FullFilePath = FullPath;
			File.m_Zipped = false;
		}

	// File is maybe zipped
	} else {

		file_info FileInfo;
		string ZipPath;

		// Check whether the file is zipped, whether the file is a directory and try to open.
		if (FindFile(Filename, &FileInfo) && (! FileInfo.m_Directory) && (! ((ZipPath = FindZip(FileInfo.m_PackID)).empty()))) {

			// Get the position of the compressed data
			ifstream ZipFile ((m_BasePath + ZipPath).c_str(), ios::binary);
			if (ZipFile) {
				streamoff DataPos = SkipLFHdr(ZipFile, streamoff(FileInfo.m_Offset));
				ZipFile.close();

				if (DataPos != streamoff(-1)) {

					// Open the file at the right position
					const std::string ZipFilePath = m_BasePath + ZipPath;
					((izstream &) File).open(
						ZipFilePath.c_str(),
						streamoff(DataPos),
						streamoff(FileInfo.m_CompSize),
						FileInfo.m_CompMethod
					);

					if (File) {
						File.m_FilePath = Filename;
						File.m_FullFilePath = FullPath;
						File.m_Zipped = true;
					}
				}
			}
		}
	}
}



//////////////////////////////////////////////////////////////////////
// File System Protected Member Functions
//////////////////////////////////////////////////////////////////////

bool filesystem::FileNotZipped(const char * FilePath) const
{
	//return io_facilities::search_iterator(FilePath);
	// follow new search_iterator implementation
	std::ifstream File(FilePath);

	if (! File)
		return false;

	return true;
}



bool filesystem::FindFile(const char * Filename, file_info * FileInfo) const
{
	filemap_const_iterator It = m_Files.find(Filename);

	if (It == m_Files.end())
		return false;	// File not found

	* FileInfo = (* It).second;
	return true;
}



const string & filesystem::FindZip(size_t PackID) const
{
	static const string EmptyString;

	zipmap_const_iterator It = m_Zips.find(PackID);

	if (It  == m_Zips.end())
		return EmptyString;	// PackID not valid

	return (* It).second.m_Filename;
}



void filesystem::InsertZip(const char * Filename, const size_t PackID)
{
	zipfile_info ZipInfo;

	// Get full path to the zip file and prepare ZipInfo
	ZipInfo.m_Filename = Filename;
	string ZipPath = m_BasePath + Filename;

	// Open zip
	ifstream File(ZipPath.c_str(), ios::binary);

	if (! File)
		return;

	// Find the start of the central directory
	if (! File.seekg(CentralDir(File))) return;

	// Check every headers within the zip file
	file_header FileHdr;

	while ((NextHeader(File) == FILE) && (FileHdr.ReadHeader(File))) {

		// Include files into Files map
		const char * Name = &(* FileHdr.m_Filename.begin());
		const unsigned short i = FileHdr.m_FilenameSize - 1;
		if (FileHdr.m_FilenameSize != 0) {

			m_Files[Name] = file_info(
				PackID,									// Package ID
				FileHdr.m_RelOffset,					// "Local File" header offset position
				FileHdr.m_UncompSize,					// File Size
				FileHdr.m_CompSize,						// Compressed File Size
				FileHdr.m_CompMethod,					// Compression Method;
				((Name[i] == '/') || (Name[i] == '\\'))	// Is a directory?
			);

			++(ZipInfo.m_NbEntries);
			ZipInfo.m_FilesSize += FileHdr.m_UncompSize;
			ZipInfo.m_FilesCompSize += FileHdr.m_CompSize;
		}
	}

	File.close();

	// Add zip file to Zips data base (only if not empty)
	if (ZipInfo.m_NbEntries != 0)
		m_Zips[PackID] = ZipInfo;
}



//////////////////////////////////////////////////////////////////////
// File System Friend Functions
//////////////////////////////////////////////////////////////////////

ostream & operator << (ostream & Out, const filesystem & FS)
{
	size_t NbFiles = 0;
	filesystem::zipfile_info AllZipsInfo;

	for (filesystem::zipmap_const_iterator It = FS.m_Zips.begin(); It != FS.m_Zips.end(); ++It) {

		const filesystem::zipfile_info & ZInfo = (* It).second;

		// Print zip filename
		Out << setiosflags(ios::left) << setw(32) << "-> \"" + ZInfo.m_Filename + "\"" << resetiosflags(ios::left);
		// Print number of entries found in this zip file
		Out << "  " << setw(5) << ZInfo.m_NbEntries << " files";
		// Print the uncompressed size of all included files
		Out << "  " << setw(7) << ZInfo.m_FilesSize / 1024 << " KB";
		// Print the compressed size of all these files
		Out << "  " << setw(7) << ZInfo.m_FilesCompSize / 1024 << " KB packed" << endl;

		++NbFiles;
		AllZipsInfo.m_NbEntries += ZInfo.m_NbEntries;
		AllZipsInfo.m_FilesSize += ZInfo.m_FilesSize;
		AllZipsInfo.m_FilesCompSize += ZInfo.m_FilesCompSize;
	}

	// Print the general info
	Out << "\nTotal:  ";
	Out << NbFiles << " packs   ";
	Out << AllZipsInfo.m_NbEntries << " files   ";
	Out << float(AllZipsInfo.m_FilesSize) / (1024 * 1024) << " MB   ";
	Out << float(AllZipsInfo.m_FilesCompSize) / (1024 * 1024) << " MB packed." << endl;

	return Out;
}



//////////////////////////////////////////////////////////////////////
// "Less Than" Comparaison lt_path_str Member Functions
//////////////////////////////////////////////////////////////////////

bool filesystem::lt_path::operator () (const string & s1, const  string & s2) const
{
	const char * A = s1.c_str();
	const char * B = s2.c_str();

	for (size_t i = 0; ; ++i) {

		if ((A[i] == '\0') && (B[i] == '\0'))
			return false;

		// case insensitive and '/' is the same as '\'
		if (! (
				(A[i] == B[i] + ('a' - 'A'))		||
				(A[i] == B[i] - ('a' - 'A'))		||
				(A[i] == B[i])						||
				((A[i] == '\\') && (B[i] == '/'))	||
				((A[i] == '/') && (B[i] == '\\'))
			)) {

			if ((A[i] == '\0') || (A[i] < B[i]))
				return true;
			else
				return false;
		}
	}
}



//////////////////////////////////////////////////////////////////////
// Zip Header Classes Related Member Functions
//////////////////////////////////////////////////////////////////////

streamoff filesystem::CentralDir(istream & File) const
{
	using io_facilities::readvar;

	// Look for the "end of central dir" header. Start minimum 22 bytes before end.
	if (! File.seekg(-22, ios::end)) return -1;

	streamoff EndPos;
	streamoff StartPos = File.tellg();

	if (StartPos == streamoff(0)) return -1;

	if (StartPos <= streamoff(65536))
		EndPos = 1;
	else
		EndPos = StartPos - streamoff(65536);

	// Start the scan
	do {
		unsigned int RawSignature;

		if (! readvar(File, RawSignature, 4)) return -1;

		eofcd_header Header;
		streampos Pos = File.tellg();

		// Found a potential "eofcd" header?
		if ((RawSignature == ENDOFDIR) && (File.seekg(-4, ios::cur)) && (Header.ReadHeader(File))) {

			// Check invariant values (1 disk only)
			if ((Header.m_NbDisks == 0) && (0 == Header.m_DirDisk) && (Header.m_LocalEntries == Header.m_TotalEntries)) {

				// Check comment ends at eof
				if (! File.seekg(-1, ios::end)) return -1;
				if ((File.tellg() + streamoff(1)) == (Pos + streamoff(Header.m_CommentSize + 22 - 4))) {

					// Check the start offset leads to a correct directory/file header;
					if (! File.seekg(Header.m_Offset)) return -1;
					if (! readvar(File, RawSignature, 4)) return -1;
					if (RawSignature == FILE)
						return Header.m_Offset;
				}
			}
		}

		File.seekg(Pos);

	} while ((File.seekg(-5, ios::cur)) && (File.tellg() > EndPos));

    return -1;
}



streamoff filesystem::SkipLFHdr(istream & File, streamoff LFHdrPos) const
{
	using io_facilities::readvar;

	unsigned short NameSize;
	unsigned short FieldSize;
	unsigned int RawSignature;

	// verify it's a local header
	if (! File.seekg(LFHdrPos)) return -1;
	if (! readvar(File, RawSignature, 4)) return -1;
	if (RawSignature != LOCALFILE) return -1;

	// Skip and go directly to comment/field size
	if (! File.seekg(22, ios::cur)) return -1;
	if (! readvar(File, NameSize, 2)) return -1;
	if (! readvar(File, FieldSize, 2)) return -1;

	// Skip comment and extra field
	if (! File.seekg(NameSize + FieldSize, ios::cur)) return -1;

	// Now we are at the compressed data position
	return (File.tellg());
}



headerid filesystem::NextHeader(istream & File) const
{
	using io_facilities::readvar;

	unsigned int RawSignature;

	if (! readvar(File, RawSignature, 4))
		return READERROR;

	if (! File.seekg(-4, ios::cur))
		return READERROR;

	headerid Signature = headerid(RawSignature);

	switch (Signature) {
	case FILE:
	case LOCALFILE:
	case ENDOFDIR:
		return Signature;
	default:
		return UNKNOWN;
	}
}




} // namespace zip_file_system
