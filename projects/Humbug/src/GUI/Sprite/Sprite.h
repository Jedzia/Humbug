#ifndef HUMBUG_GUI_SPRITE_CSPRITE_H
#define HUMBUG_GUI_SPRITE_CSPRITE_H
#include "..\Components\Point.h"

class CCanvas;
class CImage;

class CSprite {
public:

    CSprite(CCanvas* mainCanvas, CImage* sprImage, CCanvas* background = NULL);
    ~CSprite();

    void Draw() ;
    void SetPos(CPoint& pos);

    friend std::ostream& operator<<(std::ostream& o, const CSprite& r);

private:
    CCanvas* m_pMainCanvas;
    CCanvas* m_pBackground;
    CImage* m_pSprImage;

    CPoint m_cpPos;
    CPoint m_cpOldPos;
};

std::ostream& operator<<(std::ostream& o, const CSprite& r);

#endif // HUMBUG_GUI_SPRITE_CSPRITE_H guard
