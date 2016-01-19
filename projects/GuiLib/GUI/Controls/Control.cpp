// Control.cpp: implementation of the CControl class.
//
//////////////////////////////////////////////////////////////////////

#include "../../stdafx.h"
#include "Control.h"

namespace gui {
namespace controls {

//list of windows to bring to front
std::list<CControl*> CControl::s_lstUpdate(0);
//list of windows to close
std::list<CControl*> CControl::s_lstClose(0);
//static pointer to main control
CControl* CControl::s_pMainControl(NULL);
//keyboard focus
CControl* CControl::s_pKeyboardFocus(NULL);
//mouse focus
CControl* CControl::s_pMouseFocus(NULL);
//mouse hovering
CControl* CControl::s_pMouseHover(NULL);

components::CRectangle CControl::GetOffset() const
{
    return m_rectOffset;
}

    //master control constructor
CControl::CControl(gui::components::CCanvas* pCanvas, bool usesSDL2Render) :
m_lstChildren(0), 
m_bUsesSDL2Render(usesSDL2Render),
m_ID(0),
m_pParent(NULL), m_ptIsDirty(false)
{
    dbgOut(__FUNCTION__);

	if (s_pMainControl)
	{
		// throw new std::exception("CControl::CControl, already has a master control.");
	}
	
	//set the canvas
	m_pCanvas=pCanvas;
	//this is the main control
	s_pMainControl=this;
	//set position
	SetPosition(gui::components::CPoint(0,0));
    Invalidate();
}

//child control constructor
CControl::CControl(CControl* pParent, gui::components::CRectangle rcDimensions, Uint32 id, bool invalidate, bool usesSDL2Render) :
m_lstChildren(0),
m_bUsesSDL2Render(usesSDL2Render),
m_ID(id),
m_pParent(NULL), m_ptIsDirty(invalidate)
{
    dbgOut(__FUNCTION__);
	//set parent
	SetParent(pParent);
	//create an rgb compatible surface
	m_pCanvas=gui::components::CCanvas::CreateRGBCompatible(0,rcDimensions.GetW(),rcDimensions.GetH());
	//set position
	m_ptPosition.SetX(rcDimensions.GetX());
	m_ptPosition.SetY(rcDimensions.GetY());
    //Invalidate();
}

//destructor
CControl::~CControl()
{

    //remove from update list
    if(!s_lstUpdate.empty() && !IsMainControl())
    {
        s_lstUpdate.remove(this);
    }

    //remove from close list
    if(!s_lstClose.empty() && !IsMainControl())
    {
        s_lstClose.remove(this);
    }

	//set parent to NULL
	SetParent(NULL);
	//if has mouse focus, remove it
	if(HasMouseFocus())
	{
		SetMouseFocus(NULL);
	}
	//if has keyboard focus, remove it
	if(HasKeyboardFocus())
	{
		SetKeyboardFocus(NULL);
	}
	//if has mouse hovering, remove it
	if(HasMouseHover())
	{
		SetMouseHover(NULL);
	}
	//destroy all children
	while(!m_lstChildren.empty())
	{
		CControl* pControl=(*m_lstChildren.begin());
		delete pControl;
	}
	//delete canvas if not main control
	if(!IsMainControl())
	{
		delete m_pCanvas;
	}
    dbgOut(__FUNCTION__ << " (" << m_ID << ")");
}

//add child handler
void CControl::AddChild(CControl* pControl)
{
	//if cast is non-null
	if(pControl)
	{
		//remove from list(if it is there)
		m_lstChildren.remove(pControl);
		//add to child list
		m_lstChildren.push_back(pControl);
	}
}

//remove child handler
void CControl::RemoveChild(CControl* pControl)
{
	//if cast is non-null
	if(pControl)
	{
		//remove from list(if it is there)
		m_lstChildren.remove(pControl);
	}
}

//bring to front
void CControl::BringToFront()
{
	//remove from update list
	s_lstUpdate.remove(this);
	//add to update list
	s_lstUpdate.push_back(this);
}

//close
void CControl::Close()
{
	//remove from close list
	s_lstClose.remove(this);
	//add to close list
	s_lstClose.push_back(this);
}

//update all
void CControl::Update()
{
	//go through close list
	while(!s_lstClose.empty())
	{
		//grab first item in list
		CControl* pControl=(*s_lstClose.begin());
		//destroy item
		delete pControl;
	}
	//go through update list
	while(!s_lstUpdate.empty())
	{
		//grab first item in list
		CControl* pControl=(*s_lstUpdate.begin());
		//reset parent of control
		pControl->SetParent(pControl->GetParent());
	}
}

//redraw entire system
void CControl::Redraw()
{
	//redraw master control
    GetMainControl()->Draw();
}

//draw control
void CControl::Draw()
{
    // Todo: when using textures, they should be (re)generated at ctor or invalidation.
    // the coordinates have to be relative and recursive paint must be used by the control parent to draw.

	//if main control, update
	if(IsMainControl()) Update();
	//handle redrawing
    OnDraw();
	//draw all children
	std::list<CControl*>::iterator iter;
	for(iter=m_lstChildren.begin();iter!=m_lstChildren.end();iter++)
	{
		//grab item from list
		CControl* pChild=(*iter);
		//draw
		pChild->Draw();
	}
	//update parent
	CControl* pParent=GetParent();
	if(pParent)
	{
		//set up rectangles
		gui::components::CRectangle rcDst,rcSrc;
		//set destination rectangle
		rcDst.Set(GetPosition().GetX(),GetPosition().GetY(),GetWidth(),GetHeight());
		//set source rectangle
		rcSrc.Copy(rcDst);
		rcSrc.SetX(0);
		rcSrc.SetY(0);
		//blit
        if(m_ptIsDirty){
            if (m_bUsesSDL2Render)
            {
                //pParent->GetCanvas()->RenderPutCopy(GetCanvas(), &rcSrc, &rcDst);
            }
            else
                pParent->GetCanvas()->Blit(rcDst, *GetCanvas(), rcSrc);
            m_ptIsDirty = false;
        }
	}
}

//invalidate control
void CControl::Invalidate()
{
    gui::components::CRectangle globalPosition( GetLeft(), GetTop(), GetWidth(), GetHeight() );
    GetMainControl()->GetCanvas()->AddUpdateRect(globalPosition);
    // Todo: for all children
    m_ptIsDirty = true;
    if (GetParent())
    {
        GetParent()->Invalidate();
    }
}

//customize redrawing
void CControl::OnDraw()
{
	//by default, do nothing
}

//event handling
bool CControl::OnEvent(SDL_Event* pEvent)
{
	//attempt to let children handle event
	std::list<CControl*>::reverse_iterator iter;
	for(iter=m_lstChildren.rbegin();iter!=m_lstChildren.rend();iter++)
	{
		//grab item from list
		CControl* pControl=*iter;
		//attempt to handle event
		if(pControl->OnEvent(pEvent)) return (true);
	}
	//dispatch event
	switch(pEvent->type)
	{
	case SDL_KEYDOWN://key press
		{
			//key press
			return OnKeyDown(pEvent->key.keysym.sym,pEvent->key.keysym.mod);
		}break;
	case SDL_KEYUP://key release
		{
			//key release
			return OnKeyUp(pEvent->key.keysym.sym,pEvent->key.keysym.mod);
		}break;
	case SDL_MOUSEMOTION://mouse motion
		{
			return OnMouseMove(pEvent->motion.x,pEvent->motion.y,pEvent->motion.xrel,pEvent->motion.yrel,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
		}break;
	case SDL_MOUSEBUTTONDOWN://mouse button press
		{
			//which button?
			switch(pEvent->button.button)
			{
			case SDL_BUTTON_LEFT://left button
				{
					return OnLButtonDown(pEvent->button.x,pEvent->button.y);
				}break;
			case SDL_BUTTON_RIGHT://right button
				{
					return OnRButtonDown(pEvent->button.x,pEvent->button.y);
				}break;
			case SDL_BUTTON_MIDDLE://middle button
				{
					return OnMButtonDown(pEvent->button.x,pEvent->button.y);
				}break;
			}
		}break;
	case SDL_MOUSEBUTTONUP://mouse button release
		{
			//which button?
			switch(pEvent->button.button)
			{
			case SDL_BUTTON_LEFT://left button
				{
					return OnLButtonUp(pEvent->button.x,pEvent->button.y);
				}break;
			case SDL_BUTTON_RIGHT://right button
				{
					return OnRButtonUp(pEvent->button.x,pEvent->button.y);
				}break;
			case SDL_BUTTON_MIDDLE://middle button
				{
					return OnMButtonUp(pEvent->button.x,pEvent->button.y);
				}break;
			}
		}break;
	}
	return(false);
}

//keyboard events
bool CControl::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
	//return false
	return(false);
}

bool CControl::OnKeyUp(SDL_Keycode sym, Uint16 mod)
{
	//return false
	return(false);
}

//mouse events
bool CControl::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	if(IsMainControl()) return(false);
	//range check
	if(x>=GetLeft() && x<GetRight() && y>=GetTop() && y<GetBottom())
	{
		if(GetMouseHover()==NULL)
        {
            SetMouseHover(this);
        }
		return(true);
	}
	return(false);
}

bool CControl::OnLButtonDown(Uint16 x,Uint16 y)
{
	if(IsMainControl()) return(false);
	//range check
	return(x>=GetLeft() && x<GetRight() && y>=GetTop() && y<GetBottom());
}

bool CControl::OnLButtonUp(Uint16 x,Uint16 y)
{
	if(IsMainControl()) return(false);
	//range check
	return(x>=GetLeft() && x<GetRight() && y>=GetTop() && y<GetBottom());
}

bool CControl::OnRButtonDown(Uint16 x,Uint16 y)
{
	if(IsMainControl()) return(false);
	//range check
	return(x>=GetLeft() && x<GetRight() && y>=GetTop() && y<GetBottom());
}

bool CControl::OnRButtonUp(Uint16 x,Uint16 y)
{
	if(IsMainControl()) return(false);
	//range check
	return(x>=GetLeft() && x<GetRight() && y>=GetTop() && y<GetBottom());
}

bool CControl::OnMButtonDown(Uint16 x,Uint16 y)
{
	if(IsMainControl()) return(false);
	//range check
	return(x>=GetLeft() && x<GetRight() && y>=GetTop() && y<GetBottom());
}

bool CControl::OnMButtonUp(Uint16 x,Uint16 y)
{
	if(IsMainControl()) return(false);
	//range check
	return(x>=GetLeft() && x<GetRight() && y>=GetTop() && y<GetBottom());
}

//static event filter
bool CControl::FilterEvent(SDL_Event* pEvent)
{
	//set mouse hover to NULL
	if(pEvent->type==SDL_MOUSEMOTION) SetMouseHover(NULL);
	//check for a mouse event
	if(GetMouseFocus())
	{
		switch(pEvent->type)
		{
		case SDL_MOUSEMOTION://mouse motion
			{
				return GetMouseFocus()->OnMouseMove(pEvent->motion.x,pEvent->motion.y,pEvent->motion.xrel,pEvent->motion.yrel,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(pEvent->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
			}break;
		case SDL_MOUSEBUTTONDOWN://mouse button press
			{
				//which button?
				switch(pEvent->button.button)
				{
				case SDL_BUTTON_LEFT://left button
					{
						return GetMouseFocus()->OnLButtonDown(pEvent->button.x,pEvent->button.y);
					}break;
				case SDL_BUTTON_RIGHT://right button
					{
						return GetMouseFocus()->OnRButtonDown(pEvent->button.x,pEvent->button.y);
					}break;
				case SDL_BUTTON_MIDDLE://middle button
					{
						return GetMouseFocus()->OnMButtonDown(pEvent->button.x,pEvent->button.y);
					}break;
				}
			}break;
		case SDL_MOUSEBUTTONUP://mouse button release
			{
				//which button?
				switch(pEvent->button.button)
				{
				case SDL_BUTTON_LEFT://left button
					{
						return GetMouseFocus()->OnLButtonUp(pEvent->button.x,pEvent->button.y);
					}break;
				case SDL_BUTTON_RIGHT://right button
					{
						return GetMouseFocus()->OnRButtonUp(pEvent->button.x,pEvent->button.y);
					}break;
				case SDL_BUTTON_MIDDLE://middle button
					{
						return GetMouseFocus()->OnMButtonUp(pEvent->button.x,pEvent->button.y);
					}break;
				}
			}break;
		}
	}
	//check for a keyboard event
	if(GetKeyboardFocus())
	{
		switch(pEvent->type)
		{
		case SDL_KEYDOWN://key press
			{
				//key press
				return GetKeyboardFocus()->OnKeyDown(pEvent->key.keysym.sym,pEvent->key.keysym.mod);
			}break;
		case SDL_KEYUP://key release
			{
				//key release
				return GetKeyboardFocus()->OnKeyUp(pEvent->key.keysym.sym,pEvent->key.keysym.mod);
			}break;
		}
	}
	//have main control handle event
	return(GetMainControl()->OnEvent(pEvent));
}

//get position
gui::components::CPoint CControl::GetPosition() const
{
	//return position
    return(m_ptPosition);
    //return(m_ptPosition + GetOffset());
}

components::CRectangle CControl::VisibleArea() const
{
    return components::CRectangle(GetPosition().GetX(), GetPosition().GetY(), GetWidth(), GetHeight());
}

void CControl::SetOffset(const components::CRectangle& m_rect_offset)
{
    m_rectOffset = m_rect_offset;
}

components::CRectangle CControl::Intersects(const components::CRectangle& paintDestination) const
{
    auto parent = GetParent();
    if (!parent)
    {
        return paintDestination;
    }

    components::CRectangle glInter = paintDestination;
    components::CRectangle correctionRect(parent->GetLeft(), parent->GetTop(), parent->GetWidth(), parent->GetHeight());

    correctionRect.Y() += GetHeight();
    correctionRect.H() -= GetHeight() * 2;

    glInter.Intersect(correctionRect);

    return glInter;
}

//get width and height
Uint16 CControl::GetWidth() const
{
	//return canvas width
	return(GetCanvas()->GetWidth());
}

Uint16 CControl::GetHeight() const
{
	//return canvas height
	return(GetCanvas()->GetHeight());
}

//get edges in global coords
Uint16 CControl::GetLeft() const
{
	//get parent
	CControl* pParent=(GetParent());
	//if a parent exists...
	if(pParent)
	{
		//add parent's left to position
		return(pParent->GetLeft()+GetPosition().GetX());
	}
	else
	{
		//return x
		return(GetPosition().GetX());
	}
}

Uint16 CControl::GetRight() const
{
	//get parent
	CControl* pParent=(GetParent());
	//if a parent exists...
	if(pParent)
	{
		//add parent's left to position
		return(pParent->GetLeft()+GetPosition().GetX()+GetWidth());
	}
	else
	{
		//return x
		return(GetPosition().GetX()+GetWidth());
	}
}

Uint16 CControl::GetTop() const
{
	//get parent
	CControl* pParent=(GetParent());
	//if a parent exists...
	if(pParent)
	{
		//add parent's left to position
		return(pParent->GetTop()+GetPosition().GetY());
	}
	else
	{
		//return x
		return(GetPosition().GetY());
	}
}

Uint16 CControl::GetBottom() const
{
	//get parent
	CControl* pParent=(GetParent());
	//if a parent exists...
	if(pParent)
	{
		//add parent's left to position
		return(pParent->GetTop()+GetPosition().GetY()+GetHeight());
	}
	else
	{
		//return x
		return(GetPosition().GetY()+GetHeight());
	}
}

//set position
void CControl::SetPosition(gui::components::CPoint ptPosition)
{
	//set new position
	m_ptPosition=ptPosition;
}

//get canvas
gui::components::CCanvas* CControl::GetCanvas() const
{
	//get the canvas
	return(m_pCanvas);
}

//get main control
CControl* CControl::GetMainControl()
{
	//return main control
	return(s_pMainControl);
}

//get keyboard focus control
CControl* CControl::GetKeyboardFocus()
{
	//get keyboard focus
	return(s_pKeyboardFocus);
}

//set keyboard focus control
void CControl::SetKeyboardFocus(CControl* pControl)
{
	//set keyboard focus
	s_pKeyboardFocus=pControl;
}

//get mouse focus control
CControl* CControl::GetMouseFocus()
{
	//return mouse focus
	return(s_pMouseFocus);
}

//set mouse focus control
void CControl::SetMouseFocus(CControl* pControl)
{
	//set mouse focus
	s_pMouseFocus=pControl;
}

//get mouse hover control
CControl* CControl::GetMouseHover()
{
	//return mouse hover
	return(s_pMouseHover);
}

//set mouse focus control
void CControl::SetMouseHover(CControl* pControl)
{
	s_pMouseHover=pControl;
}

//check for focuses
bool CControl::IsMainControl()
{
	//check if this is main control
	return(this==GetMainControl());
}

bool CControl::HasKeyboardFocus()
{
	//check if this has keyboard focus
	return(this==GetKeyboardFocus());
}

bool CControl::HasMouseFocus()
{
	//check if this has mouse focus
	return(this==GetMouseFocus());
}

bool CControl::HasMouseHover()
{
	//check if this has mouse hovering
	return(this==GetMouseHover());
}

//set parent
void CControl::SetParent(CControl* pmhNewParent)
{
	//check for parent
	if(HasParent())
	{
		GetParent()->RemoveChild(this);
	}
	//change parent
	m_pParent=pmhNewParent;
	//check for parent
	if(HasParent())
	{
		GetParent()->AddChild(this);
	}
}

//get parent
CControl* CControl::GetParent() const
{
	//return parent
	return(m_pParent);
}

//has parent?
bool CControl::HasParent()
{
	//check for non-null parent
	return(GetParent()!=NULL);
}

//send message
bool CControl::SendMessageQ(MSGID MsgID,MSGPARM Parm1,MSGPARM Parm2,MSGPARM Parm3,MSGPARM Parm4)
{
	//attempt to handle message
	if(OnMessage(MsgID,Parm1,Parm2,Parm3,Parm4)) return(true);
	//send to parent, if available
	if(HasParent())
	{
		//send to parent
		return(GetParent()->SendMessageQ(MsgID,Parm1,Parm2,Parm3,Parm4));
	}
	else
	{
		//send to application
		return(CApplication::GetApplication()->SendMessageQ(MsgID,Parm1,Parm2,Parm3,Parm4));
	}
}

//process message(virtual)
bool CControl::OnMessage(MSGID MsgID,MSGPARM Parm1,MSGPARM Parm2,MSGPARM Parm3,MSGPARM Parm4)
{
	//false by default
	return(false);
}

//set ID
void CControl::SetID(Uint32 id)
{
	m_ID=id;
}

//get id
Uint32 CControl::GetID()
{
	return(m_ID);
}

} // namespace controls
} // namespace gui
