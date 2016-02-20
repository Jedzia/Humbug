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
#include "../Components/Point.h"
#include "../Components/Rectangle.h"
#include "../Components//BaseDrawable.h"
#include <string>

//using CCanvas=gui::components::CCanvas;
namespace gui
{
  namespace components
  {
    class CCanvas;
    class CImage;
  }
}
class FileLoader;

//
namespace gui
{
  /// Represents a two-dimensional image or animation.
  /** Hold function to bla bla bla. */
  class CSprite : public components::BaseDrawable{
public:

    CSprite(components::CCanvas* mainCanvas, components::CImage* sprImage, components::CCanvas* spriteCanvas = NULL, bool freeSrc = false
        , components::CRectangle spriteDimension = components::CRectangle(0, 0, 0,0)
        , components::CPoint spriteMove = components::CPoint(0, 0));

    CSprite(FileLoader& loader, std::string filename, components::CCanvas* mainCanvas
        , components::CPoint spriteMove = components::CPoint(0, 0)
        , components::CRectangle spriteDimension = components::CRectangle(0, 0, 0, 0)
        );
      ~CSprite();

      void Draw();

      void SetSpriteOffset(int offset);
      int GetSpriteOffset() const { return m_iOffset; }
      
      void SetHitBox(const components::CRectangle& hitbox);
      components::CRectangle GetPaintHitbox() const;

      /** Brief description which ends at this dot. Details follow
       *  here.
       */
      components::CImage * SprImage() const { return m_pSprImage; }

      void SetColorAndAlpha(Uint32 key, Uint8 alpha);

      friend std::ostream& operator<<(std::ostream& o, const CSprite& r);
      void Render();

      components::CRectangle SpriteDimension() const;
      components::CRectangle PaintDimension() const;
      components::CRectangle PaintLocation() const;

  private:

      components::CImage* m_pSprImage;
      components::CCanvas* m_pPaintCanvas;
      components::CCanvas* m_pBackground;
      //CPoint m_cpPos;
      components::CPoint m_cpOldPos;
      components::CPoint m_cpSprMove;
      components::CRectangle m_crSprDim;
      components::CRectangle m_crHitbox;
      int m_iOffset;
      bool m_bOwner;
  };

  std::ostream& operator<<(std::ostream& o, const CSprite& r);
}
#endif // HUMBUG_GUI_SPRITE_CSPRITE_H guard
