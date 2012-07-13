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
#include "../Components/Point.h"
#include "../Components/Canvas.h"
#include "Tile.h"

#include <string>
class CImage;
class FileLoader;


struct CTileImageSetup
{
    std::string BitmapIdentifier;
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

struct CTileImageInfo : CTileImageSetup
{
    /*CTileImageInfo()
    {

    }*/

    int BitmapWidth;
    int BitmapHeight;
};



class CTileImage : CCanvas {
public:

    /*CTileImage( CCanvas * mainCanvas, CImage * sprImage, CCanvas * background = NULL,
            CRectangle spriteDimension = CRectangle(0, 0, 0,
                    0),
            CPoint spriteMove = CPoint(0, 0) );*/
    CTileImage( const FileLoader& loader, std::string filename,
            CTileImageSetup configuration );
    ~CTileImage();

    bool ShowTiles( CCanvas* destination, const CPoint& destPosition = CPoint(0,0) );
    bool Draw(const CTile& tile, CCanvas* destination, const CPoint& destPosition);

    friend std::ostream& operator<<(std::ostream& o, const CTileImage& r);
private:

    CTileImageInfo m_tiConfig;
    // for later use as shared reference counter.
    // int usage_count;
};
std::ostream& operator<<(std::ostream& o, const CTileImage& r);

#endif // HUMBUG_GUI_TILEENGINE_CTILEIMAGE_H guard
