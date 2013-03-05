//
#include "stdafx.h"

//
#include "../Components/Canvas.h"
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "SeamlessImage.h"

//#include <build/cmake/include/debug.h>
using namespace gui::components;
namespace gui
{
// freeSrc: Take ownership of 'sprImage' and delete it on destruction.
  CSeamlessImage::CSeamlessImage(CCanvas* mainCanvas, CImage* sprImage, CCanvas* background, bool freeSrc,
          CRectangle SeamlessImageDimension,
          CPoint SeamlessImageMove) :
      m_bOwner(freeSrc),
      m_pMainCanvas(mainCanvas),
      m_pSprImage(sprImage),
      m_pBackground(background),
      m_cpPos(0, 0),
      m_cpOldPos(0, 0),
      m_cpSprMove(SeamlessImageMove),
      m_crSprDim(SeamlessImageDimension){
      dbgOut(__FUNCTION__ << std::endl);

      //m_cpSprDim.SetX(sprImage->SrcRect().GetW());
      //m_cpSprDim.SetY(sprImage->SrcRect().GetH());
  }

  CSeamlessImage::CSeamlessImage( FileLoader& loader, std::string filename, CCanvas* mainCanvas,
          CRectangle SeamlessImageDimension /*= CRectangle(0,0,0,0) */,
          CPoint SeamlessImageMove /*= CPoint(0,0) */ ) :
      m_bOwner(true),
      m_pMainCanvas(mainCanvas),
      m_pBackground(NULL),
      m_cpPos(0, 0),
      m_cpOldPos(0, 0),
      m_cpSprMove(SeamlessImageMove),
      m_crSprDim(SeamlessImageDimension){
      // m_pSprImage(sprImage),
      SDL_Surface* alphasurf = SDL_DisplayFormatAlpha( loader.LoadImg(filename) );

      // free the loaded surface.
      loader.FreeLast();

      if ( SeamlessImageDimension == CRectangle(0, 0, 0, 0) ) {
          m_pSprImage = new CImage( new CCanvas( alphasurf ), true );
          m_crSprDim = m_pSprImage->SrcRect();
      }
      else {
          m_pSprImage = new CImage( new CCanvas( alphasurf ), SeamlessImageDimension, true );
      }
  }

  CSeamlessImage::~CSeamlessImage(void){
      if(m_bOwner) {
          delete m_pSprImage;
      }

      dbgOut(__FUNCTION__ << std::endl);
  }

  /** CSeamlessImage, Draw:
   *  Detailed description.
   *  @return TODO
   */
  void CSeamlessImage::Draw(){
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

  /** CSeamlessImage, SetPos:
   *  Detailed description.
   *  @param position TODO
   * @return TODO
   */
  void CSeamlessImage::SetPos( CPoint position ){
      m_cpPos = position;
  }

  /** CSeamlessImage, SprOffset:
   *  Detailed description.
   *  @param offset TODO
   * @return TODO
   */
  void CSeamlessImage::SprOffset( int offset ){
      m_pSprImage->SrcRect() = m_crSprDim.Move(m_cpSprMove * offset);
  }

  /** CSeamlessImage, SetColorAndAlpha:
   *  Detailed description.
   *  @param key TODO
   * @param alpha TODO
   * @return TODO
   */
  void CSeamlessImage::SetColorAndAlpha( Uint32 key, Uint8 alpha ){
      SDL_Surface* alphasurf = m_pSprImage->GetCanvas()->GetSurface();
      SDL_SetColorKey(alphasurf, SDL_SRCCOLORKEY, key);
      SDL_SetAlpha(alphasurf, 0, alpha);
  }

  /** $(fclass), operator <<:
   *  Detailed description.
   *  @param o TODO
   * @param r TODO
   * @return TODO
   */
  std::ostream& operator<<(std::ostream& o, const CSeamlessImage& r) {
      return o << "CSeamlessImage[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                   << ", W=" << r.GetW() << ", H=" << r.GetH()
                                   <<*/
             " ]";
  }
}
