#ifndef HUMBUG_GUI_SPRITE_CSPRITE_H
#define HUMBUG_GUI_SPRITE_CSPRITE_H
#include "..\Components\Point.h"

class CCanvas;
class CImage;

class CSprite {
public:

    CSprite(CCanvas* mainCanvas, CImage* sprImage, CCanvas* background = NULL ,CRectangle spriteDimension = CRectangle(0,0,0,0)
        , CPoint spriteMove = CPoint(0,0) );
    ~CSprite();

    void Draw() ;
    void SetPos(CPoint& pos);
    void SprOffset(int offset); 

    friend std::ostream& operator<<(std::ostream& o, const CSprite& r);
    CImage* m_pSprImage;

private:
    CCanvas* m_pMainCanvas;
    CCanvas* m_pBackground;

    CPoint m_cpPos;
    CPoint m_cpOldPos;
    CPoint m_cpSprMove;
    CRectangle m_crSprDim;
};

std::ostream& operator<<(std::ostream& o, const CSprite& r);

#endif // HUMBUG_GUI_SPRITE_CSPRITE_H guard
