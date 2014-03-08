#ifndef HUMBUG_FS_FILELOADER_H
#define HUMBUG_FS_FILELOADER_H
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <string>

#define STRX(x) #x
#define STR(x) STRX(x)
//#define FL_LOADFONT(fname, ptsize) LoadFont(fname, ptsize, std::string("[") + __FILE__ + "]-> " + __FUNCTION__)
#define FL_LOADFONT(fname, ptsize) LoadFont(fname, ptsize, std::string("") + __FILE__ + "(" +  STR(__LINE__) + ") -> " + __FUNCTION__)
#define FL_LOADIMG(fname) LoadImg(fname, std::string("") + __FILE__  + "(" + STR(__LINE__) + ") -> " + __FUNCTION__)
#define FL_LOADASSTRING(fname) LoadAsString(fname, std::string("") + __FILE__  + "(" + STR(__LINE__) + ") -> " + __FUNCTION__)
#define FL_LOAD(fname) Load(fname, std::string("") + __FILE__  + "(" + STR(__LINE__) + ") -> " + __FUNCTION__)

struct SDL_Surface;
struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;
struct SDL_RWops;

class FileLoadingInfo : public boost::noncopyable
{
public:
    FileLoadingInfo(const std::string name, SDL_Surface* surface);
    FileLoadingInfo(const std::string name, TTF_Font* font, SDL_RWops* area, char *data, int fsize);
	FileLoadingInfo(const std::string name, char *data, int fsize = 0);
 ~FileLoadingInfo();

    std::string Name() const { return m_strName; }
    void Name(std::string val) { m_strName = val; }
    TTF_Font* Font() const { return m_pFont; }
	std::string Loc() const { return m_strLoc; }
	void setLoc(std::string val) { m_strLoc = val; }
	int Refcount() const { return m_refcount; }
	char * Data() const { return m_pData; }
	int Size() const { return m_fsize; }

	FileLoadingInfo& operator ++(int);
	FileLoadingInfo& operator --(int);
private:
	std::string m_strName;
	std::string m_strLoc;
	SDL_Surface* m_pSurface;
    TTF_Font* m_pFont;
    SDL_RWops* m_pArea;
    char *m_pData;
	int m_refcount;
	int m_fsize;
	friend std::ostream& operator<<(std::ostream& o, const FileLoadingInfo& r);
	friend class FileLoader;
};

std::ostream& operator<<(std::ostream& o, const FileLoadingInfo& r);

class FileLoader {
public:

    FileLoader(const std::string & basepath);
    ~FileLoader();
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

    struct FileLoaderImpl;
    boost::scoped_ptr<FileLoaderImpl> pimpl_;
};

// File loader exceptions
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
