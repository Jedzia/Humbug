#ifndef HUMBUGGL_FS_HumbugGLFileLoader_H
#define HUMBUGGL_FS_HumbugGLFileLoader_H
#include <GuiLib/Filesystem/FileLoader.h>


class HumbugGLFileLoader : public FileLoader {
public:

    HumbugGLFileLoader(const std::string & basepath);
    ~HumbugGLFileLoader();

    FileLoadingInfo& Load(const std::string & filename, std::string location) override;
    std::string LoadAsString(const std::string & filename, std::string location) override;

private:

    struct HumbugGLFileLoaderImpl;
    boost::scoped_ptr<HumbugGLFileLoaderImpl> pimpl_;
};

#endif // HUMBUGGL_FS_HumbugGLFileLoader_H guard
