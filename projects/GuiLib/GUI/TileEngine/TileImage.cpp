//
#include "stdafx.h"

//
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "TileImage.h"

//#include <build/cmake/include/debug.h>
namespace gui {
  CTileImage::CTileImage( FileLoader& loader, std::string filename,
          CTileImageSetup configuration ) : CCanvas() {
      dbgOut(__FUNCTION__);
      SDL_Surface* bitmap = SDL_DisplayFormatAlpha( loader.FL_LOADIMG(filename) );
      loader.FreeLast();
      SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, 0xff00ff);
      //SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, (Uint32)(SDL_Color)CColor::Red());
      SDL_SetAlpha(bitmap, 0, 128);
      //SDL_SetAlpha(bitmap, 0, 0);
      //SDL_SetAlpha(bitmap, 0, 255);
      SetSurface( bitmap );
      m_tiConfig.BitmapHeight = GetHeight();
      m_tiConfig.BitmapWidth = GetWidth();
      m_tiConfig.TileSetName = configuration.TileSetName;
      m_tiConfig.TileWidth = configuration.TileWidth;
      m_tiConfig.TileHeight = configuration.TileHeight;
      m_tiConfig.TileCountX = configuration.TileCountX;
      m_tiConfig.TileCountY = configuration.TileCountY;
      m_tiConfig.TransparentX = configuration.TransparentX;
      m_tiConfig.TransparentY = configuration.TransparentY;
      m_tiConfig.Sequences = configuration.Sequences;
      // delete here ?
  }

	  CTileImage::CTileImage( FileLoader& loader, std::string filename, std::string tileDescrFile )
		  : CCanvas()
	  {

		  // Todo: duplicate init code ... see other ctor, simplify
		  dbgOut(__FUNCTION__);
		  SDL_Surface* bitmap = SDL_DisplayFormatAlpha( loader.FL_LOADIMG(filename) );
		  loader.FreeLast();
		  SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, 0xff00ff);
		  //SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, (Uint32)(SDL_Color)CColor::Red());
		  SDL_SetAlpha(bitmap, 0, 128);
		  //SDL_SetAlpha(bitmap, 0, 0);
		  //SDL_SetAlpha(bitmap, 0, 255);
		  SetSurface( bitmap );
		  m_tiConfig.BitmapHeight = GetHeight();
		  m_tiConfig.BitmapWidth = GetWidth();


		  std::string tileConfData = loader.FL_LOADASSTRING(tileDescrFile);
		  // parse me
		  std::istringstream htstrstr(tileConfData);
		  int TileCount, tmp, MapCount;
		  std::string picture;

		  htstrstr >> m_tiConfig.TileWidth >> m_tiConfig.TileHeight;
		  htstrstr >> TileCount;
		  htstrstr >> m_tiConfig.TileCountX >> m_tiConfig.TileCountY;
		  htstrstr >> tmp;
		  htstrstr >> tmp;
		  htstrstr >> tmp;
		  htstrstr >> tmp;
		  htstrstr >> tmp;
		  htstrstr >> m_tiConfig.TileSetName;
		  htstrstr >> picture;
		  htstrstr >> MapCount;

		  /*for (int i = 0; i < MapCount ; i++)
		  {
			  std::string MapName;
			  htstrstr >> MapName;
		  }*/
	  }

  CTileImage::~CTileImage(void){
      dbgOut(__FUNCTION__);
      // Todo: delete the bitmap. here or above.
  }

  /** $(class), ShowTiles:
   *  Detailed description.
   *  @param destination TODO
   * @param destPosition TODO
   * @return TODO
   */
  bool CTileImage::ShowTiles( CCanvas* destination, const CPoint& destPosition ) const {
      destination->Lock();
      CRectangle rectDst = destination->GetDimension() + destPosition;
      CRectangle rectSrc = GetDimension();

      //bool result = ( SDL_BlitSurface ( GetSurface ( ), rectSrc, destination->GetSurface ( ),
      // rectDst ) == 0 );
      bool result = destination->Blit(rectDst, *this, rectSrc);
      destination->Unlock();
      return result;
  }

  /** $(class), Draw:
   *  Detailed description.
   *  @param tile TODO
   * @param destination TODO
   * @param destPosition TODO
   * @return TODO
   */
  bool CTileImage::Draw( const CTile& tile, CCanvas* destination, const CPoint& destPosition ) const {
      destination->Lock();
      CRectangle rectDst = destination->GetDimension() + destPosition;
      CPoint tileDimension(m_tiConfig.TileWidth, m_tiConfig.TileHeight);

      int xmod = tile.Index() % m_tiConfig.TileCountX;
      int ymod = tile.Index() / m_tiConfig.TileCountX;

      CPoint tilePosition(m_tiConfig.TileWidth * xmod, m_tiConfig.TileHeight * ymod);
      CRectangle rectSrc(tilePosition, tileDimension);

      bool result = destination->Blit(rectDst, *this, rectSrc);
      destination->Unlock();
      return result;
  }

  /** $(class), operator <<:
   *  Detailed description.
   *  @param o TODO
   * @param r TODO
   * @return TODO
   */
  std::ostream& operator<<(std::ostream& o, const CTileImage& r) {
      return o << "CTileImage[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                      << ", W=" << r.GetW() << ", H=" << r.GetH()
                                      <<*/
             " ]";
  }
}
