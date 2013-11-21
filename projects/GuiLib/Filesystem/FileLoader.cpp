#include "../stdafx.h"
#include "FileLoader.h"
#include <HumbugLib/LogManager.h>
#include <HumbugShared/VFS/zfsystem.h>
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"

using zip_file_system::filesystem;
using zip_file_system::izfstream;


// FileLoadingInfo

FileLoadingInfo::FileLoadingInfo(const std::string name, SDL_Surface* surface)
: m_strName(name), m_pSurface(surface), m_pFont(NULL), m_pArea(NULL), m_pData(NULL), m_fsize(0), m_refcount(0)
{
	LOGSTREAM << "FileLoadingInfo create SDL_Surface '" << *this << "'";
}

FileLoadingInfo::FileLoadingInfo( const std::string name, TTF_Font* font, SDL_RWops* area, char *data, int fsize )
: m_strName(name), m_pSurface(NULL), m_pFont(font), m_pArea(area), m_pData(data), m_fsize(fsize), m_refcount(0)
{
	LOGSTREAM << "FileLoadingInfo create Memdata '" << *this << "'";
}

FileLoadingInfo::FileLoadingInfo( const std::string name, char *data, int fsize )
: m_strName(name), m_pSurface(NULL), m_pFont(NULL), m_pArea(NULL), m_pData(data), m_fsize(fsize), m_refcount(0)
{
	LOGSTREAM << "FileLoadingInfo create Memdata '" << *this << "'";
}

FileLoadingInfo::~FileLoadingInfo()
{
    LOGSTREAM << "FileLoadingInfo freeing '" << *this << "'";
    if(m_pSurface)
    {
	    SDL_FreeSurface(m_pSurface);
        m_pSurface = NULL;
    }
    else if(m_pFont)
    {
	    TTF_CloseFont( m_pFont );
        m_pFont = NULL;
        //SDL_FreeRW(m_pArea);
        //m_pArea = NULL;
        delete[] m_pData;
        m_pData = NULL;
    }
	else if(m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}

}

FileLoadingInfo& FileLoadingInfo::operator++( int )
{
	m_refcount++;
	return *this;
}

FileLoadingInfo& FileLoadingInfo::operator--( int )
{
	m_refcount--;
	return *this;
}

std::ostream& operator<<( std::ostream& o, const FileLoadingInfo& r )
{
	return o << "FileLoadingInfo[ (" << r.Refcount() << ")Name='" << r.Name() << "', Loc=" << r.Loc()
		<< ", Font=" << r.Font() << ", rWops=" << r.m_pArea
		<<
		" ]";
}

// FileLoader

struct FileLoader::FileLoaderImpl {

#   define FILELOADER_ERRNO    errno

