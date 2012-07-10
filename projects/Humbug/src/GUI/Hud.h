#ifndef GUI_HUD_H
#define GUI_HUD_H

#include "GUI/Controls/Control.h"
#include "GUI/Components/Canvas.h"

class FileLoader;
class CImage;

class HudBackground  {
public:

    // Hud(const FileLoader& loader, CCanvas* pCanvas);
    HudBackground(const FileLoader& loader, std::string filename);
    ~HudBackground();

    //void Draw();
	CCanvas* GetCanvas();

private:
	CCanvas* m_pFooter;
};

struct HudImages
{
    char* Meter;
    char* Lamp;
    char* Switch;
    char* Nothing;
    //int rotz :1;

};

class Hud : public CControl {
public:

    // Hud(const FileLoader& loader, CCanvas* pCanvas);
    Hud(const FileLoader& loader, CControl* pParent, HudBackground* bkg, Uint32 id);
    ~Hud();

    //void Draw();
	void OnDraw();
	virtual bool OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);

private:
	void Init(CControl* pParent);
    CRectangle InitRect(const FileLoader& loader);

	//canvas used by window
	const FileLoader& m_pLoader;
	//CCanvas* m_pCanvas;
	//CPoint dst;
    HudBackground* m_pBackground;
	// CCanvas* footer;
	CImage* footerImage;
    bool oldstate;
    CCanvas* tmpcanvas;
};

#endif // GUI_HUD_H
