/*---------------------------------------------------------*/
/*!
* This file is part of Humbug, the strangest game ever.
* License details can be found in the file COPYING.
* Copyright (c) 2013, EvePanix. All rights reserved.
*
* \brief      This file contains the definition of
*             the ZoomInScreen2.h class.
* \file       ZoomInScreen2.h
* \date       2016-01-09
* \author     Jedzia.
*
* modified    2016-01-09, Jedzia
*/
/*---------------------------------------------------------*/
#ifndef HUMBUG_SCREENS_ZoomInScreen2_H
#define HUMBUG_SCREENS_ZoomInScreen2_H
#include "boost/smart_ptr/scoped_ptr.hpp"
#include <GuiLib/GUI/Components/Screen.h>

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
class DebugOverlay;
/** @class ZoomInScreen2:
 *  A one page static Page (Screen) with a selection menu.
 */
class ZoomInScreen2 : public gui::components::Screen {
public:

    /** Initializes a new instance of the <see cref="ZoomInScreen2"/> class.
    *  Detailed description.
    *  @param loader File loading facility.
    *  @param background the background canvas used by this Screen.
    */
    ZoomInScreen2(FileLoader& loader, gui::components::CCanvas* background);
    ~ZoomInScreen2();

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
    void OnKeyDown(SDL_Keycode sym, Uint16 mod) override;

private:

    struct ZoomInScreen2Impl;
    boost::scoped_ptr<ZoomInScreen2Impl> pimpl_;

    FileLoader& m_Loader;
    Uint8 x;
    gui::components::CColor mcol;
    boost::shared_ptr<gui::components::CCanvas> m_pBackground;
};
}

#endif // ifndef HUMBUG_SCREENS_ZoomInScreen2_H
