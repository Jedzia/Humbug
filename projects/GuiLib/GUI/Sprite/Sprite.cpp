//
#include "stdafx.h"

//
#include "../Components/Canvas.h"
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "Sprite.h"
//
//#include <build/cmake/include/debug.h>

const bool debugFrame = true;

using namespace gui::components;
namespace gui
{
// freeSrc: Take ownership of 'sprImage' and delete it on destruction.
    CSprite::CSprite(CCanvas* mainCanvas, CImage* sprImage, CCanvas* spriteCanvas, bool freeSrc,
          CRectangle spriteDimension,
          CPoint spriteMove) : BaseDrawable(CPoint(0,0)),
                               m_pSprImage(sprImage),
                               m_pPaintCanvas(mainCanvas),
      m_pBackground(spriteCanvas),
      m_cpOldPos(0, 0),
      m_cpSprMove(spriteMove),
      m_crSprDim(spriteDimension),
      m_crHitbox(spriteDimension),
      m_iOffset(0), m_bOwner(freeSrc)
  {
      dbgOut(__FUNCTION__);

      //m_cpSprDim.SetX(sprImage->SrcRect().GetW());
      //m_cpSprDim.SetY(sprImage->SrcRect().GetH());
  }

  CSprite::CSprite( FileLoader& loader, std::string filename, CCanvas* mainCanvas,
          CPoint spriteMove,
          CRectangle spriteDimension
          ) : BaseDrawable(CPoint(0, 0)),
                                                   m_pPaintCanvas(mainCanvas),
                                                   m_pBackground(NULL),
      m_cpOldPos(0, 0),
      m_cpSprMove(spriteMove),
      m_crSprDim(spriteDimension),
      m_crHitbox(spriteDimension),
      m_iOffset(0), m_bOwner(true)
  {
      // m_pSprImage(sprImage),
      SDL_Surface* alphasurf = ( loader.FL_LOADIMG(filename) );

      // free the loaded surface.
      loader.FreeLast();

      if ( spriteDimension == CRectangle(0, 0, 0, 0) ) {
          // old, build sprite dimension from loaded surface
          //m_pSprImage = new CImage( new CCanvas( alphasurf ), true );
          //m_crSprDim = m_pSprImage->SrcRect();
          // build sprite dimension from sprite move offset
          m_crHitbox = m_crSprDim = CRectangle(0, 0, spriteMove.GetX(), spriteMove.GetY());
          m_pSprImage = new CImage(new CCanvas(alphasurf), m_crSprDim, true);
      }
      else {
          m_pSprImage = new CImage( new CCanvas( alphasurf ), spriteDimension, true );
      }
  }

  CSprite::~CSprite(void){
      if(m_bOwner) {
          delete m_pSprImage;
      }

      dbgOut(__FUNCTION__);
  }

