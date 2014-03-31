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


		  std::string tileConfData = loader.FL_LOADASSTRING(tileDescrFile);
		  // parse me
		  std::istringstream htstrstr(tileConfData);
		  int TileCount, MapCount;
		  uint32_t transparentColorR , transparentColorG, transparentColorB;
		  uint32_t dummy1x, dummy2x, dummy3x, dummy4x, dummy5x, transparentColor;
		  std::string picture;
		  std::string tmpStr;

		  htstrstr >> m_tiConfig.TileWidth >> m_tiConfig.TileHeight;
		  htstrstr >> TileCount;
		  htstrstr >> m_tiConfig.TileCountX >> m_tiConfig.TileCountY;
		  htstrstr >> transparentColorR;
		  htstrstr >> transparentColorG;
		  htstrstr >> transparentColorB;
		  htstrstr >> dummy4x;
		  htstrstr >> dummy5x;
		  htstrstr >> m_tiConfig.TileSetName;
		  htstrstr >> picture;
		  htstrstr >> MapCount;
		
		  transparentColor = transparentColorR;
		  transparentColor <<= 8;
		  transparentColor |= transparentColorG;
		  transparentColor <<= 8;
		  transparentColor |= transparentColorB;
		  //transparentColor <<= 8;
		  SDL_SetAlpha(bitmap, 0, 0);
		  //SDL_SetAlpha(bitmap, SDL_RLEACCEL, 128);

		  SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, 0xffffff);
		  /*for (int i = 0; i < MapCount ; i++)
		  {
			  std::string MapName;
			  htstrstr >> MapName;
		  }*/


		  //SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, 0xff00ff);
		  //SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, 0xffffff);
		  //SDL_SetColorKey(bitmap, SDL_SRCCOLORKEY, (Uint32)(SDL_Color)CColor::Red());
		  //SDL_SetAlpha(bitmap, 0, 0);
		  //SDL_SetAlpha(bitmap, 0, 255);
		  SetSurface( bitmap );
		  m_tiConfig.BitmapHeight = GetHeight();
		  m_tiConfig.BitmapWidth = GetWidth();

	  }

	  CTileImage::CTileImage( const CColor& color )
		  : CCanvas()
	  {
		  CCanvas* testCanvas = CCanvas::CreateRGB(SDL_SWSURFACE | SDL_SRCALPHA, 64, 64, 8, 222, 2, 222, 11);
		  //CCanvas* testCanvas = CCanvas::CreateRGBCompatible(NULL, 128, 128);
		  CColor fcolor(0x00, 0x00, 0x00);
		  //fcolor.SetA(128);
		  //testCanvas->FillRect(testCanvas->GetDimension(), fcolor);
		  //Uint32 col = SDL_MapRGB ( testCanvas->GetSurface ( )->format, color.GetR ( ), color.GetG ( ), color.GetB ( ) );
		  //Uint32 col = SDL_MapRGB ( testCanvas->GetSurface ( )->format, 22, 112, 33);
		  Uint32 col = 0x22330000;
		  Uint32 col2 =0xaaffffff;
		  SDL_FillRect ( testCanvas->GetSurface ( ), NULL, col );

		  //testCanvas->Clear(fcolor);
		  
		  SDL_SetColorKey(testCanvas->GetSurface(), SDL_SRCCOLORKEY, col2);
		  //SDL_SetAlpha(testCanvas->GetSurface(), SDL_SRCALPHA, 0);
		  
		  //SDL_SetAlpha(testCanvas->GetSurface(), SDL_SRCALPHA, SDL_ALPHA_TRANSPARENT);
		  SetSurface( testCanvas->GetSurface() );
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
	  //CRectangle rectDst = destination->GetDimension() + destPosition;
      CPoint tileDimension(m_tiConfig.TileWidth, m_tiConfig.TileHeight);
	  CRectangle rectDst(destPosition, tileDimension);

      int xmod = tile.Index() % m_tiConfig.TileCountX;
      int ymod = tile.Index() / m_tiConfig.TileCountX;

      CPoint tilePosition(m_tiConfig.TileWidth * xmod, m_tiConfig.TileHeight * ymod);
      CRectangle rectSrc(tilePosition, tileDimension);

      bool result = destination->Blit(rectDst, *this, rectSrc);
      destination->Unlock();
	  LOGSTREAM << "CTileImage::Draw->" << rectDst << ", " << rectSrc << ".";
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
