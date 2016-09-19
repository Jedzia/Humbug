//
#include "stdafx.h"
//#include <build/cmake/include/debug.h>
//
#include "../../Filesystem/FileLoader.h"
#include "TileEngine.h"

namespace gui {
  CTileEngine::CTileEngine(const CCanvas* mainCanvas, const CCanvas* background)
      : m_pMainCanvas(mainCanvas), m_pBackground(background){
      dbgOut(__FUNCTION__);
//	_CRT_DEBUG_BLOCK
  }

  CTileEngine::~CTileEngine(void){
      m_pvTileSets.release();
      m_pvTileMaps.release();
      dbgOut(__FUNCTION__);
//    const char* explanation = "XXXXXX THIS IS ~CTileEngine.CPP";
//_RPT1( _CRT_WARN, "\n\n%s:\n**************************************\
// //************************************\n", explanation );
//    _CrtDumpMemoryLeaks( );
  }

  /** $(class), AddTileSet:
   *  Detailed description.
   *  @param tileset TODO
   * @return TODO
   */
  void CTileEngine::AddTileSet(CTileSet* tileset){
      m_pvTileSets.push_back(tileset);
  }

/*void CTileEngine::AddTileSet(const std::string& filename)
   {
    CTileImageSetup
   }*/
  void CTileEngine::AddTileSet(FileLoader& loader, const CTileImageSetup& config, const CRectangle& screen){
      std::string fname(config.TileSetName);
      fname = "Tiles/" + fname + ".bmp";
      CTileSet* tileSet = new CTileSet(m_pMainCanvas, new CTileImage(loader, fname, config),
              m_pBackground, screen );
      AddTileSet(tileSet);
  }

  /** $(class), operator []:
   *  Detailed description.
   *  @param mapName TODO
   * @return TODO
   */
  CTileEngine::CTileRunner CTileEngine::operator[]( const std::string& mapName ){
      /*TileStorage::iterator it = m_pvTileSets.find(console);
         if(it != m_vCmdCallbacks.end())
         {
          //    cout << "value:" << (*it).second
          CConsole::CConsoleImpl* mySelf =(*it).second;
          // call member
          mySelf->Command_Handler(console, command);
         }*/

      MapStorage::pointer result = NULL;
      MapStorage::iterator end = m_pvTileMaps.end();

      for (MapStorage::iterator it = m_pvTileMaps.begin(); it < end; ++it)
      {
          CTileMap& current = (*it);

          if (current.MapIdentifier() == mapName) {
              result = &current;
          }
      }
      dbgOut(__FUNCTION__ << " Found CTileMap: (" << result << ")");

	  // Todo: check for valid id, tileset, etc.
	  std::string mapId = result->TileSetIdentifier();
	  CTileSet *tileSet = GetTileSet(mapId);
      return CTileRunner(m_pMainCanvas, m_pBackground, this, result, tileSet);
  } // []

  /** $(class), AddTileMap:
   *  Detailed description.
   *  @param tmap TODO
   * @return TODO
   */
  void CTileEngine::AddTileMap( CTileMap* tmap ){
      m_pvTileMaps.push_back(tmap);
  }

  /** $(class), GetTileSet:
   *  Detailed description.
   *  @param tileSetName TODO
   * @return TODO
   */
  CTileSet * CTileEngine::GetTileSet( const std::string& tileSetName ){
      TileStorage::pointer result = NULL;
      TileStorage::iterator end = m_pvTileSets.end();

      for (TileStorage::iterator it = m_pvTileSets.begin(); it < end; ++it)
      {
          CTileSet& current = (*it);

          if (current.GetTileImage()->GetConfig().TileSetName == tileSetName) {
              result = &current;
          }
      }
      dbgOut(__FUNCTION__ << " Found CTileSet: (" << result << ")");
      return result;
  }

  /** $(class), operator <<:
   *  Detailed description.
   *  @param o TODO
   * @param r TODO
   * @return TODO
   */
  std::ostream& operator<<(std::ostream& o, const CTileEngine& r) {
      return o << "CTileEngine[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                       << ", W=" << r.GetW() << ", H=" << r.GetH()
                                       <<*/
             " ]";
  }

  CTileEngine::CTileRunner::CTileRunner( const CCanvas* mainCanvas, const CCanvas* background, CTileEngine* engine, CTileMap* tileMap, CTileSet *tileSet )
	  :m_tileMap(tileMap), m_tileSet(tileSet)
  {

  }

  CTileEngine::CTileRunner::~CTileRunner()
  {}

  /** $(class), AddTileSet:
   *  Detailed description.
   *  @param tileset TODO
   * @return TODO
   */
  void CTileEngine::CTileRunner::AddTileSet( CTileSet* tileset )
  {}

  /** $(class), DrawMap:
   *  Detailed description.
   *  @return TODO
   */
  void CTileEngine::CTileRunner::DrawMap(CCanvas* background)
  {

	  //CTile tile = m_tileSet->CreateTile(0);
	  CPoint nil;
	  m_tileMap->Draw(*m_tileSet, background, nil);
  }
}
