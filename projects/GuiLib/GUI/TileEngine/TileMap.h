/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TileMap.h class.
 * \folder     $(folder)
 * \file       TileMap.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_GUI_TILEENGINE_CTILEMAP_H
#define HUMBUG_GUI_TILEENGINE_CTILEMAP_H
#include "TileSet.h"
#include <string>

namespace gui {
  namespace components {
    class CCanvas;
  }
}
class FileLoader;

using namespace gui::components;

namespace gui {
  /** @class CTileMap:
   *  Detailed description.
   *  @param tilesdata TODO
   * @param length TODO
   */
  class CTileMap {
public:

      CTileMap( const std::string& mapData);
      ~CTileMap();

	  void ReadBinary(char* tilesdata, size_t length);
	  
	  void Draw(CTileSet& tileSet, CCanvas* background, const CPoint& position);

      //unsigned int MapWidth() const { return m_MapWidth; }
      //unsigned int MapHeight() const { return m_MapHeight; }

      std::string MapIdentifier() const { return m_MapIdentifier; }

      /** $(class), TileSetIdentifier:
       *  Detailed description.
       *  @return TODO
       */
      std::string TileSetIdentifier() const { return m_TileSetIdentifier; }

private:

      unsigned int m_MapWidth;
      unsigned int m_MapHeight;
      std::string m_MapIdentifier;
      std::string m_TileSetIdentifier;
      int* m_TileNumbers;
      int* m_BoundMapValues;
      CTileSet* m_TileSet;
  };
}

#endif // HUMBUG_GUI_TILEENGINE_CTILEMAP_H guard
