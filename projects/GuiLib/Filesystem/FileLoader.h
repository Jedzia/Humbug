/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      File loading interface and related info
 *             and error classes.
 * \file       FileLoader.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_FS_FILELOADER_H
#define HUMBUG_FS_FILELOADER_H
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <string>

#define STRX(x) # x
#define STR(x) STRX(x)
#define FL_LOADFONT(fname, ptsize) LoadFont(fname, ptsize, std::string("") + __FILE__ + "(" + STR( \
                __LINE__) + ") -> " + __FUNCTION__)
#define FL_LOADIMG(fname) LoadImg(fname, std::string("") + __FILE__ + "(" + STR(__LINE__) + ") -> " + __FUNCTION__)
#define FL_LOADASSTRING(fname) LoadAsString(fname, std::string("") + __FILE__ + "(" + STR( \
                __LINE__) + ") -> " + __FUNCTION__)
#define FL_LOAD(fname) Load(fname, std::string("") + __FILE__ + "(" + STR(__LINE__) + ") -> " + __FUNCTION__)

struct SDL_Surface;
struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;
struct SDL_RWops;

/** @class FileLoadingInfo:
 *  Stores file related information about objects loaded into memory.
 *  Handles the lifetime of the stored SDL objects.
 */
class FileLoadingInfo : public boost::noncopyable {
public:

    /** Initializes a new instance of the FileLoadingInfo class with a SDL_Surface.
    *  Creates a FileLoadingInfo of a SDL_Surface.
    *  @param name The name of the FileLoadingInfo.
    *  @param surface The surface to be stored.
    */
    FileLoadingInfo(const std::string name, SDL_Surface* surface);

    /** Initializes a new instance of the <see cref="FileLoadingInfo"/> class with a TTF_Font.
    *  Creates a FileLoadingInfo of a TTF_Font.
    *  @param name The name of the FileLoadingInfo.
    *  @param font The font to be stored.
    *  @param area The underlying SDL_RWops data.
    *  @param data The underlying raw file data.
    *  @param fsize The size of the \p data.
    */
    FileLoadingInfo(const std::string name, TTF_Font* font, SDL_RWops* area, char* data, int fsize);

    /// <summary>
    /// Initializes a new instance of the <see cref="FileLoadingInfo"/> class with raw data.
    /// </summary>
    /// <param name="name">The name of the FileLoadingInfo.</param>
    /// <param name="data">The underlying raw file data.</param>
    /// <param name="fsize">The size of the \p data.</param>
    FileLoadingInfo(const std::string name, char* data, int fsize = 0);

    /// <summary>
    /// Finalizes an instance of the <see cref="FileLoadingInfo"/> class.
    /// </summary>   
    /// <remarks>
    /// Handles the destruction of the stored raw data.
    /// </remarks>   
    ~FileLoadingInfo();

    /**  Gets the name.
     *  Gets the name of the FileLoadingInfo.
     *  @return the name of the FileLoadingInfo.
     */
    std::string GetName() const { return m_strName; }

    /**  Sets the name.
     *  Sets the name of the FileLoadingInfo.
     *  @param val Value of the name to be set.
     */
    void SetName(std::string val) { m_strName = val; }

    /**  Gets the stored font.
     *  Gets the Font connected with this instance.
     *  @return the connected SDL Font.
     */
    TTF_Font * GetFont() const { return m_pFont; }

    /** Gets the debug location data.
    *  Gets the Debug Helper Location of this instance.
    *  @return the Debug Helper Location.
    */
    std::string GetLocation() const { return m_strLoc; }

    /** Sets the debug location data.
    *  Sets the Debug Helper Location of this instance.
    *  @param val TODO
     */
    void SetLocation(std::string val) { m_strLoc = val; }

    /** Gets the reference count.
    *  Gets the number of instances referencing this object.
    *  @return the reference count.
     */
    int GetRefcount() const { return m_refcount; }

    /** Gets the stored surface.
    *  Gets the Surface data connected with this instance.
    *  @return the connected SDL_Surface.
    */
    SDL_Surface * GetSurface() const {
        return m_pSurface;
    }

    /** Gets the stored data.
    *  Gets the raw underlying data connected with this instance. 
    *  Often SDL_RWops or pure binary file data.
    *  @return the raw SDL data.
    */
    char * GetData() const {
        return m_pData;
    }

    /** Gets the FileSize.
    *  Gets the size of the stored data (of @GetData). 
    *  @return the size of the stored data.
    */
    int GetFileSize() const {
        return m_fsize;
    }

