#ifndef GUI_HUD_H
#define GUI_HUD_H

//#include "GUI/Controls/Control.h"
#include "GUI/Components/Canvas.h"

class FileLoader;
class CImage;

class Hud /*: CControl*/ {
public:

    Hud(const FileLoader& loader, CCanvas* pCanvas);
    ~Hud();

    void Draw();

private:
	//canvas used by window
	const FileLoader& m_pLoader;
	CCanvas* m_pCanvas;
	CPoint dst;
	CCanvas* footer;
	CImage* footerImage;
};

#endif // GUI_HUD_H
