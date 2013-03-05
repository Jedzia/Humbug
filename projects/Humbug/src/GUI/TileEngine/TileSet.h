
#ifndef HUMBUG_GUI_TILEENGINE_CTILESET_H
#define HUMBUG_GUI_TILEENGINE_CTILESET_H
#include "../Components/Point.h"
#include "../Components/Rectangle.h"
#include "Tile.h"
#include "TileImage.h"
#include <string>


namespace gui { namespace components {
	class CCanvas;
}}
class FileLoader;

using namespace gui::components;

class CTileSet {
public:

    CTileSet( const CCanvas * mainCanvas, CTileImage* tileImage, const CCanvas * background, CRectangle screen);
    ~CTileSet();
    CTile CreateTile(int index) const;

    inline const CTileImage* GetTileImage() const { return m_ctiTileImage; }

    friend std::ostream& operator<<(std::ostream& o, const CTileSet& r);

protected:
    // Todo: DeleteME
    void Draw(const CTile& tile);
private:

   const CTileImage* m_ctiTileImage;
   const CCanvas* m_pMainCanvas;
   const CCanvas* m_pBackground;
   CRectangle m_crScreen;
};
std::ostream& operator<<(std::ostream& o, const CTileSet& r);

#endif // HUMBUG_GUI_TILEENGINE_CTILESET_H guard
