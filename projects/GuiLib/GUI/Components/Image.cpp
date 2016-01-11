#include "../../stdafx.h"
#include "Image.h"

namespace gui {
namespace components {

CImage::CImage ( CCanvas* pcnvSource, bool freeSrc )
: m_bFreeSrc(freeSrc){
    dbgOut(__FUNCTION__);
    SetCanvas ( pcnvSource );
    m_rcSrc = m_rcDst = pcnvSource->GetDimension();
}

CImage::CImage ( CCanvas* pcnvSource, CRectangle rcSource, bool freeSrc, CPoint ptOffset )
: m_bFreeSrc(freeSrc){
    dbgOut(__FUNCTION__);
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
    dbgOut(__FUNCTION__);
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

    void CImage::RenderPut(CCanvas* pcnvDest, const CPoint& ptDst)
    {
        DstRect() += ptDst;
        CCanvas* source = GetCanvas();
        source->GetTexture();
        pcnvDest->RenderPutCopy(source, &SrcRect(), &DstRect());
        DstRect() -= ptDst;
    }

    void CImage::Scale(float factor)
    {
        Scale(factor, factor);
    }

    void CImage::Scale(float wFactor, float hFactor)
    {
        DstRect().W() *= wFactor;
        DstRect().H() *= hFactor;
    }
} // namespace components
} // namespace gui
