/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SeamlessImage.h class.
 * \folder     $(folder)
 * \file       SeamlessImage.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_GUI_SeamlessImage_CSeamlessImage_H
#define HUMBUG_GUI_SeamlessImage_CSeamlessImage_H
#include "..\Components\Point.h"
#include "..\Components\Rectangle.h"
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
  using gui::components::CCanvas;
  using gui::components::CImage;
  using gui::components::CPoint;
  using gui::components::CRectangle;

  /// Represents a two-dimensional image or animation.
  /** Hold function to bla bla bla. */
  class CSeamlessImage {
public:

      CSeamlessImage( CCanvas* mainCanvas, CImage* sprImage, CCanvas* background = NULL, bool freeSrc = false,
              CRectangle SeamlessImageDimension = CRectangle(0, 0, 0,
                      0), CPoint SeamlessImageMove = CPoint(0, 0) );

      CSeamlessImage( FileLoader& loader, std::string filename, CCanvas* mainCanvas, CRectangle SeamlessImageDimension =
                  CRectangle(0, 0, 0, 0), CPoint SeamlessImageMove = CPoint(0, 0) );
      ~CSeamlessImage();

      void Draw();

      /** Set Screen Position.
       *  Sets the screen position of the SeamlessImage.
       *  @param position The position of the SeamlessImage on screen.
       * @return nothing.
       */
      void SetPos(CPoint pos);

      void SprOffset(int offset);

      /** Brief description which ends at this dot. Details follow
       *  here.
       */
      CImage * SprImage() const { return m_pSprImage; }

      void SetColorAndAlpha(Uint32 key, Uint8 alpha);

      friend std::ostream& operator<<(std::ostream& o, const CSeamlessImage& r);

private:

      CImage* m_pSprImage;
      CCanvas* m_pMainCanvas;
      CCanvas* m_pBackground;
      CPoint m_cpPos;
      CPoint m_cpOldPos;
      CPoint m_cpSprMove;
      CRectangle m_crSprDim;
      bool m_bOwner;
  };

  std::ostream& operator<<(std::ostream& o, const CSeamlessImage& r);
}
#endif // HUMBUG_GUI_SeamlessImage_CSeamlessImage_H guard
