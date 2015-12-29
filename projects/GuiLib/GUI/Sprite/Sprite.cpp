//
#include "stdafx.h"

//
#include "../Components/Canvas.h"
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "Sprite.h"

//#include <build/cmake/include/debug.h>
using namespace gui::components;
namespace gui
{
// freeSrc: Take ownership of 'sprImage' and delete it on destruction.
  CSprite::CSprite(CCanvas* mainCanvas, CImage* sprImage, CCanvas* background, bool freeSrc,
          CRectangle spriteDimension,
          CPoint spriteMove) :
      m_bOwner(freeSrc),
      m_pMainCanvas(mainCanvas),
      m_pSprImage(sprImage),
      m_pBackground(background),
      m_cpPos(0, 0),
      m_cpOldPos(0, 0),
      m_cpSprMove(spriteMove),
      m_crSprDim(spriteDimension){
      dbgOut(__FUNCTION__);

      //m_cpSprDim.SetX(sprImage->SrcRect().GetW());
      //m_cpSprDim.SetY(sprImage->SrcRect().GetH());
  }

  CSprite::CSprite( FileLoader& loader, std::string filename, CCanvas* mainCanvas,
          CRectangle spriteDimension /*= CRectangle(0,0,0,0) */,
          CPoint spriteMove /*= CPoint(0,0) */ ) :
      m_bOwner(true),
      m_pMainCanvas(mainCanvas),
      m_pBackground(NULL),
      m_cpPos(0, 0),
      m_cpOldPos(0, 0),
      m_cpSprMove(spriteMove),
      m_crSprDim(spriteDimension){
      // m_pSprImage(sprImage),
      SDL_Surface* alphasurf = ( loader.FL_LOADIMG(filename) );

      // free the loaded surface.
      loader.FreeLast();

      if ( spriteDimension == CRectangle(0, 0, 0, 0) ) {
          m_pSprImage = new CImage( new CCanvas( alphasurf ), true );
          m_crSprDim = m_pSprImage->SrcRect();
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
      m_pMainCanvas->Lock();

      if (m_pBackground) {
          //CRectangle updrectA = m_pSprImage->GetCanvas()->GetDimension() + m_cpPos;
          CRectangle updrect = m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos;

          //CRectangle updrectR = updrect.Intersect(updrectA);
          //CRectangle updrect = m_pMainCanvas->GetDimension().Clip(CRectangle(0,0,1024, 768 -
          // 314));
          // Todo: Use the hud size as parameter.
          //CRectangle updrect = m_pMainCanvas->GetDimension().Offset(CPoint(0,-314));
          //m_pBackground->Blit(updrect, *m_pMainCanvas, updrect);
//        m_pMainCanvas->Blit(updrect, *m_pBackground, updrect);
          //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
          //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);
      }

      //m_pMainCanvas->FillRect(bluerectOld, CColor(0, 0, 0) );
      //CPoint spos( m_cpPos.GetX(), m_cpPos.GetY());
      //SDL_SetAlpha(m_pSprImage->GetCanvas()->GetSurface(), SDL_SRCALPHA /*| SDL_RLEACCEL*/,
      // 128);
      m_pSprImage->Put(m_pMainCanvas, m_cpPos);
      m_pMainCanvas->Unlock();

      //m_pMainCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
      //m_pMainCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);
      m_pMainCanvas->AddUpdateRect(m_pSprImage->DstRect() + m_cpOldPos);
      m_pMainCanvas->AddUpdateRect(m_pSprImage->DstRect() + m_cpPos);
      m_cpOldPos = m_cpPos;
  }   // Draw

  /** CSprite, SetPos:
   *  Detailed description.
   *  @param position TODO
   * @return TODO
   */
  void CSprite::SetPos( CPoint position ){
      m_cpPos = position;
  }

  /** CSprite, SprOffset:
   *  Detailed description.
   *  @param offset TODO
   * @return TODO
   */
  void CSprite::SprOffset( int offset ){
      m_pSprImage->SrcRect() = m_crSprDim.Move(m_cpSprMove * offset);
  }

  /** CSprite, SetColorAndAlpha:
   *  Detailed description.
   *  @param key TODO
   * @param alpha TODO
   * @return TODO
   */
  void CSprite::SetColorAndAlpha( Uint32 key, Uint8 alpha ){
      SDL_Surface* alphasurf = m_pSprImage->GetCanvas()->GetSurface();
      SDL_SetColorKey(alphasurf, SDL_TRUE, key);
      SDL_SetAlpha(alphasurf, 0, alpha);
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
