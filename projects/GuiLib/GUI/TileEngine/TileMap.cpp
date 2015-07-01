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
#if _MSC_VER >= 1800
	// Todo: Temporary VS2013 build fix
	bool operator!=(const std::istringstream::_Mybase& lhs, const std::istringstream::_Mysb::int_type& rhs)
	{
		//return !(lhs == rhs);
		return false;
	}

	bool operator!=(const std::basic_istream<char>::_Myt& lhs, const std::basic_istream<char>::int_type& rhs);
#endif

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

              while (htstrstr.read( const_cast<char *>(&buf[len]), sizeof(char) ) != 0)
              {
                  if (buf[len] == 0) {
                      break;
                  }
	              if (buf[len] == '(') {
		              continue;
	              }
	              if (buf[len] == ')') {
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

              item >> tileNumber;
              item >> tmp;
              item >> boundMapValue;

              htstrstr >> tmp;


			  unsigned int index = (h * m_MapWidth) + w;
              m_TileNumbers[index] = tileNumber;
              m_BoundMapValues[index] = boundMapValue;
          }
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
      char* dataPtr = reinterpret_cast<char *>(&data);

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

      while (buffer.read( const_cast<char *>(&byte1[len]), sizeof(char) ) != 0)
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

	  //background->Clear(background->GetColorKey());
	  //SDL_SetAlpha(background->GetSurface(), SDL_SRCALPHA, 128);
	  //tileSet.GetTileImage()->SetColorKey(background->GetColorKey());
	  //SDL_SetAlpha(tileSet.GetTileImage()->GetSurface(), SDL_SRCALPHA, 128);
	  //SDL_SetAlpha(background->GetSurface(), SDL_SRCALPHA, 128);
	  //SDL_SetColorKey(background->GetSurface(), SDL_SRCCOLORKEY, 0x000000);
	  //background->Clear(CColor::Black());
	  //background->SetColorKey(CColor::Black());

      for (unsigned int h = 0; h < m_MapHeight; h++)
      {
          for (unsigned int w = 0; w < m_MapWidth; w++)
          {
			  unsigned int index = (h * m_MapWidth) + w;
			  int tileNumber = m_TileNumbers[index];
			  if (tileNumber <= 0) 
			  {
				  // Todo minus check, exception ...
				  continue;
			  }

			  /*if (tileNumber > 8) 
			  {
				  x++;
			  }*/

			  // Todo: maybe cache the tiles.
			  CTile tile = tileSet.CreateTile(tileNumber - 1);

			  CPoint pos(w * 32, h * 32);
			  tile.Draw(background, pos);

			  int boundMapValue = m_BoundMapValues[index];
			  int y = tileNumber + boundMapValue;
		  }
      }
  }
}
