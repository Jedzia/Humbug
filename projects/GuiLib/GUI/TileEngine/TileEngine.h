#ifndef HUMBUG_GUI_TILEENGINE_CTILEENGINE_H
#define HUMBUG_GUI_TILEENGINE_CTILEENGINE_H

#include <boost/ptr_container/ptr_vector.hpp>
#include "TileSet.h"
#include "TileMap.h"
class FileLoader;

namespace gui {
class CTileEngine {
public:

    CTileEngine(const CCanvas * mainCanvas, const CCanvas * background);
    ~CTileEngine();

    void AddTileSet(CTileSet * tileset);
    void AddTileSet(FileLoader& loader, const CTileImageSetup& config, const CRectangle& screen);
	CTileSet * GetTileSet( const std::string& tileSetName );
    
	CTileMap * operator[]( const std::string& mapName );

    friend std::ostream& operator<<(std::ostream& o, const CTileEngine& r);
	void AddTileMap( CTileMap * tmap );
private:
    //const CTileImage* m_ctiTileImage;
	typedef boost::ptr_vector<CTileSet> TileStorage;
	typedef boost::ptr_vector<CTileMap> MapStorage;
	TileStorage m_pvTileSets;
	MapStorage m_pvTileMaps;
    const CCanvas* m_pMainCanvas;
    const CCanvas* m_pBackground;
    //CRectangle m_crScreen;
};

std::ostream& operator<<(std::ostream& o, const CTileEngine& r);

}

#endif // HUMBUG_GUI_TILEENGINE_CTILEENGINE_H guard
