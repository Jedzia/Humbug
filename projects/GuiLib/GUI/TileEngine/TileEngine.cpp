//
#include "stdafx.h"
//#include <build/cmake/include/debug.h>
//
#include "TileEngine.h"
#include "../../Filesystem/FileLoader.h"

namespace gui {


CTileEngine::CTileEngine(const CCanvas * mainCanvas, const CCanvas * background)
: m_pMainCanvas(mainCanvas), m_pBackground(background)
{
         dbgOut(__FUNCTION__);
//	_CRT_DEBUG_BLOCK
}

CTileEngine::~CTileEngine(void)
{
	m_pvTileSets.release();
	m_pvTileMaps.release();
         dbgOut(__FUNCTION__);
//    const char* explanation = "XXXXXX THIS IS ~CTileEngine.CPP";
//_RPT1( _CRT_WARN, "\n\n%s:\n**************************************\
//************************************\n", explanation );
//    _CrtDumpMemoryLeaks( );
}

void CTileEngine::AddTileSet(CTileSet * tileset)
{
    m_pvTileSets.push_back(tileset);
}

/*void CTileEngine::AddTileSet(const std::string& filename)
{
    CTileImageSetup
}*/

void CTileEngine::AddTileSet(FileLoader& loader, const CTileImageSetup& config, const CRectangle& screen)
{
    std::string fname(config.BitmapIdentifier);
    fname = "Tiles/" + fname + ".bmp";
    CTileSet* tileSet = new CTileSet(m_pMainCanvas, new CTileImage(loader, fname, config),
        m_pBackground, screen );
    AddTileSet(tileSet);
}

CTileMap * CTileEngine::operator[]( const std::string& mapName )
{
    /*TileStorage::iterator it = m_pvTileSets.find(console);
    if(it != m_vCmdCallbacks.end())
    {
        //    cout << "value:" << (*it).second
        CConsole::CConsoleImpl* mySelf =(*it).second;
        // call member
        mySelf->Command_Handler(console, command);
    }*/


    MapStorage::pointer result = NULL;
    MapStorage::iterator end = m_pvTileSets.end();
    for (MapStorage::iterator it = m_pvTileSets.begin(); it < end ; it++)
    {
        CTileMap& current = (*it);
    	if (current.MapIdentifier() == mapName)
    	{
            result = &current;
    	}
    }

    dbgOut(__FUNCTION__ << " Found CTileMap: (" << result << ")");
    return result;
}

void CTileEngine::AddTileMap( CTileMap * tmap )
{
	m_pvTileMaps.push_back(tmap);
}

CTileSet * CTileEngine::GetTileSet( const std::string& tileSetName )
{
    TileStorage::pointer result = NULL;
    TileStorage::iterator end = m_pvTileSets.end();
    for (TileStorage::iterator it = m_pvTileSets.begin(); it < end ; it++)
    {
        CTileSet& current = (*it);
    	if (current.GetTileImage()->GetConfig().BitmapIdentifier == tileSetName)
    	{
            result = &current;
    	}
    }

    dbgOut(__FUNCTION__ << " Found CTileSet: (" << result << ")");
    return result;
}

std::ostream& operator<<(std::ostream& o, const CTileEngine& r) {
    return o << "CTileEngine[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
        << ", W=" << r.GetW() << ", H=" << r.GetH()
        <<*/ " ]";
}

}
