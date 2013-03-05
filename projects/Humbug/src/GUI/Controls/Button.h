#ifndef BUTTON_H__
#define BUTTON_H__

#include "Control.h"
#include <string>
#include "sdl_ttf.h"
#include "../Components/Color.h"

namespace gui {
namespace controls {

//CButton class
//abstracts a ui button
class CButton : public CControl  
{
private:
	//caption for button
	std::string m_sCaption;
	//colors for button
	gui::components::CColor m_colFace;
	gui::components::CColor m_colText;
	gui::components::CColor m_colHilite;
	gui::components::CColor m_colShadow;
	//canvas for text
	gui::components::CCanvas* m_pcnvText;
	//pressed state
	bool m_bPressed;
	//button font
	static TTF_Font* s_ButtonFont;
public:
	//construction
	CButton(CControl* pParent,gui::components::CRectangle rcDimensions,Uint32 id,std::string sCaption,gui::components::CColor colFace=gui::components::CColor(192,192,192),gui::components::CColor colText=gui::components::CColor(0,0,0),gui::components::CColor colHilite=gui::components::CColor(255,255,255),gui::components::CColor colShadow=gui::components::CColor(128,128,128));
	//destruction
	virtual ~CButton();
	//customize redrawing
	virtual void OnDraw();
	//left button handlers
	virtual bool OnLButtonDown(Uint16 x,Uint16 y);
	virtual bool OnLButtonUp(Uint16 x,Uint16 y);
	//set caption
	void SetCaption(std::string sCaption);
	//get caption
	std::string GetCaption();
	//set button font
	static void SetButtonFont(TTF_Font* pFont);
	static TTF_Font* GetButtonFont();
	//message for clicking button
	static MSGID MSGID_ButtonClick;//parm1=id
};

} // namespace controls
} // namespace gui

#endif // #ifndef BUTTON_H__