    /// <summary>
    /// Increments the reference count.
    /// </summary>
    /// <param name="">The .</param>
    /// <returns>FileLoadingInfo &.</returns>
    FileLoadingInfo& operator ++(int);

    /// <summary>
    /// Decrements the reference count.
    /// </summary>
    /// <param name="">The .</param>
    /// <returns>FileLoadingInfo &.</returns>
    FileLoadingInfo& operator --(int);

private:

    std::string m_strName;
    std::string m_strLoc;
    SDL_Surface* m_pSurface;
    TTF_Font* m_pFont;
    SDL_RWops* m_pArea;
    char* m_pData;
    int m_refcount;
    int m_fsize;
    friend std::ostream& operator<<(std::ostream& o, const FileLoadingInfo& r);

    friend class FileLoader;
};

std::ostream& operator<<(std::ostream& o, const FileLoadingInfo& r);

/** @class FileLoader:
 *  The FileLoader abstracts access to file system operations.
 *  This interface provides access to SDL data used by the GuiLib. A user
 *  has to implement this interface for easy use of ... bla bla bla.
 */
class FileLoader {
public:

    /// <summary>
    /// Initializes a new instance of the <see cref="FileLoader"/> class with a base search path.
    /// </summary>
    /// <param name="basepath">The base filesystem path to search for requested files.</param>
    FileLoader(const std::string & basepath);
    virtual ~FileLoader();
    const char * language(int x) const;

    /// <summary>
    /// Loads the specified filename.
    /// </summary>
    /// <param name="filename">The path and name of the file to load.</param>
    /// <param name="location">The instantiate location for logging and debugging.</param>
    /// <returns>a FileLoadingInfo representing the loaded data.</returns>
    virtual FileLoadingInfo& Load(const std::string & filename, std::string location) = 0;

    /// <summary>
    /// Loads the specified file as string.
    /// </summary>
    /// <param name="filename">The path and name of the file to load.</param>
    /// <param name="location">The instantiate location for logging and debugging.</param>
    /// <returns>the file content as string.</returns>
    virtual std::string LoadAsString(const std::string & filename, std::string location) = 0;

    /// <summary>
    /// Loads the specified image as SDL_Surface.
    /// </summary>
    /// <param name="filename">The path and name of the file to load.</param>
    /// <param name="location">The instantiate location for logging and debugging.</param>
    /// <returns>the SDL_Surface loaded via \p filename.</returns>
    virtual SDL_Surface * LoadImg(const std::string & filename, std::string location) = 0;

    /// <summary>
    /// Loads the the specified file as TTF_Font.
    /// </summary>
    /// <param name="filename">The path and name of the file to load.</param>
    /// <param name="ptsize">The font size.</param>
    /// <param name="location">The instantiate location for logging and debugging.</param>
    /// <returns>the TTF_Font loaded via \p filename.</returns>
    virtual TTF_Font * LoadFont(const std::string & filename, int ptsize, std::string location) = 0;

    /// <summary>
    /// Frees the file with the specified name (!!! not implemented !!!).
    /// </summary>
    /// <param name="name">The name of the file.</param>
    void Free(const std::string& name);

    /// <summary>
    /// Immediately frees the last file loaded.
    /// </summary>
    void FreeLast();

protected:

    /// <summary>
    /// Gets the C-String of the basepath.
    /// </summary>
    /// <returns> the base path as C-String.</returns>
    const char * GetBasepathCstr() const {
        return m_pBasepath.c_str();
    }

    /// <summary>
    /// Gets the path and name of the last loaded file.
    /// </summary>
    /// <returns>std.string.</returns>
    std::string GetLastLoaded() const {
        return m_pLastLoaded;
    }

    /// <summary>
    /// Sets the path and name of the last loaded file.
    /// </summary>
    /// <param name="name">The name of the file.</param>
    void SetLastLoaded(const std::string name){
        m_pLastLoaded = name;
    }
    
    boost::ptr_map<std::string, FileLoadingInfo> m_resMap;

private:

    std::string m_pBasepath;
    std::string m_pLastLoaded;
    typedef boost::ptr_vector<FileLoadingInfo> surfacevector;
};

// File loader exceptions
#define HUMBUG_FILELOADER_THROW(EX) \
    throw EX
/** @class FileLoaderException:
 *  Detailed description.
 *  @return TODO
 */
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

    /** $(fclass), path1:
     *  Detailed description.
     *  @return TODO
     */
    const std::string& path1() const {
        static const std::string empty_path;
        return m_imp_ptr.get() ? m_imp_ptr->m_path1 : empty_path;
    }
    /** $(fclass), path2:
     *  Detailed description.
     *  @return TODO
     */
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
