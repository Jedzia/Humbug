#include "../../stdafx.h"
#include "Image.h"
CImage::CImage ( CCanvas* pcnvSource, bool freeSrc )
: m_bFreeSrc(freeSrc){
    SetCanvas ( pcnvSource );
    m_rcSrc = m_rcDst = pcnvSource->GetDimension();
}

CImage::CImage ( CCanvas* pcnvSource, CRectangle rcSource, CPoint ptOffset, bool freeSrc )
: m_bFreeSrc(freeSrc){
    SetCanvas ( pcnvSource );
    SrcRect ( ) = rcSource;
    DstRect ( ) = rcSource;
    DstRect ( ) -= ptOffset;
}

CImage::~CImage ( )
{
    if (m_bFreeSrc)
    {
        delete m_pcnvSrc;
    }
}

CCanvas * CImage::GetCanvas ( ){
    return ( m_pcnvSrc );
}

void CImage::SetCanvas ( CCanvas* pcnvSource ){
    m_pcnvSrc = pcnvSource;
}

CRectangle& CImage::SrcRect ( ){
    return ( m_rcSrc );
}

CRectangle& CImage::DstRect ( ){
    return ( m_rcDst );
}

void CImage::Put ( CCanvas* pcnvDest, const CPoint& ptDst ){
    DstRect ( ) += ptDst;
    pcnvDest->Blit ( DstRect ( ), *GetCanvas ( ), SrcRect ( ) );
    DstRect ( ) -= ptDst;
}

