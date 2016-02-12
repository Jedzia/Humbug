#include "stdafx.h"
//
#include "HumbugFileLoader.h"
#include <HumbugLib/LogManager.h>
#include <HumbugShared/VFS/zfsystem.h>
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"

using zip_file_system::filesystem;
using zip_file_system::izfstream;



// HumbugFileLoader

struct HumbugFileLoader::HumbugFileLoaderImpl {

#   define HumbugFileLoader_ERRNO    errno

    static void slurp(std::string& data, const std::string& filename, bool is_binary = false)
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

    static void slurp2(std::string& data, const std::string& filename, bool is_binary = false)
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
        SDL_RWops* imgmem;

        if (! file)
        {
            //std::cerr << "[HumbugFileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened.";
			LOGSTREAM << "ERROR: Can't load:" + filename;

			// Todo: does not show filename with the exception.
            HUMBUG_FILELOADER_THROW(
                FileLoaderException("[HumbugFileLoader::LoadImg-slurp5]", filename,
                boost::system::error_code(HumbugFileLoader_ERRNO, boost::system::system_category())));
        }
        
        //data.clear();
        //data.resize(fsize);
        data = new char[bufsize];
        file.read(&data[0], bufsize);
        imgmem = SDL_RWFromMem(&data[0], bufsize);

        file.close();
        return imgmem;
    }

    static int PrepareRead( const filesystem &fsys, const std::string &filename, izfstream &file )
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

    static char* LoadChar(const filesystem& fsys, const std::string& filename, int& bufsize)
	{
		izfstream file(filename.c_str());
		bufsize = PrepareRead(fsys, filename, file);

		char* data;
		if (! file)
		{
			//std::cerr << "[HumbugFileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened.";
			LOGSTREAM << "ERROR: Can't load:" + filename;

			// Todo: does not show filename with the exception.
			HUMBUG_FILELOADER_THROW(
				FileLoaderException("[HumbugFileLoader::LoadChar]", filename,
				boost::system::error_code(HumbugFileLoader_ERRNO, boost::system::system_category())));
		}
	    
        data = new char[bufsize];
	    file.read(&data[0], bufsize);

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
            //std::cerr << "[HumbugFileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUG_FILELOADER_THROW(
                FileLoaderException("[HumbugFileLoader::LoadImg-imgmem]", filename,
                boost::system::error_code(HumbugFileLoader_ERRNO, boost::system::system_category())));
        }
        
        //data.clear();
        //data.resize(fsize);
        //SDL_LoadBMP_RW(imgmem, 1);
        sdlsurface = IMG_Load_RW(imgmem, 1);
        //SDL_FreeRW(imgmem);
        delete[] data;
        if (!sdlsurface) {
            //fprintf(stderr, "Error: '%s' could not be opened: %s\n", filename.c_str(), IMG_GetError());
            // load a internal error image.
            const char *imgMsg = IMG_GetError();

            HUMBUG_FILELOADER_THROW(
                FileLoaderException(std::string("[HumbugFileLoader::LoadImg-sdlsurface]: '" ) + filename + "' " + imgMsg, 1));
            // generic_category
        }

        return sdlsurface;
    }

    FileLoadingInfo* LoadFont(const filesystem& fsys, const std::string & filename, int ptsize )
    {
        //std::vector<char> data;
        TTF_Font* font;
		int bufsize;
        SDL_RWops* imgmem = LoadData(fsys, filename, bufsize);
        FileLoadingInfo *flinfo;

        if (! imgmem)
        {
            //std::cerr << "[HumbugFileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUG_FILELOADER_THROW(
                FileLoaderException("[HumbugFileLoader::LoadFont]", filename,
                boost::system::error_code(HumbugFileLoader_ERRNO, boost::system::system_category())));
        }
        
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
                FileLoaderException(std::string("[HumbugFileLoader::LoadFont]: '" ) + filename + "' " + TTF_GetError(), 1));
            // generic_category
        }

        return flinfo;

    };

    static SDL_Surface* LoadImgXX(const filesystem& fsys, const std::string& filename)
    {
		izfstream file(filename.c_str());
		int fsize = PrepareRead(fsys, filename, file);
        //std::vector<char> data;
        SDL_Surface* sdlsurface;

        if (! file)
        {
            //std::cerr << "[HumbugFileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUG_FILELOADER_THROW(
                FileLoaderException("[HumbugFileLoader::LoadImg-slurp5]", filename,
                boost::system::error_code(HumbugFileLoader_ERRNO, boost::system::system_category())));
        }
        
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
                FileLoaderException(std::string("[HumbugFileLoader::LoadImg-slurp5]: '" ) + filename + "' " + IMG_GetError(), 1));

            // generic_category
        }

        file.close();
        return sdlsurface;
    }


};