    void slurp(std::string& data, const std::string& filename, bool is_binary = false)
    {
        //std::ios_base::openmode openmode = ios::ate | ios::in;
        //if (is_binary)
        //    openmode |= ios::binary;
        //ifstream file(filename.c_str(), openmode);
        izfstream file(filename.c_str());

        if (! file)
            LOGSTREAM << "ERROR: Cannot open file!";
        else
        {

            std::string contents((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
            data = contents;
        }

        file.close();
    }

    void slurp2(std::string& data, const std::string& filename, bool is_binary = false)
    {
        //std::ios_base::openmode openmode = ios::ate | ios::in;
        //if (is_binary)
        //    openmode |= ios::binary;
        //ifstream file(filename.c_str(), openmode);
        izfstream file(filename.c_str());

        if (! file)
            LOGSTREAM << "ERROR: Cannot open file!";
        else
        {

            data.clear();
            data.reserve(file.tellg());
            file.seekg(0, std::ios::beg);
            data.append(std::istreambuf_iterator<char>(file.rdbuf()),
                std::istreambuf_iterator<char>());
        }

        file.close();
    }

    char* data;
    SDL_RWops* LoadData(const filesystem& fsys, const std::string& filename, int& bufsize)
    {
        data = NULL;
		izfstream file(filename.c_str());
		bufsize = PrepareRead(fsys, filename, file);
        //std::vector<char> data;
        SDL_RWops* imgmem = NULL;
        SDL_Surface *sdlsurface=NULL;

        if (! file)
        {
            //std::cerr << "[FileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened.";
			LOGSTREAM << "ERROR: Can't load:" + filename;

			// Todo: does not show filename with the exception.
            HUMBUG_FILELOADER_THROW(
                FileLoaderException("[FileLoader::LoadImg-slurp5]", filename,
                boost::system::error_code(FILELOADER_ERRNO, boost::system::system_category())));
            return NULL;
        }
        else
        {
            //data.clear();
            //data.resize(fsize);
            data = new char[bufsize];
            file.read(&data[0], bufsize);
	        imgmem = SDL_RWFromMem(&data[0], bufsize);

            //sdlsurface = IMG_Load_RW(imgmem, 1);
        }

        file.close();
        return imgmem;
    }

	int PrepareRead( const filesystem &fsys, const std::string &filename, izfstream &file ) 
	{
		int bufsize;
		//std::string xxx = file.FullFilePath();
		if(file.Zipped())
		{
			// File is in ZIP, get size.
			bufsize = fsys.FileSize(filename.c_str());
		}
		else
		{
			// File is on disc, get size.
			file.seekg (0, file.end);
			bufsize = file.tellg();		
			file.seekg (0, file.beg);
		}
		return bufsize;
	}

	char* LoadChar(const filesystem& fsys, const std::string& filename, int& bufsize)
	{
		izfstream file(filename.c_str());
		bufsize = PrepareRead(fsys, filename, file);

		char* data = NULL;
		if (! file)
		{
			//std::cerr << "[FileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened.";
			LOGSTREAM << "ERROR: Can't load:" + filename;

			// Todo: does not show filename with the exception.
			HUMBUG_FILELOADER_THROW(
				FileLoaderException("[FileLoader::LoadChar]", filename,
				boost::system::error_code(FILELOADER_ERRNO, boost::system::system_category())));
			return NULL;
		}
		else
		{
			data = new char[bufsize];
			file.read(&data[0], bufsize);
		}

		file.close();
		return data;
	}

    SDL_Surface* LoadImg(const filesystem& fsys, const std::string& filename)
    {
        //std::vector<char> data;
        SDL_Surface* sdlsurface;
		int bufsize;
        SDL_RWops* imgmem = LoadData(fsys, filename, bufsize);

        if (! imgmem)
        {
            //std::cerr << "[FileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUG_FILELOADER_THROW(
                FileLoaderException("[FileLoader::LoadImg-imgmem]", filename,
                boost::system::error_code(FILELOADER_ERRNO, boost::system::system_category())));
            return NULL;
        }
        else
        {
            //data.clear();
            //data.resize(fsize);
            //SDL_LoadBMP_RW(imgmem, 1);
	            sdlsurface = IMG_Load_RW(imgmem, 1);
            //SDL_FreeRW(imgmem);
            delete[] data;
            if (!sdlsurface) {
                //fprintf(stderr, "Error: '%s' could not be opened: %s\n", filename.c_str(), IMG_GetError());
                // load a internal error image.
					char *imgMsg = IMG_GetError();

                HUMBUG_FILELOADER_THROW(
                    FileLoaderException(std::string("[FileLoader::LoadImg-sdlsurface]: '" ) + filename + "' " + imgMsg, 1));
                // generic_category
            }
        }

        return sdlsurface;
    }

    FileLoadingInfo* LoadFont(const filesystem& fsys, const std::string & filename, int ptsize )
    {
        //std::vector<char> data;
        TTF_Font* font;
		int bufsize;
        SDL_RWops* imgmem = LoadData(fsys, filename, bufsize);
        FileLoadingInfo *flinfo = NULL;

        if (! imgmem)
        {
            //std::cerr << "[FileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUG_FILELOADER_THROW(
                FileLoaderException("[FileLoader::LoadFont]", filename,
                boost::system::error_code(FILELOADER_ERRNO, boost::system::system_category())));
            return NULL;
        }
        else
        {
            //data.clear();
            //data.resize(fsize);
	            font = TTF_OpenFontRW(imgmem, 1, ptsize);
            flinfo = new FileLoadingInfo(filename, font, imgmem, data, bufsize);
            //SDL_FreeRW(imgmem);
            //delete[] data;
            if (!font) {
                //fprintf(stderr, "Error: '%s' could not be opened: %s\n", filename.c_str(), IMG_GetError());
                // load a internal error image.
				HUMBUG_FILELOADER_THROW(
	                    FileLoaderException(std::string("[FileLoader::LoadFont]: '" ) + filename + "' " + TTF_GetError(), 1));
                // generic_category
            }

        }

        return flinfo;

    };

