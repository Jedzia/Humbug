#include "../stdafx.h"
#include "FileLoader.h"
#include <HumbugShared/VFS/zfsystem.h>
#include "SDL.h"
#include "SDL_ttf.h"

using zip_file_system::filesystem;
using zip_file_system::izfstream;


// FileLoadingInfo

FileLoadingInfo::FileLoadingInfo(const std::string name, SDL_Surface* surface)
: m_strName(name), m_pSurface(surface), m_pFont(NULL), m_pArea(NULL), m_pData(NULL)
{

}

FileLoadingInfo::FileLoadingInfo( const std::string name, TTF_Font* font, SDL_RWops* area, char *data )
: m_strName(name), m_pSurface(NULL), m_pFont(font), m_pArea(area), m_pData(data)
{

}

FileLoadingInfo::~FileLoadingInfo()
{
    std::cout << "FileLoadingInfo freeing '" << Name() << "'" << std::endl;
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
            std::cout << "ERROR: Cannot open file!" << std::endl;
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
            std::cout << "ERROR: Cannot open file!" << std::endl;
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
    SDL_RWops* LoadData(const filesystem& fsys, const std::string& filename)
    {
        data = NULL;
        int fsize = fsys.FileSize(filename.c_str());
        izfstream file(filename.c_str());
        //std::vector<char> data;
        SDL_RWops* imgmem = NULL;
        SDL_Surface *sdlsurface=NULL;

        if (! file)
        {
            //std::cerr << "[FileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUGGL_FILELOADER_THROW(
                FileLoaderException("[FileLoader::LoadImg-slurp5]", filename,
                boost::system::error_code(FILELOADER_ERRNO, boost::system::system_category())));
            return NULL;
        }
        else
        {
            //data.clear();
            //data.resize(fsize);
            data = new char[fsize];
            file.read(&data[0], fsize);
            imgmem = SDL_RWFromMem(&data[0], fsize);

            //sdlsurface = IMG_Load_RW(imgmem, 1);
        }

        file.close();
        return imgmem;
    }


    SDL_Surface* LoadImg(const filesystem& fsys, const std::string& filename)
    {
        //std::vector<char> data;
        SDL_Surface* sdlsurface;
        SDL_RWops* imgmem = LoadData(fsys, filename);

        if (! imgmem)
        {
            //std::cerr << "[FileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUGGL_FILELOADER_THROW(
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
                HUMBUGGL_FILELOADER_THROW(
                    FileLoaderException(std::string("[FileLoader::LoadImg-sdlsurface]: '" ) + filename + "' " + IMG_GetError(), 1));
                // generic_category
            }
        }

        return sdlsurface;
    }

    FileLoadingInfo* LoadFont(const filesystem& fsys, const std::string & filename, int ptsize )
    {
        //std::vector<char> data;
        TTF_Font* font;
        SDL_RWops* imgmem = LoadData(fsys, filename);
        FileLoadingInfo *flinfo = NULL;

        if (! imgmem)
        {
            //std::cerr << "[FileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUGGL_FILELOADER_THROW(
                FileLoaderException("[FileLoader::LoadFont]", filename,
                boost::system::error_code(FILELOADER_ERRNO, boost::system::system_category())));
            return NULL;
        }
        else
        {
            //data.clear();
            //data.resize(fsize);
            font = TTF_OpenFontRW(imgmem, 1, ptsize);
            flinfo = new FileLoadingInfo(filename, font, imgmem, data);
            //SDL_FreeRW(imgmem);
            //delete[] data;
            if (!font) {
                //fprintf(stderr, "Error: '%s' could not be opened: %s\n", filename.c_str(), IMG_GetError());
                // load a internal error image.
                HUMBUGGL_FILELOADER_THROW(
                    FileLoaderException(std::string("[FileLoader::LoadFont]: '" ) + filename + "' " + TTF_GetError(), 1));
                // generic_category
            }

        }

        return flinfo;

    };

    SDL_Surface* LoadImgXX(const filesystem& fsys, const std::string& filename)
    {
        int fsize = fsys.FileSize(filename.c_str());
        izfstream file(filename.c_str());
        //std::vector<char> data;
        SDL_Surface* sdlsurface;

        if (! file)
        {
            //std::cerr << "[FileLoader::LoadImg-slurp5] Error: " << filename << " could not be opened." << std::endl;
            HUMBUGGL_FILELOADER_THROW(
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
                HUMBUGGL_FILELOADER_THROW(
                    FileLoaderException(std::string("[FileLoader::LoadImg-slurp5]: '" ) + filename + "' " + IMG_GetError(), 1));
                // generic_category
            }
        }

        file.close();
        return sdlsurface;
    }


};

FileLoader::FileLoader(const std::string & basepath)
: pimpl_(new FileLoader::FileLoaderImpl), m_pBasepath(basepath), m_pLastSurface(NULL)
{
         dbgOut(__FUNCTION__ << std::endl);
}

FileLoader::~FileLoader(void)
{
    m_pvSurfaces.release();
    dbgOut(__FUNCTION__ << std::endl);
}

const char* FileLoader::language(int x) const
{
    return "AsciiDoc";
}

void FileLoader::Load(const std::string & filename) const
{
	filesystem fsys(m_pBasepath.c_str(), "zip", true);
	std::cout << fsys << std::endl;

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



SDL_Surface* FileLoader::LoadImg(const std::string & filename) 
{
	filesystem fsys(m_pBasepath.c_str(), "zip", true);
	std::cout << fsys << std::endl;

	// Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)

    m_pLastSurface = pimpl_->LoadImg(fsys, filename);
    m_pvSurfaces.push_back(new FileLoadingInfo(filename, m_pLastSurface));
    return m_pLastSurface;
}

void FileLoader::FreeLast()
{
    boost::ptr_vector<FileLoadingInfo>::auto_type current(m_pvSurfaces.pop_back());
    std::cout << "FileLoader freeing '" << current->Name() << "'" << std::endl;
    //std::string nase = f->Name();
    
    /*if (m_pLastSurface)
    {
        SDL_FreeSurface(m_pLastSurface);
    }*/
}

void FileLoader::Free( const std::string& name )
{

    surfacevector::pointer result = NULL;
    surfacevector::iterator end = m_pvSurfaces.end();
    for (surfacevector::iterator it = m_pvSurfaces.begin(); it < end ; it++)
    {
        FileLoadingInfo& current = (*it);
        if (current.Name().compare(name))
        {
            std::cout << "FileLoader freeing '" << current.Name() << "'" << std::endl;
            //m_pvSurfaces.erase(it);
            //result = &current;
        }
    }
    // std::cout << result->Name() << std::endl;
}

TTF_Font* FileLoader::LoadFont( const std::string & filename, int ptsize )
{
    filesystem fsys(m_pBasepath.c_str(), "zip", true);
    std::cout << fsys << std::endl;

    // Try to open a zipped file (Careful! The openmode is always 'ios::in | ios::binary'.)

    //TTF_Font* m_pLastFont = pimpl_->LoadFont(fsys, filename, ptsize);
    FileLoadingInfo* m_pflInfo = pimpl_->LoadFont(fsys, filename, ptsize);
    m_pvSurfaces.push_back(m_pflInfo);
    return m_pflInfo->Font();
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

