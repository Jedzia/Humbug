//
#include "stdafx.h"
//
#include "Sprite.h"
#include "SDL.h"
#include "../Components/Image.h"
#include "../Components/Canvas.h"

//#include <build/cmake/include/debug.h>


CSprite::CSprite(CCanvas* mainCanvas, CImage* sprImage, CCanvas* background)
: m_pMainCanvas(mainCanvas), m_pSprImage(sprImage), m_pBackground(background), m_cpPos(0,0), m_cpOldPos(0,0)
{
         dbgOut(__FUNCTION__ << std::endl);
}

CSprite::~CSprite(void)
{
         dbgOut(__FUNCTION__ << std::endl);
}

void CSprite::Draw() 
{
    m_pMainCanvas->Lock();

    if (m_pBackground)
    {
        //CRectangle updrectA = m_pSprImage->GetCanvas()->GetDimension() + m_cpPos;
        CRectangle updrect = m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos;
        //CRectangle updrectR = updrect.Intersect(updrectA);
        //CRectangle updrect = m_pMainCanvas->GetDimension().Clip(CRectangle(0,0,1024, 768 - 314));
        // Todo: Use the hud size as parameter.
        //CRectangle updrect = m_pMainCanvas->GetDimension().Offset(CPoint(0,-314));
        //m_pBackground->Blit(updrect, *m_pMainCanvas, updrect);
//        m_pMainCanvas->Blit(updrect, *m_pBackground, updrect);

        //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
        //m_pBackground->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);
    }

    //m_pMainCanvas->FillRect(bluerectOld, CColor(0, 0, 0) );
    //CPoint spos( m_cpPos.GetX(), m_cpPos.GetY());
    //SDL_SetAlpha(m_pSprImage->GetCanvas()->GetSurface(), SDL_SRCALPHA /*| SDL_RLEACCEL*/, 128);
    m_pSprImage->Put(m_pMainCanvas, m_cpPos);
    m_pMainCanvas->Unlock();
    m_pMainCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpOldPos);
    m_pMainCanvas->AddUpdateRect(m_pSprImage->GetCanvas()->GetDimension() + m_cpPos);

    m_cpOldPos = m_cpPos;
}

void CSprite::SetPos( CPoint& position )
{
    m_cpPos = position; 
}


std::ostream& operator<<(std::ostream& o, const CSprite& r) {
    return o << "CSprite[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
        << ", W=" << r.GetW() << ", H=" << r.GetH()
        <<*/ " ]";
}

