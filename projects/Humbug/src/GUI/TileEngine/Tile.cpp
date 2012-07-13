//
#include "stdafx.h"

//
#include "../Components/Canvas.h"
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "Tile.h"
#include "TileImage.h"


CTile::CTile(  CTileImage* tileImage, int index   )
:  m_ctiTileImage(tileImage), m_iIndex(index){
    dbgOut(__FUNCTION__ << std::endl);
}


CTile::~CTile(void){
    dbgOut(__FUNCTION__ << std::endl);
}

void CTile::Draw(CCanvas* background, const CPoint& position){
    if (background) {
        m_ctiTileImage->Draw(*this, background, position);
    }

} // Draw

std::ostream& operator<<(std::ostream& o, const CTile& r) {
    return o << "CTile[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                 << ", W=" << r.GetW() << ", H=" << r.GetH()
                                 <<*/" ]";
}

