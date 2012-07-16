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
#ifndef HUMBUG_GUI_SPRITE_CSPRITE_H
#define HUMBUG_GUI_SPRITE_CSPRITE_H
#include "..\Components\Point.h"
#include <string>
class CCanvas;
class CImage;
class FileLoader;
class CSprite {
public:

    CSprite( CCanvas * mainCanvas, CImage * sprImage, CCanvas * background = NULL,
            CRectangle spriteDimension = CRectangle(0, 0, 0,
                    0),
            CPoint spriteMove = CPoint(0, 0) );
    CSprite( const FileLoader& loader, std::string filename, CCanvas * mainCanvas,
            CRectangle spriteDimension = CRectangle(0, 0, 0,
                    0),
            CPoint spriteMove = CPoint(0, 0) );
    ~CSprite();
    void Draw();

    void SetPos(CPoint& pos);

    void SprOffset(int offset);

    friend std::ostream& operator<<(std::ostream& o, const CSprite& r);

    CImage* m_pSprImage;

private:

    CCanvas* m_pMainCanvas;
    CCanvas* m_pBackground;
    CCanvas* m_pCanvas;
    CPoint m_cpPos;
    CPoint m_cpOldPos;
    CPoint m_cpSprMove;
    CRectangle m_crSprDim;
    bool m_bOwner;
};
std::ostream& operator<<(std::ostream& o, const CSprite& r);

#endif // HUMBUG_GUI_SPRITE_CSPRITE_H guard
