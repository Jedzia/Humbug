/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TileSet.h class.
 * \folder     $(folder)
 * \file       TileSet.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_GUI_TILEENGINE_CTILESET_H
#define HUMBUG_GUI_TILEENGINE_CTILESET_H
#include "../Components/Point.h"
#include "../Components/Rectangle.h"
#include "Tile.h"
#include "TileImage.h"
#include <string>

namespace gui {
  namespace components {
    class CCanvas;
  }
}
class FileLoader;

using namespace gui::components;

namespace gui {
  /** @class CTileSet:
   *  Detailed description.
   *  @param index TODO
   * @return TODO
   */
  class CTileSet {
public:

      CTileSet( const CCanvas* mainCanvas, CTileImage* tileImage, const CCanvas* background, CRectangle screen);
      ~CTileSet();
      CTile CreateTile(int index) const;

      /** $(class), GetTileImage:
       *  Detailed description.
       *  @return TODO
       */
      inline const CTileImage * GetTileImage() const { return m_ctiTileImage; }

      friend std::ostream& operator<<(std::ostream& o, const CTileSet& r);

protected:

      // Todo: DeleteME
      void Draw(const CTile& tile);

private:

      const CTileImage* m_ctiTileImage;
      const CCanvas* m_pMainCanvas;
      const CCanvas* m_pBackground;
      CRectangle m_crScreen;
  };

  std::ostream& operator<<(std::ostream& o, const CTileSet& r);
}

#endif // HUMBUG_GUI_TILEENGINE_CTILESET_H guard
