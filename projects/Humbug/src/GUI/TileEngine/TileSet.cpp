//
#include "stdafx.h"

//
#include "../Components/Canvas.h"
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "TileSet.h"

CTileSet::CTileSet( const CCanvas * mainCanvas, CTileImage* tileImage, const CCanvas * background, CRectangle screen )
:  m_pMainCanvas(mainCanvas),
m_ctiTileImage(tileImage),
    m_pBackground(background),
    m_crScreen(screen){
   dbgOut(__FUNCTION__ << std::endl);
   // m_pSprImage(sprImage),
}


CTileSet::~CTileSet(void){
    delete m_ctiTileImage;
    m_ctiTileImage = NULL;
    dbgOut(__FUNCTION__ << std::endl);
}

void CTileSet::Draw(const CTile& tile){

    if (m_pBackground) {
        m_pBackground->Lock();
        //CRectangle updrectA = m_pSprImage->GetCanvas()->GetDimension() + m_cpPos;
        //CRectangle updrect = m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos;

        //CRectangle updrectR = updrect.Intersect(updrectA);
        //CRectangle updrect = m_pMainCanvas->GetDimension().Clip(CRectangle(0,0,1024, 768 - 314));
        // Todo: Use the hud size as parameter.
        //CRectangle updrect = m_pMainCanvas->GetDimension().Offset(CPoint(0,-314));
        //m_pBackground->Blit(updrect, *m_pMainCanvas, updrect);
//        m_pMainCanvas->Blit(updrect, *m_pBackground, updrect);
        //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
        //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);
        //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), m_ctiTileImage, m_ctiTileImage->GetDimension());
        // m_ctiTileImage->Draw(m_pBackground);
        m_pBackground->Unlock();
    }

    //m_pMainCanvas->FillRect(bluerectOld, CColor(0, 0, 0) );
    //CPoint spos( m_cpPos.GetX(), m_cpPos.GetY());
    //SDL_SetAlpha(m_pSprImage->GetCanvas()->GetSurface(), SDL_SRCALPHA , 128);
    //m_pSprImage->Put(m_pMainCanvas, m_cpPos);

    //m_pMainCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
    //m_pMainCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);
    //m_pMainCanvas->AddUpdateRect(m_pSprImage->DstRect() + m_cpOldPos);
    //m_pMainCanvas->AddUpdateRect(m_pSprImage->DstRect() + m_cpPos);
    //m_cpOldPos = m_cpPos;
} // Draw

CTile CTileSet::CreateTile( int index ) const
{
    return CTile(*m_ctiTileImage ,index);
}

std::ostream& operator<<(std::ostream& o, const CTileSet& r) {
    return o << "CTileSet[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                 << ", W=" << r.GetW() << ", H=" << r.GetH()
                                 <<*/" ]";
}

