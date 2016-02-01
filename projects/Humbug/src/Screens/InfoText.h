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
#include <GuiLib/GUI/Components/TextAnimatorImpl.h>

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

        for(TextStorage::iterator it = m_pvecInfoTexts.begin(); it < end; ++it)
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

            if(text.IsDisposed()) {
                TextStorage::iterator it2 = it;
                removeList.push_back(it2);
            }

            //itpos++;
        }
        BOOST_FOREACH(TextStorage::iterator itpos, removeList)
        {
            m_pvecInfoTexts.release(itpos);
        }
    } // Draw

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
        p->SetPosition(m_rectPaint);
        m_rectPaint += p->VerticalSpacing();
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

/** @class InfoText:
 *  Detailed description.
 *  Todo: With a global TextAnimator chain. 
 *  @return TODO
 */
class InfoText3 : public gui::components::BaseDrawable {
public:
    typedef boost::function<void(const gui::components::CCanvas *, gui::components::BaseDrawable * text, gui::components::TextAnimatorData& mdata)> InfoTextModifierFunc;

private:
    int m_iTicks;
    int m_iStartTicks;
    TTF_Font* m_pTextFont;
    TTF_Font* m_pKeysFont;
    gui::components::CRectangle m_rectPaint;
    gui::components::CRectangle m_rectInitPos;
    typedef boost::ptr_vector<gui::components::CText> TextStorage;
    TextStorage m_pvecInfoTexts;
    typedef float seconds;
    typedef std::vector<InfoTextModifierFunc> TextModifierStorage;
    TextModifierStorage m_vecModifierVault;
    //typedef boost::ptr_vector<gui::components::TextAnimator> AnimatorStorage;
    //AnimatorStorage m_vecAnimatorVault;

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

    gui::components::CRectangle CalcRelativePosition(const gui::components::CRectangle& paintDimensions)
    {
        gui::components::CRectangle relative(paintDimensions);
        relative.X() = 0;
        relative.Y() = 0;
        return relative;
    }

    InfoText3(TTF_Font* textFont, TTF_Font* keysFont, const gui::components::CRectangle& paintDimensions) 
       // : BaseDrawable(paintDimensions.Position(gui::components::CRectangle::CompassRose::NW)), m_iTicks(0), m_iStartTicks(0),
       : BaseDrawable(gui::components::CPoint(paintDimensions.GetX(), paintDimensions.GetY())), m_iTicks(0), m_iStartTicks(0),
       m_pTextFont(textFont), m_pKeysFont(keysFont), m_rectPaint(CalcRelativePosition(paintDimensions)), m_rectInitPos(CalcRelativePosition(paintDimensions)) {}

    ~InfoText3() {}

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

        for(TextStorage::iterator it = m_pvecInfoTexts.begin(); it < end; ++it)
        {
            gui::components::CText & text = (*it);

            //BOOST_FOREACH(gui::components::CText & text, m_pvecInfoTexts)
            //{
            FROMTIME(time)
                //text.SetPosition(rect);
                // Todo: Let the global modifiers run here.
            gui::components::CRectangle r = text.GetCanvas()->GetDimension();
            r += text.GetPosition();
            r += GetPosition();
            text.RenderPut(canvas, r);
            //rect += text.VerticalSpacing();
            ENDTIMEBLOCK
                time += 0.25f;

            if(text.IsDisposed()) {
                TextStorage::iterator it2 = it;
                removeList.push_back(it2);
            }

            //itpos++;
        }
        BOOST_FOREACH(TextStorage::iterator itpos, removeList)
        {
            m_pvecInfoTexts.release(itpos);
        }
    } // Draw

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
        p->SetPosition(m_rectPaint);
        m_rectPaint += p->VerticalSpacing();
        m_pvecInfoTexts.push_back(p);
        return p;
    }

    void AddAnimator(InfoTextModifierFunc updfunc) {
        m_vecModifierVault.push_back(updfunc);
    }

    /*void AddAnimator(gui::components::TextAnimator* animator) {
        m_vecAnimatorVault.push_back(animator);
    }*/

    template <typename T, typename A>
    gui::components::TextAnimator* MoveTo(gui::components::CPoint point, gui::Hookable* hookable, float speed, gui::Timing::seconds timeIn, gui::Timing::seconds timeOut, const A& parEase)
    {
        auto mover = new gui::components::TextMover(point, hookable, speed, timeIn, timeOut, T(parEase));
        AddAnimator(mover);
        return mover;
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