HumbugFileLoader::HumbugFileLoader(const std::string & basepath)
: FileLoader(basepath), pimpl_(new HumbugFileLoader::HumbugFileLoaderImpl)
{
	 using namespace humbuglib;
     dbgOut(__FUNCTION__);
	 LogManager::getSingleton().logMessage("Creating HumbugFileLoader for '" + basepath + "'.");
	 LogManager::getSingleton().stream() << "Logging from Stream.";
}

HumbugFileLoader::~HumbugFileLoader(void)
{
    //m_pvSurfaces.release();
	m_resMap.release();
    dbgOut(__FUNCTION__);
	humbuglib::LogManager::getSingleton().stream() << __FUNCTION__ << " Logging from Stream.";

}

std::string HumbugFileLoader::LoadAsString(const std::string & filename, std::string location)
{
	std::string tmp;
	boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs1 = m_resMap.find(filename);
	if (rexs1 != m_resMap.end())
	{
		FileLoadingInfo& finf = *(rexs1->second);
		LOGSTREAM << "HumbugFileLoader LoadAsString in Cache '" << filename << "': " << location;
		finf++;
		return std::string(finf.GetData(), finf.GetFileSize());
	}
	else
		LOGSTREAM << "HumbugFileLoader LoadAsString '" << filename << "' " << location;

    filesystem fsys(GetBasepathCstr(), "zip", true);
	LOGSTREAM << fsys;

	// Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)


	SetLastLoaded(filename);
	int bufsize;
	char *data = pimpl_->LoadChar(fsys, filename, bufsize);
	FileLoadingInfo* flInfo = new FileLoadingInfo(filename, data, bufsize);
	flInfo->SetLocation(location);
	std::string fname(filename);
	m_resMap.insert(fname, flInfo);

    //m_pvSurfaces.push_back(new FileLoadingInfo(filename, m_pLastSurface));
    //return surface;
	return std::string(data, bufsize);
}

FileLoadingInfo& HumbugFileLoader::Load(const std::string & filename, std::string location)
{
	boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs1 = m_resMap.find(filename);
	if (rexs1 != m_resMap.end())
	{
		FileLoadingInfo& finf = *(rexs1->second);
		LOGSTREAM << "HumbugFileLoader LoadImg in Cache '" << filename << "': " << location;
		finf++;
		return finf;
	}
	else
		LOGSTREAM << "HumbugFileLoader Load '" << filename << "' " << location;

    filesystem fsys(GetBasepathCstr(), "zip", true);
	LOGSTREAM << fsys;

	// Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)


    SetLastLoaded(filename);
    int bufsize;
	char *data = pimpl_->LoadChar(fsys, filename, bufsize);
	FileLoadingInfo* flInfo = new FileLoadingInfo(filename, data, bufsize);
	flInfo->SetLocation(location);
	std::string fname(filename);
	m_resMap.insert(fname, flInfo);

    //m_pvSurfaces.push_back(new FileLoadingInfo(filename, m_pLastSurface));
    return *flInfo;
}