  /** CSprite, Draw:
   *  Detailed description.
   *  @return TODO
   */
  void CSprite::Draw(){
      Render();
      return;
      m_pSprImage->RenderPut(m_pPaintCanvas, GetPosition());
      if (debugFrame)
      {
          CColor col = CColor::White();
          m_pPaintCanvas->RenderDrawRect(m_pSprImage->DstRect() + GetPosition(), &col);
      }
      //CRectangle dstrect = m_pSprImage->DstRect();
      //dstrect = dstrect / 2;
      //m_pSprImage->RenderPut(m_pPaintCanvas, dstrect + m_cpPos);
      m_cpOldPos = GetPosition();
      return;
      m_pPaintCanvas->Lock();

      if (m_pBackground) {
          //CRectangle updrectA = m_pSprImage->GetCanvas()->GetDimension() + m_cpPos;
          CRectangle updrect = m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos;

          //CRectangle updrectR = updrect.Intersect(updrectA);
          //CRectangle updrect = m_pPaintCanvas->GetDimension().Clip(CRectangle(0,0,1024, 768 -
          // 314));
          // Todo: Use the hud size as parameter.
          //CRectangle updrect = m_pPaintCanvas->GetDimension().Offset(CPoint(0,-314));
          //m_pBackground->Blit(updrect, *m_pPaintCanvas, updrect);
//        m_pPaintCanvas->Blit(updrect, *m_pBackground, updrect);
          //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
          //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);
      }

      //m_pPaintCanvas->FillRect(bluerectOld, CColor(0, 0, 0) );
      //CPoint spos( m_cpPos.GetX(), m_cpPos.GetY());
      //SDL_SetSurfaceAlphaMod(m_pSprImage->GetCanvas()->GetSurface() /*| SDL_RLEACCEL*/,
      // 128);
      m_pSprImage->Put(m_pPaintCanvas, GetPosition());
      m_pPaintCanvas->Unlock();

      //m_pPaintCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
      //m_pPaintCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);
      m_pPaintCanvas->AddUpdateRect(m_pSprImage->DstRect() + m_cpOldPos);
      m_pPaintCanvas->AddUpdateRect(m_pSprImage->DstRect() + GetPosition());
      m_cpOldPos = GetPosition();
  }   // Draw

  
  /** CSprite, SetSpriteOffset:
   *  Detailed description.
   *  @param offset TODO
   * @return TODO
   */
  void CSprite::SetSpriteOffset( int offset ){
      if (m_iOffset == offset)
      {
          return;
      }

      m_iOffset = offset;
      CRectangle fullspriteDimension = m_pSprImage->GetCanvas()->GetDimension();

      int xMove = m_cpSprMove.GetX();
      int yMove = m_cpSprMove.GetY();
      if (xMove == 0)
      {
          // old behaviour, Todo: check & remove
          m_pSprImage->SrcRect() = m_crSprDim.Move(m_cpSprMove * offset);
          return;
      }

      int xRange = fullspriteDimension.GetW() / xMove;
      //int yRange = fullspriteDimension.GetH() / yMove;
      int xOffset = offset % xRange;
      int yOffset = (offset / xRange);

      CPoint offsetPoint(xMove * xOffset, yMove * yOffset);
      m_pSprImage->SrcRect() = m_crSprDim.Move(offsetPoint);
  }

void CSprite::SetHitBox(const components::CRectangle& hitbox)
{
    m_crHitbox = hitbox;
}

components::CRectangle CSprite::GetPaintHitbox() const
{
    return m_crHitbox + GetPosition();
}

/** CSprite, SetColorAndAlpha:
         *  Detailed description.
         *  @param key TODO
         * @param alpha TODO
         * @return TODO
         */
  void CSprite::SetColorAndAlpha( Uint32 key, Uint8 alpha ){
      //SDL_Surface* alphasurf = m_pSprImage->GetCanvas()->GetSurface();
      m_pSprImage->GetCanvas()->SetColorKey(key);
      //SDL_SetColorKey(alphasurf, SDL_TRUE, key);
      //SDL_SetSurfaceAlphaMod(alphasurf, alpha);
      m_pSprImage->GetCanvas()->SetSurfaceAlphaMod(alpha);
  }

void CSprite::Render()
{
    if (debugFrame)
    {
        const CColor colbounds = CColor::White();
        //m_pPaintCanvas->RenderDrawRect(m_pSprImage->DstRect() + GetPosition(), &colbounds);
        m_pPaintCanvas->RenderDrawRect(PaintLocation(), &colbounds);
    
        CColor colhitbox = CColor::DarkRed();
        m_pPaintCanvas->RenderDrawRect(GetPaintHitbox(), &colhitbox);
    }

    m_pSprImage->RenderPut(m_pPaintCanvas, GetPosition());
    m_cpOldPos = GetPosition();
}

CRectangle CSprite::SpriteDimension() const
{
    return m_crSprDim;
}

CRectangle CSprite::PaintDimension() const
{
    return m_pSprImage->DstRect();
}

CRectangle CSprite::PaintLocation() const
{
    return m_pSprImage->DstRect() + GetPosition();
}

    /** $(fclass), operator <<:
         *  Detailed description.
         *  @param o TODO
         * @param r TODO
         * @return TODO
         */
  std::ostream& operator<<(std::ostream& o, const CSprite& r) {
      return o << "CSprite[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                   << ", W=" << r.GetW() << ", H=" << r.GetH()
                                   <<*/
             " ]";
  }
}
