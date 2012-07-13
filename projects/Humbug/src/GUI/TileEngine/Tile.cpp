//
#include "stdafx.h"

//
#include "../Components/Canvas.h"
#include "../Components/Image.h"
#include "Filesystem/FileLoader.h"
#include "SDL.h"
#include "Tile.h"


CTile::CTile( int index  )
:  m_iIndex(index){
    dbgOut(__FUNCTION__ << std::endl);
}


CTile::~CTile(void){
    dbgOut(__FUNCTION__ << std::endl);
}

void CTile::Draw(){

} // Draw

void CTile::SetPos( CPoint& position ){
    //m_cpPos = position;
}

void CTile::SprOffset( int offset ){
    //m_pSprImage->SrcRect() = m_crSprDim.Move(m_cpSprMove * offset);
}

std::ostream& operator<<(std::ostream& o, const CTile& r) {
    return o << "CTile[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                 << ", W=" << r.GetW() << ", H=" << r.GetH()
                                 <<*/" ]";
}

