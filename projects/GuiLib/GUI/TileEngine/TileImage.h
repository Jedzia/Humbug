/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Sprite.h class.
 * \folder     $(folder)
 * \file       Sprite.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_GUI_TILEENGINE_CTILEIMAGE_H
#define HUMBUG_GUI_TILEENGINE_CTILEIMAGE_H
#include "../Components/Canvas.h"
#include "../Components/Point.h"
#include "Tile.h"
#include <string>

using namespace gui::components;

namespace gui { namespace components {
class CImage;
}}
class FileLoader;

namespace gui {

// configuration of a tile image.
struct CTileImageSetup
{
    std::string TileSetName;
    int TileWidth;
    int TileHeight;
    int TileCountX;
    int TileCountY;
    int TransparentX;
    int TransparentY;
    int Sequences;

//    int ** SequenceData;
//    int * SequenceLength;
//    int * SequencePosition;
//    int * SequenceCounter;
};

// info about the tile image.
struct CTileImageInfo : CTileImageSetup
{
    /*CTileImageInfo()
       {

       }*/
    int BitmapWidth;
    int BitmapHeight;
};

// The image, that holds the elements of a tile-set.
class CTileImage : CCanvas {
public:

    CTileImage( FileLoader& loader, std::string filename, CTileImageSetup configuration );
    virtual ~CTileImage();
    bool ShowTiles( CCanvas * destination, const CPoint& destPosition = CPoint(0, 0) ) const ;

    bool Draw(const CTile& tile, CCanvas * destination, const CPoint& destPosition) const ;

    const CTileImageInfo& GetConfig() const { return m_tiConfig; }
    friend std::ostream& operator<<(std::ostream& o, const CTileImage& r);

private:

    CTileImageInfo m_tiConfig;
    // for later use as shared reference counter.
    // int usage_count;
};
std::ostream& operator<<(std::ostream& o, const CTileImage& r);

}

#endif // HUMBUG_GUI_TILEENGINE_CTILEIMAGE_H guard
