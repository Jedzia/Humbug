#ifndef HUMBUG_GUI_TILEENGINE_CTILEENGINE_H
#define HUMBUG_GUI_TILEENGINE_CTILEENGINE_H

#include <boost/ptr_container/ptr_vector.hpp>
#include "TileSet.h"
class FileLoader;

class CTileEngine {
public:

    CTileEngine(const CCanvas * mainCanvas, const CCanvas * background);
    ~CTileEngine();

    void AddTileSet(CTileSet * tileset);
    void AddTileSet(const FileLoader& loader, const CTileImageSetup& config, const CRectangle& screen);


    CTileSet * operator[]( const std::string& tileSetName );

    friend std::ostream& operator<<(std::ostream& o, const CTileEngine& r);

private:
    //const CTileImage* m_ctiTileImage;
    typedef boost::ptr_vector<CTileSet> TileStorage;
    TileStorage m_pvTileSets;
    const CCanvas* m_pMainCanvas;
    const CCanvas* m_pBackground;
    //CRectangle m_crScreen;
};

std::ostream& operator<<(std::ostream& o, const CTileEngine& r);

#endif // HUMBUG_GUI_TILEENGINE_CTILEENGINE_H guard
