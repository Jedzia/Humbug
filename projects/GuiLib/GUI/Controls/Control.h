/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Control.h class.
 * \file       Control.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef CONTROL_H__
#define CONTROL_H__

#include "../Components/Canvas.h"
#include "../Visual/MessageHandler.h"
#include <boost/smart_ptr/make_shared_object.hpp>
#include <list>

namespace gui {
namespace controls {
class CControl;

//CControl class
//abstracts a user interface control

/** @class ControlPainterParameters:
 *  Detailed description.
 */
class ControlPainterParameters {
    bool m_bDrawn;

public:

    explicit ControlPainterParameters()
        : m_bDrawn(false)
    {}

    /** Brief description of ControlPainterParameters, IsDrawn
     *  Detailed description.
     *  @return TODO
     */
    bool IsDrawn() const {
        return m_bDrawn;
    }
    /** Brief description of ControlPainterParameters, SetDrawn
     *  Detailed description.
     *  @param drawn TODO
     */
    void SetDrawn(const bool drawn){
        m_bDrawn = drawn;
    }
    //__declspec(property(get = IsDrawn, put = SetDrawn)) bool MBxDrawn;
};

/** @class DetailedControlPainter:
 *  Detailed description.
 */
class DetailedControlPainter {
    //const CControl& parent;
    //CControl* pChild;

public:

    DetailedControlPainter()
    //DetailedControlPainter(const CControl& parent, CControl* const p_child)
    //: parent{parent}, pChild{p_child}
    {}

    virtual ~DetailedControlPainter()
    {}

    /** Brief description of DetailedControlPainter, BeforeDrawChild
     *  Detailed description.
     *  @param parent TODO
     *  @param pChild TODO
     *  @param param TODO
     */
    virtual void BeforeDrawChild(const CControl& parent, CControl* pChild, ControlPainterParameters&
            param)
    {}

    virtual void DrawChild(const CControl& parent, CControl* pChild, ControlPainterParameters& param) = 0;

    /** Brief description of DetailedControlPainter, AfterDrawChild
     *  Detailed description.
     *  @param parent TODO
     *  @param pChild TODO
     *  @param param TODO
     */
    virtual void AfterDrawChild(const CControl& parent, CControl* pChild, ControlPainterParameters&
            param)
    {}

    /*inline DetailedControlPainter* new_clone(const DetailedControlPainter& c)
       {
        return NULL;
       }*/
};

/** @class CControl:
 *  Detailed description.
 */
class CControl {
    typedef boost::function<void (const CControl& parent, CControl * pChild, ControlPainterParameters& param)> ControlPainter;
    typedef std::vector<ControlPainter> ControlPainterStorage;
    ControlPainterStorage m_vecChildrenFuncPainter;

    typedef boost::shared_ptr<DetailedControlPainter> DetailedControlPainterPtr;
    typedef std::vector<DetailedControlPainterPtr> DetailedControlPainterStorage;
    DetailedControlPainterStorage m_vecChildrenDetailPainter;

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

    /** Get parent control.
     *  Gets the parent of this instance.
     *  @return the parent of this control or NULL if no parent exists.
     */
    CControl * GetParent() const;

    //has parent?
    bool HasParent() const;

    /** Set ID.
     *  Sets the identification number of this instance.
     *  @param id the ID to set.
     */
    void SetID(Uint32 id);

    //get id
    Uint32 GetID() const;

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

    std::list<CControl*>::size_type GetNumChildren() const
    {
        return m_lstChildren.size();
    }

    //update all
    static void Update();

    //redraw entire system
    static void Redraw();

    // add a children control painter via functor.
    void AddChildPainter(const ControlPainter& updfunc);

    // add a children control painter. takes ownership
    void MakeChildPainter(DetailedControlPainter* painter);

    // add a children control painter. takes ownership
    void MakeChildPainter(boost::shared_ptr<DetailedControlPainter> painter);

    // make and add a children control painter.
    template<class T, class Arg1, class ... Args>
    typename boost::detail::sp_if_not_array<T>::type MakeChildPainter(Arg1 && arg1, Args && ... args){
        auto painter = boost::make_shared<T>(arg1, args ...);
        MakeChildPainter(painter);
        return painter;
    }
    virtual void DrawChild(const CControl& parent, CControl* pChild) const;

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
    bool IsMainControl() const;

    bool HasKeyboardFocus() const;

    bool HasMouseFocus() const;

    bool HasMouseHover() const;
};
}   // namespace controls
} // namespace gui
#endif //
