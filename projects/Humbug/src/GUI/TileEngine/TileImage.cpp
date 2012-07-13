//
#include "stdafx.h"

//
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "TileImage.h"

//#include <build/cmake/include/debug.h>
/*CTileImage::CTileImage(CCanvas* mainCanvas, CImage* sprImage, CCanvas* background,
        CRectangle spriteDimension,
        CPoint spriteMove) :
    m_pMainCanvas(mainCanvas),
    m_pSprImage(sprImage),
    m_pBackground(background),
    m_cpPos(0, 0),
    m_cpOldPos(0, 0),
    m_cpSprMove(spriteMove),
    m_crSprDim(spriteDimension){
    dbgOut(__FUNCTION__ << std::endl);

    //m_cpSprDim.SetX(sprImage->SrcRect().GetW());
    //m_cpSprDim.SetY(sprImage->SrcRect().GetH());
}*/

CTileImage::CTileImage( const FileLoader& loader, std::string filename, CTileImageSetup configuration )
: CCanvas()
{
    // m_pSprImage(sprImage),
    /*if ( spriteDimension == CRectangle(0, 0, 0, 0) ) {
        m_pSprImage = new CImage( new CCanvas( SDL_DisplayFormatAlpha( loader.LoadImg(filename) ) ) );
    }
    else {
        m_pSprImage = new CImage( new CCanvas( SDL_DisplayFormatAlpha( loader.LoadImg(
                                        filename) ) ), spriteDimension );
    }*/
    SetSurface( SDL_DisplayFormatAlpha( loader.LoadImg(filename)  ));

    m_tiConfig.BitmapHeight = GetHeight();
    m_tiConfig.BitmapWidth = GetWidth();
    m_tiConfig.BitmapIdentifier = configuration.BitmapIdentifier;
    m_tiConfig.TileWidth = configuration.TileWidth;
    m_tiConfig.TileHeight = configuration.TileHeight;
    m_tiConfig.TileCountX = configuration.TileCountX;
    m_tiConfig.TileCountY = configuration.TileCountY;
    m_tiConfig.TransparentX = configuration.TransparentX;
    m_tiConfig.TransparentY = configuration.TransparentY;
    m_tiConfig.Sequences = configuration.Sequences;
}

CTileImage::~CTileImage(void){
    dbgOut(__FUNCTION__ << std::endl);
}

void CTileImage::SetPos( CPoint& position ){
}

void CTileImage::SprOffset( int offset ){
    // m_pSprImage->SrcRect() = m_crSprDim.Move(m_cpSprMove * offset);
}

bool CTileImage::Draw( CCanvas* destination )
{
    CRectangle rectDst2 = destination->GetDimension();
    CRectangle rectSrc = GetDimension();

    return ( SDL_BlitSurface ( GetSurface ( ), rectSrc, destination->GetSurface ( ), rectDst2 ) == 0 );

}

std::ostream& operator<<(std::ostream& o, const CTileImage& r) {
    return o << "CTileImage[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                 << ", W=" << r.GetW() << ", H=" << r.GetH()
                                 <<*/" ]";
}

