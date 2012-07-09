#ifndef HUMBUG_FS_FILELOADER_H
#define HUMBUG_FS_FILELOADER_H

#include <string>

class FileLoader {
public:

    FileLoader(const std::string & basepath);
    ~FileLoader();

    const char *language(int x) const;
    void Load(const std::string & filename);
    SDL_Surface* LoadImg(const std::string & filename);

private:
	std::string m_pBasepath;
};

#endif // HUMBUG_FS_FILELOADER_H
