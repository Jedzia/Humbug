/*---------------------------------------------------------*/
/*!
* This file is part of Humbug, the strangest game ever.
* License details can be found in the file COPYING.
* Copyright (c) 2013, EvePanix. All rights reserved.
*
* \brief      This file contains the definition of
*             the Template.h class.
* \file       Template.h
* \date       2016-01-09
* \author     Jedzia.
*
* modified    2016-01-09, Jedzia
*/
/*---------------------------------------------------------*/
#ifndef HUMBUGGL_SCREENS_Template_H
#define HUMBUGGL_SCREENS_Template_H
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
/** @class Template:
 *  A one page static Page (Screen) with a selection menu.
 */
class Template : public gui::components::Screen {
public:

    /** Initializes a new instance of the <see cref="Template"/> class.
    *  Detailed description.
    *  @param loader File loading facility.
    *  @param background the background canvas used by this Screen.
    */
    Template(FileLoader& loader, gui::components::CCanvas* background);
    ~Template();

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

private:

    struct TemplateImpl;
    boost::scoped_ptr<TemplateImpl> pimpl_;

    FileLoader& m_Loader;
    Uint8 x;
    gui::components::CColor mcol;
    boost::shared_ptr<gui::components::CCanvas> m_pBackground;
    boost::scoped_ptr<gui::components::CText> m_pScrollText;
    boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
    boost::scoped_ptr<gui::CSpriteManager> m_pSprMgr;
    boost::scoped_ptr<DebugOverlay> m_pOverlay;
};
}

#endif // ifndef HUMBUGGL_SCREENS_Template_H
