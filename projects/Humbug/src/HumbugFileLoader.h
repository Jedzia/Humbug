#ifndef HUMBUG_FS_HumbugFileLoader_H
#define HUMBUG_FS_HumbugFileLoader_H
#include <GuiLib/Filesystem/FileLoader.h>
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <string>


class HumbugFileLoader : public FileLoader {
public:

    HumbugFileLoader(const std::string & basepath);
    ~HumbugFileLoader();
    const char* language(int x) const;

    // Placeholder
	FileLoadingInfo& Load(const std::string & filename, std::string location);
	std::string LoadAsString(const std::string & filename, std::string location);

    // Loads a image from the package or filesystem.
    // Remember to use SDL_FreeSurface( surface ) to release the allocated memory.
    SDL_Surface* LoadImg(const std::string & filename, std::string location) ;
    TTF_Font* LoadFont(const std::string & filename, int ptsize, std::string  location ) ;
    void Free(const std::string& name);
    void FreeLast();

private:

    std::string m_pBasepath;
	std::string m_pLastLoaded;
    typedef boost::ptr_vector<FileLoadingInfo> surfacevector;
    //surfacevector m_pvSurfaces;
	boost::ptr_map<std::string, FileLoadingInfo> m_resMap;

    struct HumbugFileLoaderImpl;
    boost::scoped_ptr<HumbugFileLoaderImpl> pimpl_;
};

#endif // HUMBUG_FS_HumbugFileLoader_H
