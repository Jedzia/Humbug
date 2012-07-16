#ifndef HUMBUG_FS_FILELOADER_H
#define HUMBUG_FS_FILELOADER_H
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <string>

class FileLoadingInfo 
{
public:
    FileLoadingInfo(SDL_Surface* surface);
    ~FileLoadingInfo();
private:
    SDL_Surface* m_pSurface;
};

class FileLoader {
public:

    FileLoader(const std::string & basepath);
    ~FileLoader();
    const char* language(int x) const;

    // Placeholder
    void Load(const std::string & filename) const;

    // Loads a image from the package or filesystem.
    // Remember to use SDL_FreeSurface( surface ) to release the allocated memory.
    SDL_Surface* LoadImg(const std::string & filename) const;
    void FreeLast();

private:

    std::string m_pBasepath;
    static SDL_Surface* m_pLastSurface;
    boost::ptr_vector<FileLoadingInfo> m_pvSurfaces;

};
#define HUMBUG_FILELOADER_THROW(EX) \
    throw EX
class FileLoaderException : public boost::system::system_error {
    // see http://www.boost.org/more/error_handling.html for design rationale
    // all functions are inline to avoid issues with crossing dll boundaries

public:

    // compiler generates copy constructor and copy assignment
    FileLoaderException(            const std::string & what_arg, boost::system::error_code ec);

    FileLoaderException(
            const std::string & what_arg, const std::string& path1_arg,
            boost::system::error_code ec);

    FileLoaderException(
            const std::string & what_arg, const std::string& path1_arg,
            const std::string& path2_arg, boost::system::error_code ec);

    FileLoaderException(            const std::string & what_arg, int ec);

    ~FileLoaderException()
    throw() {}

    const std::string& path1() const {
        static const std::string empty_path;
        return m_imp_ptr.get() ? m_imp_ptr->m_path1 : empty_path;
    }

    const std::string& path2() const {
        static const std::string empty_path;
        return m_imp_ptr.get() ? m_imp_ptr->m_path2 : empty_path;
    }

    const char * what() const
    throw(); // what

private:

    struct m_imp
    {
        std::string m_path1;       // may be empty()
        std::string m_path2;       // may be empty()
        // path         m_path1; // may be empty()
        // path         m_path2; // may be empty()
        std::string m_what; // not built until needed
    };
    boost::shared_ptr<m_imp> m_imp_ptr;
};
#endif // HUMBUG_FS_FILELOADER_H
