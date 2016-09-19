
#include "stdafx.h"
//
#include "FileDetector.h"

#include <iostream>
#include <fstream>
#include <string.h>
//
#include <debug.h>

namespace HumbugLIB_NAMESPACE {

FileDetector::FileDetector(const std::string & filename) {
  
  std::ifstream input_file;
  input_file.open( filename.c_str() );
  m_type = identify(input_file);
  input_file.close();
}

FileDetector::~FileDetector(){
}

FileDetector::FileType FileDetector::identify(std::ifstream & input_file) {
        char buf[11];

        if( !input_file ) {
            _DEBUG_CERR("Error opening input stream");
            return ftError;
        }

        memset( buf, 0, sizeof(buf) );
        input_file.read( buf, sizeof(buf) - 1 );

        if( input_file.bad() ) {
            _DEBUG_CERR("Error reading data");
            return ftError;
        }

        _DEBUG_COUT("Data: [" << buf << "]");

        if(buf[0] == 'P' && buf[1] == 'K') {
            _DEBUG_COUT("ftZip" );
            return ftZip;
        }

        if(buf[0] == 'R' && buf[1] == 'a'&& buf[2] == 'r'&& buf[3] == '!') {
            _DEBUG_COUT("ftRar");
            return ftRar;
        }

        bool istext = true;

        for(int i = 0; i < sizeof(buf) - 1; i++)
            if(isgraph(buf[i]) == 0 && buf[i] != ' ' )
                istext = false;

        if(istext) {
            _DEBUG_COUT("ftText");
            return ftText;
        }

        _DEBUG_COUT("ftUnknown");
        return ftUnknown;
}


HumbugLIB_END_NAMESPACE
