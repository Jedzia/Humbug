#ifndef HUMBUGSHARED_VFS_ZFSYSTEM_H
#define HUMBUGSHARED_VFS_ZFSYSTEM_H
// zfsystem.h: interface for the zip file system classes.
//
//////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2004 Tanguy Fautré.
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source distribution.
//
//  Tanguy Fautré
//  softdev@telenet.be
//
//////////////////////////////////////////////////////////////////////
//
//							Zip File System.
//							****************
//
// Current version: 1.00 BETA 2 (16/07/2004)
//
// Comment: -
//
// History: - 1.00 BETA 2 (16/07/2004) - Updated to follow latest version
//                                       of fileio.h
//          - 1.00 BETA 1 (21/07/2002) - First public release
//
//////////////////////////////////////////////////////////////////////



#include <map>
#include <string>
#include <vector>

#include "ziphdr.h"		// Zip file header
#include "zstream.h"	// Zip Stream



// Zip File System Namespace
namespace zip_file_system {




class filesystem;



// Input Zip File class
class izfstream : public izstream
{
public:
	izfstream(const filesystem * pFS = pDefaultFS);
	izfstream(const char * FilePath, const filesystem * pFS = pDefaultFS);

	void open(const char * FilePath);
	void close();

	bool is_open() const;

	bool Zipped() const;
	const std::string & FilePath() const;
	const std::string & FullFilePath() const;

protected:
	friend class filesystem;

	// Default File System Pointer (default = NULL)
	static const filesystem * pDefaultFS;

	std::string m_FilePath;
	std::string m_FullFilePath;
	const filesystem * m_pFS;
	bool m_Zipped;
};




// Zip File System central class
class filesystem  
{
public:
	filesystem(const char * BasePath = "", const char * FileExt = "zip", bool DefaultFS = true); 
	~filesystem();

	void MakeDefault() const;
	void Open(izfstream & File, const char * Filename) const;
	int FileSize(const char * Filename) const;

	friend std::ostream & operator << (std::ostream & Out, const filesystem & FS);

protected:

	// Zip file info class
	class zipfile_info
	{
	public:
		zipfile_info() : m_NbEntries(0), m_FilesSize(0), m_FilesCompSize(0) { }

		std::string	m_Filename;
		size_t		m_NbEntries;
		size_t		m_FilesSize;
		size_t		m_FilesCompSize;
	};


	// "local" file info class
	class file_info
	{
	public:
		file_info() : m_PackID(0), m_Offset(0), m_Size(0), m_CompSize(0), m_CompMethod(0), m_Directory(true) { }
		file_info(size_t PackID, size_t Offset, size_t Size, size_t CompSize, short CompMethod, bool Directory) :
			m_PackID(PackID), m_Offset(Offset), m_Size(Size), m_CompSize(CompSize), m_CompMethod(CompMethod), m_Directory(Directory) { }

		size_t	m_PackID;
		size_t	m_Offset;
		size_t	m_Size;
		size_t	m_CompSize;
		short	m_CompMethod;
		bool	m_Directory;
	};


	// Class for file path string comparaison
	struct lt_path
	{
		bool operator() (const std::string & s1, const std::string & s2) const;
	};


	// Protected member functions
	// Zip file format related functions
	std::streamoff CentralDir(std::istream & File) const;
	std::streamoff SkipLFHdr(std::istream & File, std::streamoff LFHdrPos) const;
	headerid NextHeader(std::istream & File) const;

	// File/Zip map related functions
	bool FileNotZipped(const char * FilePath) const;
	bool FindFile(const char * Filename, file_info * FileInfo) const;
	const std::string & FindZip(size_t PackID) const;
	void InsertZip(const char * Filename, const size_t PackID);

	// New type definitions
	typedef std::map<size_t, zipfile_info>								zipmap;
	typedef std::map<size_t, zipfile_info>::iterator					zipmap_iterator;
	typedef std::map<size_t, zipfile_info>::const_iterator				zipmap_const_iterator;
	typedef std::map<std::string, file_info, lt_path>					filemap;
	typedef std::map<std::string, file_info, lt_path>::iterator			filemap_iterator;
	typedef std::map<std::string, file_info, lt_path>::const_iterator	filemap_const_iterator;

	// Mighty protected member variables
	std::string	m_BasePath;
	std::string	m_FileExt;
	zipmap		m_Zips;
	filemap		m_Files;
};




//////////////////////////////////////////////////////////////////////
// zip_file_system::izfile Inline Functions
//////////////////////////////////////////////////////////////////////

inline izfstream::izfstream(const filesystem * pFS) : m_pFS(pFS) { }

inline izfstream::izfstream(const char * FilePath, const filesystem * pFS) : m_pFS(pFS) {
	open(FilePath);
}

inline void izfstream::open(const char * FilePath) {
	if (m_pFS != NULL)
		m_pFS->Open(* this, FilePath);
}

inline void izfstream::close() {
	izstream::close();
	m_FilePath = m_FullFilePath = "";
}

inline bool izfstream::is_open() const {
	return static_cast<zbuffer *>(rdbuf())->is_open();
}

inline bool izfstream::Zipped() const {
	return m_Zipped;
}

inline const std::string & izfstream::FilePath() const {
	return m_FilePath;
}

inline const std::string & izfstream::FullFilePath() const {
	return m_FullFilePath;
}



//////////////////////////////////////////////////////////////////////
// zip_file_system::filesystem Inline Functions
//////////////////////////////////////////////////////////////////////

inline filesystem::~filesystem() {
	// Security mesure with izfile::pDefaultFS
	if (izfstream::pDefaultFS == this)
		izfstream::pDefaultFS = NULL;
}

inline void filesystem::MakeDefault() const {
	izfstream::pDefaultFS = this;
}




}	// namespace zip_file_system

#endif // HUMBUGSHARED_VFS_ZFSYSTEM_H guard
