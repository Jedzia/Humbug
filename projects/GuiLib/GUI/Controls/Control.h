/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Control.h class.
 * \folder     $(folder)
 * \file       Control.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef CONTROL_H__
#define CONTROL_H__

#include "../Components/Canvas.h"
#include "../Visual/Application.h"
#include "../Visual/MessageHandler.h"
#include <list>

namespace gui {
  namespace controls {
//CControl class
//abstracts a user interface control
    class CControl {
private:

        //parent
        CControl* m_pParent;
        //list of child controls
        std::list<CControl *> m_lstChildren;
        //list of windows to bring to front
        static std::list<CControl *> s_lstUpdate;
        //list of windows to close
        static std::list<CControl *> s_lstClose;
        //canvas used by window
        gui::components::CCanvas* m_pCanvas;
        //position
        gui::components::CPoint m_ptPosition;
        //id
        Uint32 m_ID;
        //static pointer to main control
        static CControl* s_pMainControl;
        //keyboard focus
        static CControl* s_pKeyboardFocus;
        //mouse focus
        static CControl* s_pMouseFocus;
        //mouse hovering
        static CControl* s_pMouseHover;

protected:

        bool m_ptIsDirty;

public:

        //master control constructor
        CControl(gui::components::CCanvas* pCanvas);
        //child control constructor
        CControl(CControl* pParent, gui::components::CRectangle rcDimensions, Uint32 id, bool invalidate = true);
        //destructor
        virtual ~CControl();
        //set parent
        void SetParent(CControl* pmhNewParent);

        //get parent
        CControl * GetParent();

        //has parent?
        bool HasParent();

        //set ID
        void SetID(Uint32 id);

        //get id
        Uint32 GetID();

        //send message
        bool SendMessageQ(MSGID MsgID, MSGPARM Parm1 = NULL, MSGPARM Parm2 = NULL, MSGPARM Parm3 = NULL,
                MSGPARM Parm4 = NULL);

        //process message(virtual)
        virtual bool OnMessage(MSGID MsgID, MSGPARM Parm1, MSGPARM Parm2, MSGPARM Parm3, MSGPARM Parm4);

        //add child handler
        void AddChild(CControl* pControl);

        //remove child handler
        void RemoveChild(CControl* pControl);

        //bring to front
        void BringToFront();

        //close
        void Close();

        //update all
        static void Update();

        //redraw entire system
        static void Redraw();

        //draw control
        void Draw();

        void Invalidate();

        //customize redrawing
        virtual void OnDraw();

        //event handling
        virtual bool OnEvent(SDL_Event* pEvent);

        //keyboard events
        virtual bool OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);

        virtual bool OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

        //mouse events
        virtual bool OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight, bool bMiddle);

        virtual bool OnLButtonDown(Uint16 x, Uint16 y);

        virtual bool OnLButtonUp(Uint16 x, Uint16 y);

        virtual bool OnRButtonDown(Uint16 x, Uint16 y);

        virtual bool OnRButtonUp(Uint16 x, Uint16 y);

        virtual bool OnMButtonDown(Uint16 x, Uint16 y);

        virtual bool OnMButtonUp(Uint16 x, Uint16 y);

        //static event filter
        static bool FilterEvent(SDL_Event* pEvent);

        //get position
        gui::components::CPoint GetPosition();

        //get width and height
        Uint16 GetWidth();

        Uint16 GetHeight();

        //get edges in global coords
        Uint16 GetLeft();

        Uint16 GetRight();

        Uint16 GetTop();

        Uint16 GetBottom();

        //set position
        void SetPosition(gui::components::CPoint ptPosition);

        //get canvas
        gui::components::CCanvas * GetCanvas();

        //get main control
        static CControl * GetMainControl();

        //get keyboard focus control
        static CControl * GetKeyboardFocus();

        //set keyboard focus control
        static void SetKeyboardFocus(CControl* pControl);

        //get mouse focus control
        static CControl * GetMouseFocus();

        //set mouse focus control
        static void SetMouseFocus(CControl* pControl);

        //get mouse hover control
        static CControl * GetMouseHover();

        //set mouse focus control
        static void SetMouseHover(CControl* pControl);

        //check for focuses
        bool IsMainControl();

        bool HasKeyboardFocus();

        bool HasMouseFocus();

        bool HasMouseHover();
    };
  } // namespace controls
} // namespace gui
#endif //
