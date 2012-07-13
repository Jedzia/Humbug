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

bool CTileImage::ShowTiles( CCanvas* destination, const CPoint& destPosition )
{
    destination->Lock();
    CRectangle rectDst = destination->GetDimension() + destPosition;
    CRectangle rectSrc = GetDimension();

    //bool result = ( SDL_BlitSurface ( GetSurface ( ), rectSrc, destination->GetSurface ( ), rectDst ) == 0 );
    bool result = destination->Blit(rectDst, *this, rectSrc);
    destination->Unlock();
    return result;
}


bool CTileImage::Draw( const CTile& tile, CCanvas* destination, const CPoint& destPosition )
{
    destination->Lock();
    CRectangle rectDst = destination->GetDimension() + destPosition;
    CPoint tileDimension(m_tiConfig.TileWidth, m_tiConfig.TileHeight);
    CPoint tileIndex(m_tiConfig.TileWidth, 0);
    CPoint tilePosition = tileIndex * tile.Index();
    CRectangle rectSrc(tilePosition, tileDimension);

    //bool result = ( SDL_BlitSurface ( GetSurface ( ), rectSrc, destination->GetSurface ( ), rectDst ) == 0 );
    bool result = destination->Blit(rectDst, *this, rectSrc);
    destination->Unlock();
    return result;
}

std::ostream& operator<<(std::ostream& o, const CTileImage& r) {
    return o << "CTileImage[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                 << ", W=" << r.GetW() << ", H=" << r.GetH()
                                 <<*/" ]";
}

