#ifndef GUI_HUD_H
#define GUI_HUD_H

#include "GUI/Components/Canvas.h"

class FileLoader;
class CImage;

class Hud {
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
