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
#ifndef HUMBUG_GUI_TILEENGINE_CTILESET_H
#define HUMBUG_GUI_TILEENGINE_CTILESET_H
#include "../Components/Point.h"
#include "../Components/Rectangle.h"
#include "TileImage.h"
#include <string>
class CCanvas;


class CTileSet {
public:

    /*CTileSet( CCanvas * mainCanvas, CImage * sprImage, CCanvas * background = NULL,
            CRectangle spriteDimension = CRectangle(0, 0, 0,
                    0),
            CPoint spriteMove = CPoint(0, 0) );*/
    CTileSet( CCanvas * mainCanvas, /*const*/ CTileImage* tileImage, CCanvas * background, CRectangle screen);
    ~CTileSet();
    void Draw();

    void SetPos(CPoint& pos);

    void SprOffset(int offset);

    friend std::ostream& operator<<(std::ostream& o, const CTileSet& r);

private:

   /*const*/ CTileImage* m_ctiTileImage;
   CCanvas* m_pMainCanvas;
   CCanvas* m_pBackground;
   CRectangle m_crScreen;
};
std::ostream& operator<<(std::ostream& o, const CTileSet& r);

#endif // HUMBUG_GUI_TILEENGINE_CTILESET_H guard