    SDL_Surface* LoadImgXX(const filesystem& fsys, const std::string& filename)
    {
		izfstream file(filename.c_str());
		int fsize = PrepareRead(fsys, filename, file);
        //std::vector<char> data;
        SDL_Surface* sdlsurface;

        if (! file)
        {
            //std::cerr << "[FileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUG_FILELOADER_THROW(
                FileLoaderException("[FileLoader::LoadImg-slurp5]", filename,
                boost::system::error_code(FILELOADER_ERRNO, boost::system::system_category())));
            return NULL;
        }
        else
        {
            //data.clear();
            //data.resize(fsize);
            char* data = new char[fsize];
            file.read(&data[0], fsize);

	            SDL_RWops* imgmem = SDL_RWFromMem(&data[0], fsize);
	            sdlsurface = IMG_Load_RW(imgmem, 1);
            delete[] data;
            if (!sdlsurface) {
                //fprintf(stderr, "Error: '%s' could not be opened: %s\n", filename.c_str(), IMG_GetError());
                // load a internal error image.
	                HUMBUG_FILELOADER_THROW(
	                    FileLoaderException(std::string("[FileLoader::LoadImg-slurp5]: '" ) + filename + "' " + IMG_GetError(), 1));

                // generic_category
            }
        }

        file.close();
        return sdlsurface;
    }


};

FileLoader::FileLoader(const std::string & basepath)
: pimpl_(new FileLoader::FileLoaderImpl), m_pBasepath(basepath), m_pLastLoaded("")
{
	 using namespace humbuglib;
     dbgOut(__FUNCTION__);
	 LogManager::getSingleton().logMessage("Creating FileLoader for '" + basepath + "'.");
	 LogManager::getSingleton().stream() << "Logging from Stream.";
}

FileLoader::~FileLoader(void)
{
    //m_pvSurfaces.release();
	m_resMap.release();
    dbgOut(__FUNCTION__);
	humbuglib::LogManager::getSingleton().stream() << __FUNCTION__ << " Logging from Stream.";

}

const char* FileLoader::language(int x) const
{
    return "AsciiDoc";
}

std::string FileLoader::LoadAsString(const std::string & filename, std::string location) 
{
	std::string tmp;
	boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs1 = m_resMap.find(filename);
	if (rexs1 != m_resMap.end())
	{
		FileLoadingInfo& finf = *(rexs1->second);
		LOGSTREAM << "FileLoader LoadAsString in Cache '" << filename << "': " << location;
		finf++;
		return std::string(finf.m_pData, finf.m_fsize);
	}
	else
		LOGSTREAM << "FileLoader LoadAsString '" << filename << "' " << location;

	filesystem fsys(m_pBasepath.c_str(), "zip", true);
	LOGSTREAM << fsys;

	// Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)


	m_pLastLoaded = filename;
	int bufsize;
	char *data = pimpl_->LoadChar(fsys, filename, bufsize);
	FileLoadingInfo* flInfo = new FileLoadingInfo(filename, data, bufsize);
	flInfo->setLoc(location);
	std::string fname(filename);
	m_resMap.insert(fname, flInfo);

    //m_pvSurfaces.push_back(new FileLoadingInfo(filename, m_pLastSurface));
    //return surface;
	return std::string(data, bufsize);
}

void FileLoader::Load(const std::string & filename) const
{
	LOGSTREAM << "FileLoader Load '" << filename << "'";
	filesystem fsys(m_pBasepath.c_str(), "zip", true);
	LOGSTREAM << fsys;

    //zip_file_system::filesystem::file_info *finfo;
    //fsys.FindFile(&filename.c_str(), finfo);

	// Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)

    std::string contents;
    std::vector<char> vcontents;
    // slurp(contents, filename, false);
    //slurp(contents, filename);
    //slurp4(vcontents, fsys, filename);

    //std::string contents((std::istreambuf_iterator<char>(infile)),
      //  std::istreambuf_iterator<char>());

    //std::string tmp;

}


