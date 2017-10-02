#ifndef HUMBUG_FS_HumbugFileLoader_H
#define HUMBUG_FS_HumbugFileLoader_H
#include <GuiLib/Filesystem/FileLoader.h>


class HumbugFileLoader : public FileLoader {
public:

    HumbugFileLoader(const std::string & basepath);
    ~HumbugFileLoader();

    FileLoadingInfo& Load(const std::string & filename, std::string location) override;
    std::string LoadAsString(const std::string & filename, std::string location) override;

private:

    struct HumbugFileLoaderImpl;
    boost::scoped_ptr<HumbugFileLoaderImpl> pimpl_;
};

#endif // HUMBUG_FS_HumbugFileLoader_H guard
