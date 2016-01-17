/*---------------------------------------------------------*/
/*!
* This file is part of Humbug, the strangest game ever.
* License details can be found in the file COPYING.
* Copyright (c) 2013, EvePanix. All rights reserved.
*
* \brief      This file contains the definition of
*             the MenuScreen.h class.
* \file       MenuScreen.h
* \date       2016-01-09
* \author     Jedzia.
*
* modified    2016-01-09, Jedzia
*/
/*---------------------------------------------------------*/
#ifndef HUMBUG_SCREENS_MenuScreen_H
#define HUMBUG_SCREENS_MenuScreen_H
#include "boost/smart_ptr/scoped_ptr.hpp"
#include <GuiLib/GUI/Components/Screen.h>
#include <GuiLib/GUI/Controls/LineMenu.h>

class FileLoader;
namespace gui {
class CSprite;
class CSpriteManager;
namespace components {
    class CCanvas;
class CText;
class CTextScroller;
}
}

namespace humbug {
    class InfoText;
    class DebugOverlay;
/** @class MenuScreen:
 *  A one page static Page (Screen) with a selection menu.
 */
class MenuScreen : public gui::components::Screen, public gui::CMaster {
public:

    gui::components::CMainCanvas* GetMainCanvas() const override;

    /** Initializes a new instance of the <see cref="MenuScreen"/> class.
        *  Detailed description.
        *  @param loader File loading facility.
        *  @param background the background canvas used by this Screen.
        */
    MenuScreen(FileLoader& loader, gui::components::CCanvas* background);
    ~MenuScreen();

    /** Initialization frame-loop.
    *  Is called once on initialization.
    *  @param argc Dummy parameter.
    * @param argv Dummy parameter.
    * @return Screen::OnInit(argc, argv) or true on success.
    */
    bool OnInit(int argc, char* argv[]) override;

    /** Idle frame-loop.
    *  Is called once per frame, before OnDraw().
    *  @param ticks frame ticks counter.
    */
    void OnIdle(int ticks) override;

    /** Draw frame-loop.
    *  Is called once per frame.
    */
    void OnDraw() override;

    /** Update frame-loop.
    *  Is called once per frame, after OnDraw().
    */
    void OnUpdate() override;

    /** Update event-loop.
    *  Override to handle SDL events.
    */
    void OnEvent(SDL_Event* pEvent) override;

private:

    virtual void MenuSelectionChanged(int selectedLabel) const;

    struct MenuScreenImpl;
    boost::scoped_ptr<MenuScreenImpl> pimpl_;
    FileLoader& m_Loader;
    Uint8 x;
    gui::components::CColor mcol;
    boost::shared_ptr<gui::components::CCanvas> m_pBackground;
    boost::scoped_ptr<gui::components::CText> m_pScrollText;
    boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
    boost::scoped_ptr<gui::CSpriteManager> m_pSprMgr;
    boost::scoped_ptr<gui::components::LineMenu> m_pLineMenu;
    boost::scoped_ptr<InfoText> m_pInfoText;
    gui::components::LineMenu::menu_changed_connection_t m_connection;

    boost::scoped_ptr<gui::HookableManager> m_HookMgr;
    gui::HookableManager* HookMgr() const { return m_HookMgr.get(); }


    int label1;
    int label2;
    int label3;
    int label4;
    int label5;

};
}

#endif // ifndef HUMBUG_SCREENS_MenuScreen_H