SDL_Surface* FileLoader::LoadImg(const std::string & filename, std::string location)
{

	boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs1 = m_resMap.find(filename);
	if (rexs1 != m_resMap.end())
	{
		FileLoadingInfo& finf = *(rexs1->second);
		LOGSTREAM << "FileLoader LoadImg in Cache '" << filename << "': " << location;
		finf++;
		return finf.m_pSurface;
	}
	else
		LOGSTREAM << "FileLoader LoadImg '" << filename << "' " << location;
	/*if (m_pvSurfaces.size() > 0)
	{
		surfacevector::pointer result = NULL;
		surfacevector::iterator end = m_pvSurfaces.end();
		for (surfacevector::iterator it = m_pvSurfaces.begin(); it < end ; it++)
		{
			FileLoadingInfo& current = (*it);
			if (current.Name().compare(filename))
			{
				//LOGSTREAM << "FileLoader freeing '" << current.Name() << "'";
				LOGSTREAM << "FileLoader LoadImg in Cache '" << current << "'";
				result = &current;
			}
		}
	}*/

	filesystem fsys(m_pBasepath.c_str(), "zip", true);
	LOGSTREAM << fsys;

	// Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)


	m_pLastLoaded = filename;
    SDL_Surface *surface = pimpl_->LoadImg(fsys, filename);
	FileLoadingInfo* flInfo = new FileLoadingInfo(filename, surface);
	flInfo->setLoc(location);
	std::string fname(filename);
	m_resMap.insert(fname, flInfo);

    //m_pvSurfaces.push_back(new FileLoadingInfo(filename, m_pLastSurface));
    return surface;
}

void FileLoader::FreeLast()
{
    //boost::ptr_vector<FileLoadingInfo>::auto_type current(m_pvSurfaces.pop_back());
	// LOGSTREAM << "FileLoader freeing '" << current->Name() << "'";
	LOGSTREAM << "FileLoader freeing 'FreeLast'";
    //std::string nase = f->Name();

    if (m_pLastLoaded == "")
    {
		return;
        //SDL_FreeSurface(m_pLastSurface);
    }

	boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs1 = m_resMap.find(m_pLastLoaded);
	if (rexs1 != m_resMap.end())
	{
		FileLoadingInfo& finf = *(rexs1->second);
		LOGSTREAM << "FileLoader FreeLast found Cached '" << finf << "'";
	}
	else
		LOGSTREAM << "FileLoader FreeLast NOT found Cached '" << m_pLastLoaded << "' atom.";
}

void FileLoader::Free( const std::string& name )
{
	LOGSTREAM << "FileLoader freeing '" << name << "'";

    /*surfacevector::pointer result = NULL;
    surfacevector::iterator end = m_pvSurfaces.end();
    for (surfacevector::iterator it = m_pvSurfaces.begin(); it < end ; it++)
    {
        FileLoadingInfo& current = (*it);
        if (current.Name().compare(name))
        {
			//LOGSTREAM << "FileLoader freeing '" << current.Name() << "'";
			LOGSTREAM << "FileLoader freeing '" << current << "'";
            m_pvSurfaces.erase(it);
            result = &current;
        }
    }*/
    // LOGSTREAM << result->Name();
}