SDL_Surface* HumbugFileLoader::LoadImg(const std::string & filename, std::string location)
{

	boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs1 = m_resMap.find(filename);
	if (rexs1 != m_resMap.end())
	{
		FileLoadingInfo& finf = *(rexs1->second);
		LOGSTREAM << "HumbugFileLoader LoadImg in Cache '" << filename << "': " << location;
		finf++;
		return finf.GetSurface();
	}
	else
		LOGSTREAM << "HumbugFileLoader LoadImg '" << filename << "' " << location;
	/*if (m_pvSurfaces.size() > 0)
	{
		surfacevector::pointer result = NULL;
		surfacevector::iterator end = m_pvSurfaces.end();
		for (surfacevector::iterator it = m_pvSurfaces.begin(); it < end ; ++it)
		{
			FileLoadingInfo& current = (*it);
			if (current.SetName().compare(filename))
			{
				//LOGSTREAM << "HumbugFileLoader freeing '" << current.SetName() << "'";
				LOGSTREAM << "HumbugFileLoader LoadImg in Cache '" << current << "'";
				result = &current;
			}
		}
	}*/

    filesystem fsys(GetBasepathCstr(), "zip", true);
	LOGSTREAM << fsys;

	// Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)


    SetLastLoaded(filename);
    SDL_Surface *surface = pimpl_->LoadImg(fsys, filename);
	FileLoadingInfo* flInfo = new FileLoadingInfo(filename, surface);
	flInfo->SetLocation(location);
	std::string fname(filename);
	m_resMap.insert(fname, flInfo);

    //m_pvSurfaces.push_back(new FileLoadingInfo(filename, m_pLastSurface));
    return surface;
}

TTF_Font* HumbugFileLoader::LoadFont( const std::string & filename, int ptsize, std::string  location )
{

	boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs1 = m_resMap.find(filename);
	if (rexs1 != m_resMap.end())
	{
		FileLoadingInfo& finf = *(rexs1->second);
		LOGSTREAM << "HumbugFileLoader LoadFont in Cache '" << filename << "': " << location;
		finf++;
		char *data = finf.GetData();
		SDL_RWops* imgmem = SDL_RWFromMem(&data[0], finf.GetFileSize());
		TTF_Font* font = TTF_OpenFontRW(imgmem, 1, ptsize);
		return font;
	}
	else
		LOGSTREAM << "HumbugFileLoader LoadFont '" << filename << "'";


	//FileLoadingInfo& aaa = m_resMap["bla"];
	//m_resMap["bla"];
	/*if (m_pvSurfaces.size() > 0)
	{
		surfacevector::pointer result = NULL;
		surfacevector::iterator end = m_pvSurfaces.end();
		for (surfacevector::iterator it = m_pvSurfaces.begin(); it < end ; ++it)
		{
			FileLoadingInfo& current = (*it);
			if (current.SetName().compare(filename))
			{
				//LOGSTREAM << "HumbugFileLoader freeing '" << current.SetName() << "'";
				LOGSTREAM << "HumbugFileLoader LoadFont in Cache '" << current << "'";
				result = &current;
				break;
			}
		}
	}*/

    filesystem fsys(GetBasepathCstr(), "zip", true);
    LOGSTREAM << fsys;

    // Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)

    //TTF_Font* m_pLastFont = pimpl_->LoadFont(fsys, filename, ptsize);
    FileLoadingInfo* flInfo = pimpl_->LoadFont(fsys, filename, ptsize);
	flInfo->SetLocation(location);

	//m_pvSurfaces.push_back(flInfo);
	//m_resMap.insert(std::string(filename), flInfo);


//	boost::ptr_map<std::string, FileLoadingInfo> map;
	//m_resMap.insert(std::string(filename), boost::ref(flInfo));
	std::string fname(filename);
	m_resMap.insert(fname, flInfo);
	//const FileLoadingInfo& res = m_resMap.at(filename);

	//boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs2 = m_resMap.find(filename + "dadsad");


    return flInfo->GetFont();
}

