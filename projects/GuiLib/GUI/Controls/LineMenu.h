/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the LineMenu.h class.
 * \folder     $(folder)
 * \file       LineMenu.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef GUI_LineMenu_H
#define GUI_LineMenu_H

#include "../../Filesystem/FileLoader.h"
#include "../../GUI/Components/Canvas.h"
#include "../../GUI/Components/Image.h"
#include "../../GUI/Components/Text.h"
#include "Control.h"
#include "Label.h"
#include "../Detail/Signals.h"

namespace gui {
namespace components {
/** @class LineMenu: 
 *  Detailed description.
 *
 */
class LineMenu : public controls::CControl { 
public:
    typedef bs::signal<void(int selectedLabel)>  menu_changed_signal_t;
    typedef bs::connection  menu_changed_connection_t;

    // LineMenu(const FileLoader& loader, CCanvas* pCanvas);
    LineMenu(FileLoader& loader, CControl* pParent, Uint32 id, const std::string& name, const CRectangle& dimensions, const CRectangle& padding);
    ~LineMenu();

    menu_changed_connection_t connect(menu_changed_signal_t::slot_function_type subscriber)
    {
        return m_sigMenuChanged.connect(subscriber);
    }

    void disconnect(menu_changed_connection_t subscriber)
    {
        subscriber.disconnect();
    }

    void OnDraw() override;

    /** EventLoop update.
        *  Call during the event-loop method of your screen.
        *  @param pEvent Use this to pass the event parameter of the event loop.
        */
    void HookEventloop(SDL_Event* pEvent, bool onlyRecognizeQuit = false);

    /** Idle update.
     *  Call during the idle method of your display loop.
     *  @param ticks Use this to pass the ticks parameter of the idle loop.
     */
    void IdleSetVars(int ticks);

    /** Create a text label and add it to the overlay.
     *  Creates a new text label with the specified text and adds it to the debug overlay.
     *  @param text The optional caption of the label. If not specified, an auto-generated text is used.
     *  @return a unique identifier of the label. This id can be used by functions like
     *SetTextLabelText.
     */
    int AddTextLabel(const std::string& text = "");

    /** Sets the text of a label.
     *  Use this method to set the text of a label, created by AddTextLabel().
     *  @param id The identifikation number of the text label.
     *  @param text The new caption of the label.
     */
    void SetTextLabelText(int id, const std::string& text);

    void NavigateUp();
    void NavigateDown();

    bool OnMouseMove(Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight, bool bMiddle) override;
protected:
    void CalculateBounds();
    CRectangle VisibleArea();

private:

    void Init(CControl* pParent);
    CRectangle InitRect(const FileLoader& loader);
    static void DrawRect(CCanvas* canvas, const CRectangle& dimensions, const CColor& color);

    static int LabelId;
    menu_changed_signal_t m_sigMenuChanged;
    const FileLoader& m_pLoader;
    TTF_Font* m_pDebugfont;
    boost::scoped_ptr<CText> m_pTextA;
    boost::ptr_map<int, controls::CLabel> m_mLabels;
    int m_iLastAutoLabelPosition;
    std::string m_sName;
    CRectangle m_rPadding;
    bool m_bOldstate;
    CCanvas* m_tmpcanvas;
    bool m_bFlank;
    int m_iTicks;
    int m_iSelectedLabel;

    int m_iScrollPosition;
};
}
}
#endif // GUI_LineMenu_H
