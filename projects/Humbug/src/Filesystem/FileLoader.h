#ifndef HUMBUG_FS_FILELOADER_H
#define HUMBUG_FS_FILELOADER_H

#include <string>

class FileLoader {
public:

    FileLoader(const std::string & basepath);
    ~FileLoader();

    const char *language(int x) const;
    void Load(const std::string & filename) const;
    SDL_Surface* LoadImg(const std::string & filename) const;

private:
	std::string m_pBasepath;
};

  class FileLoaderException //: public system::system_error
  {
  // see http://www.boost.org/more/error_handling.html for design rationale

  // all functions are inline to avoid issues with crossing dll boundaries

  public:
    // compiler generates copy constructor and copy assignment

    FileLoaderException(
      const std::string & what_arg, int ec)
      //: system::system_error(ec, what_arg)
    {
      try
      {
        //m_imp_ptr.reset(new m_imp);
      }
      catch (...) { /*m_imp_ptr.reset();*/ }
    }

  private:
    struct m_imp
    {
     // path         m_path1; // may be empty()
     // path         m_path2; // may be empty()
      std::string  m_what;  // not built until needed
    };
    //boost::shared_ptr<m_imp> m_imp_ptr;

  };

#endif // HUMBUG_FS_FILELOADER_H
