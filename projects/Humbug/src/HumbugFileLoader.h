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

    // Placeholder
    FileLoadingInfo& Load(const std::string & filename, std::string location) override;
    std::string LoadAsString(const std::string & filename, std::string location) override;

    // Loads a image from the package or filesystem.
    // Remember to use SDL_FreeSurface( surface ) to release the allocated memory.
    SDL_Surface* LoadImg(const std::string & filename, std::string location) override;
    TTF_Font* LoadFont(const std::string & filename, int ptsize, std::string  location ) override;
    //void Free(const std::string& name);
    //void FreeLast();

private:

    struct HumbugFileLoaderImpl;
    boost::scoped_ptr<HumbugFileLoaderImpl> pimpl_;
};

#endif // HUMBUG_FS_HumbugFileLoader_H
