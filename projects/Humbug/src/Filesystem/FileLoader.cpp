#include <build/cmake/include/debug.h>
#include "../stdafx.h"
#include "FileLoader.h"
#include <HumbugShared/VFS/zfsystem.h>

using zip_file_system::filesystem;
using zip_file_system::izfstream;


FileLoader::FileLoader(const std::string & basepath)
: m_pBasepath(basepath)
{
         dbgOut(__FUNCTION__ << std::endl);
}

FileLoader::~FileLoader(void)
{
         dbgOut(__FUNCTION__ << std::endl);
}

const char* FileLoader::language(int x) const
{
    return "AsciiDoc";
}

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

void slurp3(std::string& data, const filesystem& fsys, const std::string& filename)
{
    //std::ios_base::openmode openmode = ios::ate | ios::in;
    //if (is_binary)
    //    openmode |= ios::binary;
    //ifstream file(filename.c_str(), openmode);
    int fsize = fsys.FileSize(filename.c_str());
    izfstream file(filename.c_str());


	if (! file)
		std::cout << "ERROR: Cannot open file!" << std::endl;
    else
    {

        data.clear();
        data.reserve(fsize);
        data.append(std::istreambuf_iterator<char>(file.rdbuf()),
                    std::istreambuf_iterator<char>());

        std::vector<char> contents((std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>());
        int x = contents.size();

        /*//file.seekg(0, std::ios::beg);
        long cnt = 0;
        //while((c = file.peek()) != std:ios:eof)
        while(!file.eof())
        {
            char c;
            c = file.get();
            cnt++;
        }
        //data.clear();
        int sz = cnt;
  		std::cout << "file " << filename << " has a size of " << sz << " bytes." << std::endl;

        file.seekg(0, std::ios::beg);
        //data.append(std::istreambuf_iterator<char>(file.rdbuf()),
        //            std::istreambuf_iterator<char>());*/
    }

    file.close();
}

bool slurp4(std::vector<char>& data, const filesystem& fsys, const std::string& filename)
{
    int fsize = fsys.FileSize(filename.c_str());
    izfstream file(filename.c_str());

	if (! file)
    {
        std::cout << "ERROR: Cannot open file!" << std::endl;
        return false;
    }
    else
    {
        data.clear();
        data.resize(fsize);
        file.read(&data[0], fsize);

        SDL_RWops* imgmem = SDL_RWFromMem(&data[0], fsize);
        SDL_Surface* sdlsurface = IMG_Load_RW(imgmem, 1);

    }

    file.close();
    return true;
}

#   define FILELOADER_ERRNO    errno

SDL_Surface* slurp5(const filesystem& fsys, const std::string& filename)
{
    int fsize = fsys.FileSize(filename.c_str());
    izfstream file(filename.c_str());
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
    slurp4(vcontents, fsys, filename);

    //std::string contents((std::istreambuf_iterator<char>(infile)),
      //  std::istreambuf_iterator<char>());

    //std::string tmp;

}



SDL_Surface* FileLoader::LoadImg(const std::string & filename) const
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
    SDL_Surface* sdlsurface = slurp5(fsys, filename);
    return sdlsurface;

    //std::string contents((std::istreambuf_iterator<char>(infile)),
      //  std::istreambuf_iterator<char>());

    //std::string tmp;

}

