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
#include "..\Components\Rectangle.h"
#include <string>

//using CCanvas=gui::components::CCanvas;

namespace gui { namespace components {
	class CCanvas;
	class CImage;
}}
class FileLoader;

namespace gui {

class CSprite {
public:

	CSprite( gui::components::CCanvas * mainCanvas, gui::components::CImage * sprImage, gui::components::CCanvas * background = NULL, bool freeSrc = false,
            gui::components::CRectangle spriteDimension = gui::components::CRectangle(0, 0, 0,
                    0),
            gui::components::CPoint spriteMove = gui::components::CPoint(0, 0) );
    CSprite( FileLoader& loader, std::string filename, gui::components::CCanvas * mainCanvas,
            gui::components::CRectangle spriteDimension = gui::components::CRectangle(0, 0, 0,
                    0),
            gui::components::CPoint spriteMove = gui::components::CPoint(0, 0) );
    ~CSprite();
    void Draw();

    void SetPos(gui::components::CPoint pos);

    void SprOffset(int offset);

    gui::components::CImage* SprImage() const { return m_pSprImage; }
    void SetColorAndAlpha(Uint32 key, Uint8 alpha);

    friend std::ostream& operator<<(std::ostream& o, const CSprite& r);


private:

    gui::components::CImage* m_pSprImage;
    gui::components::CCanvas* m_pMainCanvas;
    gui::components::CCanvas* m_pBackground;
    gui::components::CPoint m_cpPos;
    gui::components::CPoint m_cpOldPos;
    gui::components::CPoint m_cpSprMove;
    gui::components::CRectangle m_crSprDim;
    bool m_bOwner;
};
std::ostream& operator<<(std::ostream& o, const CSprite& r);
}
#endif // HUMBUG_GUI_SPRITE_CSPRITE_H guard
