#ifndef BUTTON_H__
#define BUTTON_H__

#include "Control.h"
#include <string>
#include "sdl_ttf.h"
#include "../Components/Color.h"

//CButton class
//abstracts a ui button
class CButton : public CControl  
{
private:
	//caption for button
	std::string m_sCaption;
	//colors for button
	CColor m_colFace;
	CColor m_colText;
	CColor m_colHilite;
	CColor m_colShadow;
	//canvas for text
	CCanvas* m_pcnvText;
	//pressed state
	bool m_bPressed;
	//button font
	static TTF_Font* s_ButtonFont;
public:
	//construction
	CButton(CControl* pParent,CRectangle rcDimensions,Uint32 id,std::string sCaption,CColor colFace=CColor(192,192,192),CColor colText=CColor(0,0,0),CColor colHilite=CColor(255,255,255),CColor colShadow=CColor(128,128,128));
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

#endif // #ifndef BUTTON_H__
