#ifndef HUMBUG_FS_FILELOADER_H
#define HUMBUG_FS_FILELOADER_H
#include <boost/shared_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <string>
class FileLoader {
public:

    FileLoader(const std::string & basepath);
    ~FileLoader();
    const char * language(int x) const;

    void Load(const std::string & filename) const;

    SDL_Surface * LoadImg(const std::string & filename) const;

private:

    std::string m_pBasepath;
};
#define HUMBUG_FILELOADER_THROW(EX) \
    throw EX
class FileLoaderException : public boost::system::system_error {
    // see http://www.boost.org/more/error_handling.html for design rationale
    // all functions are inline to avoid issues with crossing dll boundaries

public:

    // compiler generates copy constructor and copy assignment
    FileLoaderException(
            const std::string & what_arg, boost::system::error_code ec) :
        boost::system::system_error(ec, what_arg){
        try
        {
            m_imp_ptr.reset(new m_imp);
        }
        catch (...) { m_imp_ptr.reset();
        }
    }

    FileLoaderException(
            const std::string & what_arg, const std::string& path1_arg,
            boost::system::error_code ec) :
        boost::system::system_error(ec, what_arg){
        try
        {
            m_imp_ptr.reset(new m_imp);
            m_imp_ptr->m_path1 = path1_arg;
        }
        catch (...) { m_imp_ptr.reset();
        }
    }

    FileLoaderException(
            const std::string & what_arg, const std::string& path1_arg,
            const std::string& path2_arg, boost::system::error_code ec) :
        boost::system::system_error(ec, what_arg){
        try
        {
            m_imp_ptr.reset(new m_imp);
            m_imp_ptr->m_path1 = path1_arg;
            m_imp_ptr->m_path2 = path2_arg;
        }
        catch (...) { m_imp_ptr.reset(); }
    }

    FileLoaderException(            const std::string & what_arg, int ec) :
        boost::system::system_error(boost::system::error_code(ec, boost::system::system_category()), ""){
        try
        {
            m_imp_ptr.reset(new m_imp);
            m_imp_ptr->m_what = what_arg;
            //m_imp_ptr->m_path1 = path1_arg;
            //m_imp_ptr->m_path2 = path2_arg;
        }
        catch (...) { m_imp_ptr.reset(); }
    }

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
    throw(){
        if ( !m_imp_ptr.get() ) {
            return boost::system::system_error::what();
        }

        try
        {
            if ( m_imp_ptr->m_what.empty() ) {
                m_imp_ptr->m_what = boost::system::system_error::what();

                if ( !m_imp_ptr->m_path1.empty() ) {
                    m_imp_ptr->m_what += ": \"";
                    m_imp_ptr->m_what += m_imp_ptr->m_path1;
                    m_imp_ptr->m_what += "\"";
                }

                if ( !m_imp_ptr->m_path2.empty() ) {
                    m_imp_ptr->m_what += ", \"";
                    m_imp_ptr->m_what += m_imp_ptr->m_path2;
                    m_imp_ptr->m_what += "\"";
                }
            }

            return m_imp_ptr->m_what.c_str();
        }
        catch (...)
        {
            return boost::system::system_error::what();
        }
    } // what

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
