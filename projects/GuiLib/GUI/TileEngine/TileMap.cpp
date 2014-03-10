//
#include "stdafx.h"

//
#include "../Components/Canvas.h"
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "TileMap.h"
//#include <stdint.h>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/cstdint.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>

namespace gui {
  CTileMap::CTileMap( const std::string& mapData )
      : m_TileSet(NULL), m_MapWidth(0), m_MapHeight(0), m_MapIdentifier(""), m_TileSetIdentifier(""){
      /*std::stringstream htstrstr(mapData);

         uint16_t TileCount1, TileWidth1, TileHeight1;
         htstrstr >> TileCount1 >> TileWidth1 >> TileHeight1;

         uint32_t dummy1x, dummy2x, dummy3x, dummy4x, dummy5x;
         htstrstr >> dummy1x;
         htstrstr >> dummy2x;
         htstrstr >> dummy3x;
         htstrstr >> dummy4x;
         htstrstr >> dummy5x;


         std::string TileSetIdentifier1;
         htstrstr >> TileSetIdentifier1;*/

      std::istringstream htstrstr(mapData);

      htstrstr >> m_MapWidth >> m_MapHeight;
      htstrstr >> m_MapIdentifier;
      htstrstr >> m_TileSetIdentifier;

      //std::tr1::array<int,3,4> myarray;

      m_TileNumbers = new int[m_MapWidth * m_MapHeight];
      m_BoundMapValues = new int[m_MapWidth * m_MapHeight];

      for (unsigned int h = 0; h < m_MapHeight; h++)
      {
          std::string tmp;

          for (unsigned int w = 0; w < m_MapWidth; w++)
          {
              char buf[256];
              size_t len = 0;

              while (htstrstr.read( (char *)&buf[len], sizeof(char) ) != 0)
              {
                  if (buf[len] == 0) {
                      break;
                  }
                  else if (buf[len] == '(') {
                      continue;
                  }
                  else if (buf[len] == ')') {
                      break;
                  }

                  len++;

                  if ( len > sizeof(buf) ) {
                      break;
                  }
              }
              std::istringstream item(buf);

              int tileNumber;
              int boundMapValue;

              //item >> tmp;
              item >> tileNumber;
              item >> tmp;
              item >> boundMapValue;
              //item >> tmp;

              htstrstr >> tmp;

              m_TileNumbers[h * m_MapHeight + w] = tileNumber;
              m_BoundMapValues[h * m_MapHeight + w] = boundMapValue;
          }
          //htstrstr >> tmp;
          //htstrstr >> tmp;
      }
  }

  CTileMap::~CTileMap()
  {
	  delete[] m_TileNumbers;
	  delete[] m_BoundMapValues;
  }

  /** $(class), ReadBinary:
   *  Detailed description.
   *  @param tilesdata TODO
   * @param length TODO
   * @return TODO
   */
  void CTileMap::ReadBinary( char* tilesdata, size_t length ){
      //char buf[4096];
      /*for (int i = 0; i < finf.Size() ; i++)
         {
              buf[i] = tilesdata[i];
         }*/

      uint16_t data[] = {1234, 5678};
      char* dataPtr = (char *)&data;

      /*typedef boost::iostreams::basic_array_sink<char> ODevice;
         boost::iostreams::stream_buffer<ODevice> obuffer(buf, sizeof(buf));
         boost::archive::binary_oarchive oarchive(obuffer, boost::archive::no_header);

         std::basic_string<char> identifier("TheString");
         oarchive << identifier;*/

      /*char wbuffer[4096];

         boost::iostreams::basic_array_sink<char> sr(wbuffer, sizeof(wbuffer));
         boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source(sr);

         boost::archive::binary_oarchive oa(source);
         oa << identifier;*/

      typedef boost::iostreams::basic_array_source<char> Device;
      //boost::iostreams::stream_buffer<Device> buffer(dataPtr, sizeof(data));
      boost::iostreams::stream<Device> buffer(tilesdata, length);
      boost::archive::binary_iarchive archive(buffer, boost::archive::no_header);

      uint16_t TileCount, TileWidth, TileHeight;
      archive >> TileCount >> TileWidth >> TileHeight;
      //std::cout << word1 << "," << word2 << std::endl;

      uint16_t dummy1, dummy2, dummy3, dummy4, dummy5;
      archive >> dummy1 >> dummy2 >> dummy3 >> dummy4 >> dummy5;
      //std::string TileSetIdentifier;
      std::basic_string<char> TileSetIdentifier;
      //archive >> TileSetIdentifier;
      //byte byte1[256];
      char byte1[256];
      size_t len = 0;

      while (buffer.read( (char *)&byte1[len], sizeof(char) ) != 0)
      {
          if (byte1[len] == 0) {
              break;
          }

          len++;

          if ( len > sizeof(byte1) ) {
              break;
          }
      }
      //std::basic_string<uint8_t> bla(byte1);
      std::string bla(byte1);
  } // CTileMap::ReadBinary

  /** $(class), Draw:
   *  Detailed description.
   *  @param tileSet TODO
   * @return TODO
   */
  void CTileMap::Draw( CTileSet& tileSet, CCanvas* background, const CPoint& position ){
      //CTile tile = tileSet.CreateTile(0);
      //tileSet.Draw(tile);


      for (unsigned int h = 0; h < m_MapHeight; h++)
      {
          for (unsigned int w = 0; w < m_MapWidth; w++)
          {
			  int tileNumber = m_TileNumbers[h * m_MapHeight + w];
			  if (tileNumber <= 0) 
			  {
				  // Todo minus check, exception ...
				  continue;
			  }

			  // Todo: maybe cache the tiles.
			  CTile tile = tileSet.CreateTile(tileNumber - 1);

			  CPoint pos(w * 32, h * 32);
			  tile.Draw(background, pos);

			  int boundMapValue = m_BoundMapValues[h * m_MapHeight + w];
			  int y = tileNumber + boundMapValue;
		  }
      }
  }
}
