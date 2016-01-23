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
    int m_iTicks;
    int m_iStartTicks;
    TTF_Font* m_pTextFont;
    TTF_Font* m_pKeysFont;
    gui::components::CRectangle m_rectPaint;
    gui::components::CRectangle m_rectInitPos;
    typedef boost::ptr_vector<gui::components::CText> TextStorage;
    TextStorage m_pvecInfoTexts;
    typedef float seconds;

    /** Brief description of InfoText2, GetTime
     *  Detailed description.
     *  @return TODO
     */
    seconds GetTime() const {
        return (m_iTicks - m_iStartTicks) / 30.0f;
    }
#define FROMTIME(x) if(GetTime() > (x)) {
#define ENDTIMEBLOCK \
    }

public:

    InfoText2(TTF_Font* textFont, TTF_Font* keysFont, const gui::components::CRectangle& paintDimensions) : m_iTicks(0), m_iStartTicks(0),
        m_pTextFont(textFont), m_pKeysFont(keysFont), m_rectPaint(paintDimensions), m_rectInitPos(paintDimensions) {}

    ~InfoText2() {}

    /** Brief description of InfoText2, Draw
     *  Detailed description.
     *  @param canvas TODO
     */
    void Draw(const gui::components::CCanvas* canvas) {
        //gui::components::CRectangle rect = m_rectPaint;
        //std::vector<gui::components::CText*> removeList;
        std::vector<TextStorage::iterator> removeList;
        
        float time = 0.25f;
        //int itpos = 0;
        TextStorage::iterator end = m_pvecInfoTexts.end();
        for (TextStorage::iterator it = m_pvecInfoTexts.begin(); it < end; ++it)
        {
            gui::components::CText & text = (*it);

        //BOOST_FOREACH(gui::components::CText & text, m_pvecInfoTexts)
        //{
            FROMTIME(time)
            //text.SetPosition(rect);
            //text.RenderPut(canvas, rect);
            text.RenderPut(canvas);
            //rect += text.VerticalSpacing();
            ENDTIMEBLOCK
            time += 0.25f;

            if (text.IsDisposed())
            {
                TextStorage::iterator it2 = it;
                removeList.push_back(it2);
            }
            //itpos++;
        }

        BOOST_FOREACH(TextStorage::iterator itpos, removeList)
        {
            m_pvecInfoTexts.release(itpos);
        }
    }    
    
    // Draw
    /** Brief description of InfoText2, Idle
     *  Detailed description.
     *  @param ticks TODO
     */
    void UpdateIdle(int ticks) {
        if(!m_iStartTicks) {
            m_iStartTicks = ticks;
        }

        m_iTicks = ticks;
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
        p->SetPosition(m_rectInitPos);
        m_rectInitPos += p->VerticalSpacing();
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