TTF_Font* FileLoader::LoadFont( const std::string & filename, int ptsize, std::string  location )
{

	boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs1 = m_resMap.find(filename);
	if (rexs1 != m_resMap.end())
	{
		FileLoadingInfo& finf = *(rexs1->second);
		LOGSTREAM << "FileLoader LoadFont in Cache '" << filename << "': " << location;
		finf++;
		char *data = finf.m_pData;
		SDL_RWops* imgmem = SDL_RWFromMem(&data[0], finf.m_fsize);
		TTF_Font* font = TTF_OpenFontRW(imgmem, 1, ptsize);
		return font;
	}
	else
		LOGSTREAM << "FileLoader LoadFont '" << filename << "'";


	//FileLoadingInfo& aaa = m_resMap["bla"];
	//m_resMap["bla"];
	/*if (m_pvSurfaces.size() > 0)
	{
		surfacevector::pointer result = NULL;
		surfacevector::iterator end = m_pvSurfaces.end();
		for (surfacevector::iterator it = m_pvSurfaces.begin(); it < end ; it++)
		{
			FileLoadingInfo& current = (*it);
			if (current.Name().compare(filename))
			{
				//LOGSTREAM << "FileLoader freeing '" << current.Name() << "'";
				LOGSTREAM << "FileLoader LoadFont in Cache '" << current << "'";
				result = &current;
				break;
			}
		}
	}*/

	filesystem fsys(m_pBasepath.c_str(), "zip", true);
    LOGSTREAM << fsys;

    // Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)

    //TTF_Font* m_pLastFont = pimpl_->LoadFont(fsys, filename, ptsize);
    FileLoadingInfo* flInfo = pimpl_->LoadFont(fsys, filename, ptsize);
	flInfo->setLoc(location);

	//m_pvSurfaces.push_back(flInfo);
	//m_resMap.insert(std::string(filename), flInfo);


//	boost::ptr_map<std::string, FileLoadingInfo> map;
	//m_resMap.insert(std::string(filename), boost::ref(flInfo));
	std::string fname(filename);
	m_resMap.insert(fname, flInfo);
	//const FileLoadingInfo& res = m_resMap.at(filename);

	//boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs2 = m_resMap.find(filename + "dadsad");


    return flInfo->Font();
}


const char * FileLoaderException::what() const throw()
{
    if ( !m_imp_ptr.get() ) {
        return boost::system::system_error::what();
    }

    try
    {
        if ( m_imp_ptr->m_what.empty() ) {
            m_imp_ptr->m_what = boost::system::system_error::what();

            if ( !m_imp_ptr->m_path1.empty() ) {
                m_imp_ptr->m_what += ": \"";
                m_imp_ptr->m_what += m_imp_ptr->m_path1;
                m_imp_ptr->m_what += "\"";
            }

            if ( !m_imp_ptr->m_path2.empty() ) {
                m_imp_ptr->m_what += ", \"";
                m_imp_ptr->m_what += m_imp_ptr->m_path2;
                m_imp_ptr->m_what += "\"";
            }
        }

        return m_imp_ptr->m_what.c_str();
    }
    catch (...)
    {
        return boost::system::system_error::what();
    }
}

FileLoaderException::FileLoaderException( const std::string & what_arg, int ec ) :
boost::system::system_error(boost::system::error_code(ec, boost::system::system_category()), "")
{
    try
    {
        m_imp_ptr.reset(new m_imp);
        m_imp_ptr->m_what = what_arg;
        //m_imp_ptr->m_path1 = path1_arg;
        //m_imp_ptr->m_path2 = path2_arg;
    }
    catch (...) { m_imp_ptr.reset(); }
}

FileLoaderException::FileLoaderException( const std::string & what_arg, const std::string& path1_arg, const std::string& path2_arg, boost::system::error_code ec ) :
boost::system::system_error(ec, what_arg)
{
    try
    {
        m_imp_ptr.reset(new m_imp);
        m_imp_ptr->m_path1 = path1_arg;
        m_imp_ptr->m_path2 = path2_arg;
    }
    catch (...) { m_imp_ptr.reset(); }
}

FileLoaderException::FileLoaderException( const std::string & what_arg, const std::string& path1_arg, boost::system::error_code ec ) :
boost::system::system_error(ec, what_arg)
{
    try
    {
        m_imp_ptr.reset(new m_imp);
        m_imp_ptr->m_path1 = path1_arg;
    }
    catch (...) { m_imp_ptr.reset();
    }
}

FileLoaderException::FileLoaderException( const std::string & what_arg, boost::system::error_code ec ) :
boost::system::system_error(ec, what_arg)
{
    try
    {
        m_imp_ptr.reset(new m_imp);
    }
    catch (...) { m_imp_ptr.reset();
    }
}


