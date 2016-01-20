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
      class CControl;

      //CControl class
//abstracts a user interface control

    class ControlPainterParameters {
        bool m_bDrawn;

    public:
        explicit ControlPainterParameters()
            : m_bDrawn(false)
        {
        }


        bool IsDrawn() const
        {
            return m_bDrawn;
        }

        void SetDrawn(const bool drawn)
        {
            m_bDrawn = drawn;
        }

        //__declspec(property(get = IsDrawn, put = SetDrawn)) bool MBxDrawn;
    };

    class ControlPainter {
        const CControl& parent;
        CControl* pChild;

    protected:
        ~ControlPainter()
        {
        }

    public:
        ControlPainter(const CControl& parent, CControl* const p_child)
            : parent{parent},
              pChild{p_child}
        {
        }

        virtual void DrawChild(const CControl& parent, CControl* pChild, ControlPainterParameters& param) = 0;
    };

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
        components::CCanvas* m_pCanvas;
        //position
        components::CPoint m_ptPosition;
        //offsetfor scrolling
        components::CRectangle m_rectOffset;
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
        bool m_bUsesSDL2Render;

    public:

        //master control constructor
        explicit CControl(components::CCanvas* pCanvas, bool usesSDL2Render = false);
        //child control constructor
        CControl(CControl* pParent, components::CRectangle rcDimensions, Uint32 id, bool invalidate = true, bool usesSDL2Render = false);
        //destructor
        virtual ~CControl();
        //set parent
        void SetParent(CControl* pmhNewParent);

        //get parent
        CControl * GetParent() const;

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
        
        virtual void DrawChild(const CControl& parent, CControl* pChild);
        //draw control
        void Draw();
        void Invalidate();

        //customize redrawing
        virtual void OnDraw();

        //event handling
        virtual bool OnEvent(SDL_Event* pEvent);

        //keyboard events
        virtual bool OnKeyDown(SDL_Keycode sym, Uint16 mod);

        virtual bool OnKeyUp(SDL_Keycode sym, Uint16 mod);

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
        components::CPoint GetPosition() const;
        
        // get visible area for the painter.
        virtual components::CRectangle VisibleArea() const;

        /*// get scrolling offset reference
        components::CRectangle& Offset();*/

        // get scrolling offset
        components::CRectangle GetOffset() const;

        // set offset for scrolling
        void SetOffset(const components::CRectangle& m_rect_offset);

        // get visual bounds check
        virtual components::CRectangle Intersects(const components::CRectangle& rcDst) const;

        //get width and height
        virtual Uint16 GetWidth() const;

        virtual Uint16 GetHeight() const;

        //get edges in global coords
        Uint16 GetLeft() const;

        Uint16 GetRight() const;

        Uint16 GetTop() const;

        Uint16 GetBottom() const;

        //set position
        void SetPosition(components::CPoint ptPosition);

        //get canvas
        components::CCanvas * GetCanvas() const;

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
