/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the FileLoader.cpp class.
 * \file       FileLoader.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include "FileLoader.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <HumbugGLLib/LogManager.h>

FileLoadingInfo::FileLoadingInfo(const std::string name, SDL_Surface* surface)
    : m_strName(name), m_pSurface(surface), m_pFont(NULL), m_pArea(NULL), m_pData(NULL), m_fsize(0), m_refcount(0){
    LOGSTREAM << "FileLoadingInfo create SDL_Surface '" << *this << "'";
}

FileLoadingInfo::FileLoadingInfo( const std::string name, TTF_Font* font, SDL_RWops* area, char* data, int fsize )
    : m_strName(name), m_pSurface(NULL), m_pFont(font), m_pArea(area), m_pData(data), m_fsize(fsize), m_refcount(0){
    LOGSTREAM << "FileLoadingInfo create Memdata '" << *this << "'";
}

FileLoadingInfo::FileLoadingInfo( const std::string name, char* data, int fsize )
    : m_strName(name), m_pSurface(NULL), m_pFont(NULL), m_pArea(NULL), m_pData(data), m_fsize(fsize), m_refcount(0){
    LOGSTREAM << "FileLoadingInfo create Memdata '" << *this << "'";
}

FileLoadingInfo::~FileLoadingInfo(){
    LOGSTREAM << "FileLoadingInfo freeing '" << *this << "'";

    if(m_pSurface) {
        SDL_FreeSurface(m_pSurface);
        m_pSurface = NULL;
    }
    else if(m_pFont) {
        TTF_CloseFont( m_pFont );
        m_pFont = NULL;
        //SDL_FreeRW(m_pArea);
        //m_pArea = NULL;
        delete[] m_pData;
        m_pData = NULL;
    }
    else if(m_pData) {
        delete[] m_pData;
        m_pData = NULL;
    }
}

FileLoadingInfo& FileLoadingInfo::operator++( int ){
    m_refcount++;
    return *this;
}

FileLoadingInfo& FileLoadingInfo::operator--( int ){
    m_refcount--;
    return *this;
}

std::ostream& operator<<( std::ostream& o, const FileLoadingInfo& r ){
    return o << "FileLoadingInfo[ (" << r.GetRefcount() << ")Name='" << r.GetName() << "', Loc=" << r.GetLocation() <<
           ", Font=" << r.GetFont() << ", rWops=" << r.m_pArea
             <<
           " ]";
}

FileLoader::FileLoader(const std::string & basepath)
    : m_pBasepath(basepath), m_pLastLoaded(""){
    using namespace humbuglib;
    dbgOut(__FUNCTION__);
    LogManager::getSingleton().logMessage("Creating FileLoader for '" + basepath + "'.");
    LogManager::getSingleton().stream() << "Logging from Stream.";
}

/// <summary>
/// Finalizes an instance of the <see cref="FileLoader"/> class.
/// </summary>
FileLoader::~FileLoader(void){
    dbgOut(__FUNCTION__);
    humbuglib::LogManager::getSingleton().stream() << __FUNCTION__ << " Logging from Stream.";
}

/// <summary>
/// Dummy test method.
/// </summary>
/// <param name="x">The x.</param>
/// <returns>const char *.</returns>
const char * FileLoader::language(int x) const {
    return "AsciiDoc";
}

void FileLoader::FreeLast(){
    //boost::ptr_vector<FileLoadingInfo>::auto_type current(m_pvSurfaces.pop_back());
    // LOGSTREAM << "FileLoader freeing '" << current->GetName() << "'";
    LOGSTREAM << "FileLoader freeing 'FreeLast'";
    //std::string nase = f->GetName();

    if (m_pLastLoaded == "") {
        return;
        //SDL_FreeSurface(m_pLastSurface);
    }

    boost::ptr_map<std::string, FileLoadingInfo>::iterator rexs1 = m_resMap.find(m_pLastLoaded);

    if ( rexs1 != m_resMap.end() ) {
        FileLoadingInfo& finf = *(rexs1->second);
        LOGSTREAM << "FileLoader FreeLast found Cached '" << finf << "'";
    }
    else {
        LOGSTREAM << "FileLoader FreeLast NOT found Cached '" << m_pLastLoaded << "' atom.";
    }
} // FileLoader::FreeLast

void FileLoader::Free( const std::string& name ){
    LOGSTREAM << "FileLoader freeing by name (OOPS not implemented...) '" << name << "'";

    /*surfacevector::pointer result = NULL;
       surfacevector::iterator end = m_pvSurfaces.end();
       for (surfacevector::iterator it = m_pvSurfaces.begin(); it < end ; ++it)
       {
        FileLoadingInfo& current = (*it);
        if (current.GetName().compare(name))
        {
                        //LOGSTREAM << "FileLoader freeing '" << current.GetName() << "'";
                        LOGSTREAM << "FileLoader freeing '" << current << "'";
            m_pvSurfaces.erase(it);
            result = &current;
        }
       }*/
    // LOGSTREAM << result->GetName();
}

const char * FileLoaderException::what() const throw(){
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
} // FileLoaderException::what

FileLoaderException::FileLoaderException( const std::string & what_arg, int ec ) :
    boost::system::system_error(boost::system::error_code( ec, boost::system::system_category() ), ""){
    try
    {
        m_imp_ptr.reset(new m_imp);
        m_imp_ptr->m_what = what_arg;
        //m_imp_ptr->m_path1 = path1_arg;
        //m_imp_ptr->m_path2 = path2_arg;
    }
    catch (...) {
        m_imp_ptr.reset();
    }
}

FileLoaderException::FileLoaderException( const std::string & what_arg, const std::string& path1_arg,
        const std::string& path2_arg, boost::system::error_code ec ) :
    boost::system::system_error(ec, what_arg){
    try
    {
        m_imp_ptr.reset(new m_imp);
        m_imp_ptr->m_path1 = path1_arg;
        m_imp_ptr->m_path2 = path2_arg;
    }
    catch (...) {
        m_imp_ptr.reset();
    }
}

FileLoaderException::FileLoaderException( const std::string & what_arg, const std::string& path1_arg,
        boost::system::error_code ec ) :
    boost::system::system_error(ec, what_arg){
    try
    {
        m_imp_ptr.reset(new m_imp);
        m_imp_ptr->m_path1 = path1_arg;
    }
    catch (...) {
        m_imp_ptr.reset();
    }
}

FileLoaderException::FileLoaderException( const std::string & what_arg, boost::system::error_code ec ) :
    boost::system::system_error(ec, what_arg){
    try
    {
        m_imp_ptr.reset(new m_imp);
    }
    catch (...) {
        m_imp_ptr.reset();
    }
}
