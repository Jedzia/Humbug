/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the InfoText.h class.
 * \file       InfoText.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include <GuiLib/GUI/Components/Rectangle.h>
#include <GuiLib/GUI/Components/Text.h>
#include <boost/foreach.hpp>

namespace humbug {
/** @class InfoText:
 *  Detailed description.
 *  @return TODO
 */
class InfoText2 {
    int m_iFrames;
    int m_iInitFrame;
    TTF_Font* m_pTextFont;
    TTF_Font* m_pKeysFont;
    gui::components::CRectangle m_rectPaint;
    boost::ptr_vector<gui::components::CText> m_pvecInfoTexts;
    typedef float seconds;

    /** Brief description of InfoText2, GetTime
     *  Detailed description.
     *  @return TODO
     */
    seconds GetTime() const {
        return (m_iFrames - m_iInitFrame) / 30.0f;
    }
#define FROMTIME(x) if(GetTime() > (x)) {
#define ENDTIMEBLOCK \
    }

public:

    InfoText2(TTF_Font* textFont, TTF_Font* keysFont, const gui::components::CRectangle& paintDimensions) : m_iFrames(0), m_iInitFrame(0),
        m_pTextFont(textFont), m_pKeysFont(keysFont), m_rectPaint(paintDimensions) {}
    ~InfoText2() {}

    /** Brief description of InfoText2, Draw
     *  Detailed description.
     *  @param canvas TODO
     */
    void Draw(const gui::components::CCanvas* canvas) {
        gui::components::CRectangle rect = m_rectPaint;

        float time = 0.25f;
        BOOST_FOREACH(gui::components::CText & text, m_pvecInfoTexts)
        {
            FROMTIME(time)
            text.RenderPut(canvas, rect);
            rect += text.VerticalSpacing();
            ENDTIMEBLOCK
                time += 0.25f;
        }
    }     // Draw
    /** Brief description of InfoText2, Idle
     *  Detailed description.
     *  @param ticks TODO
     */
    void Idle(int ticks) {
        if(!m_iInitFrame) {
            m_iInitFrame = ticks;
        }

        m_iFrames = ticks;
    }
    //typename boost::detail::sp_if_not_array<T>::type OwnChildPainter(Arg1 && arg1, Args && ...
    // args){

    template<class T, class Arg1, class ... Args>
    typename T * makeCText(Arg1 && arg1, Args && ... args) {
        //auto painter = boost::make_shared<T>(arg1, args ...);
        //auto painter2 = std::allocate_shared<T>(arg1, args ...);
        //painter.reset();
        //OwnChildPainter(painter);
        //auto p = new CText(boost::detail::sp_forward<Arg1>(arg1),
        // boost::detail::sp_forward<Args>(args)...);
        auto p = new T(boost::detail::sp_forward<Arg1>(arg1), boost::detail::sp_forward<Args>(args) ...);
        m_pvecInfoTexts.push_back(p);
        return p;
    }

    /*template<class T, class Arg1, class ... Args>
       typename boost::detail::sp_if_not_array<T>::type OwnChildPainter(Arg1 && arg1, Args && ...
       args){
       //auto painter = boost::make_shared<T>(arg1, args ...);
       //auto painter2 = std::allocate_shared<T>(arg1, args ...);
       //painter.reset();
       //OwnChildPainter(painter);
       //auto p = new CText(boost::detail::sp_forward<Arg1>(arg1),
       boost::detail::sp_forward<Args>(args)...);
       auto p = boost::make_shared<T>(boost::detail::sp_forward<Arg1>(arg1),
       boost::detail::sp_forward<Args>(args)...);
       return p;
       }*/
};
}
