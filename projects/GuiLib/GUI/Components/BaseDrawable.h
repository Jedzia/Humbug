/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BaseDrawable.h class.
 * \file       BaseDrawable.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include "../Disposable.h"
#include "Rectangle.h"

namespace gui {
namespace components {
class CCanvas;

// Todo: move to #include "BaseDrawable.h" and apply this to gui::components::CText
template<class T1, class T2, class T2data>
class BaseModifierWorker {
public:

    typedef boost::function<void (const CCanvas *, T1 * text, T2data& mdata)> DrawableAnimatorFunc;

private:

    typedef std::vector<DrawableAnimatorFunc> TextModifierStorage;
    TextModifierStorage m_vecModifierVault;
    //typedef std::vector<gui::components::CText::TextModifierFunc> TextModifierStorage;
    //TextModifierStorage m_vecModifierVault;
    typedef boost::ptr_vector<T2> AnimatorStorage;
    AnimatorStorage m_vecAnimatorVault;

protected:

    /** Brief description of BaseModifierWorker, ApplyModifiers
     *  Detailed description.
     *  @param target TODO
     *  @param text TODO
     *  @param srcRect TODO
     *  @param dstRect TODO
     */
    void ApplyModifiers(const CCanvas* target, T1* modifiedItem, CRectangle& srcRect,
            CRectangle& dstRect) {
        target->Lock();

        T2data mdata(&srcRect, &dstRect);

        if(!m_vecModifierVault.empty()) {
            typename TextModifierStorage::iterator end = m_vecModifierVault.end();

            for(typename TextModifierStorage::iterator it = m_vecModifierVault.begin(); it < end; ++it)
            {
                (*it)(target, modifiedItem, mdata);
                if(mdata.markedForDeletion) {
                    //m_vecModifierVault.pop_back();
                    //TextModifierStorage::iterator ex;
                    m_vecModifierVault.erase(it);
                    mdata.markedForDeletion = false;
                    // Todo: better fill a deleter list and erase after loop.
                    break;
                }
            }
        }

        target->Unlock();
    }     // BaseModifierWorker::ApplyModifiers

    /** Brief description of BaseModifierWorker, ApplyAnimators
     *  Detailed description.
     *  @param target TODO
     *  @param text TODO
     *  @param srcRect TODO
     *  @param dstRect TODO
     */
    void ApplyAnimators(const CCanvas* target, T1* modifiedItem,
            CRectangle& srcRect, CRectangle& dstRect) {
        using namespace components;
        target->Lock();

        T2data mdata(&srcRect, &dstRect);

        if(!m_vecAnimatorVault.empty()) {
            typename AnimatorStorage::iterator end = m_vecAnimatorVault.end();

            for(typename AnimatorStorage::iterator it = m_vecAnimatorVault.begin(); it < end; ++it)
            {
                (*it)(target, modifiedItem /* was this */, mdata);
                if(mdata.markedForDeletion) {
                    T2* savedAnimator = (*it).nextAnimator;

                    if(savedAnimator) {
                        //savedAnimator->x = (*it).x;
                        //savedAnimator->y = (*it).y;
                        (*it).nextAnimator = NULL;
                        m_vecAnimatorVault.erase(it);
                        mdata.markedForDeletion = false;
                        AddAnimator(savedAnimator);
                        break;
                    }

                    m_vecAnimatorVault.erase(it);
                    mdata.markedForDeletion = false;
                    // Todo: better fill a deleter list and erase after loop.
                    break;
                }
            }
        }

        target->Unlock();
    }     // BaseModifierWorker::ApplyAnimators

public:

    /** Brief description of BaseModifierWorker, AddAnimator
     *  Detailed description.
     *  @param animator TODO
     */
    void AddAnimator(T2* animator) {
        m_vecAnimatorVault.push_back(animator);
    }

    /** Brief description of BaseModifierWorker, AddAnimator
     *  Detailed description.
     *  @param updfunc TODO
     */
    void AddAnimator(const DrawableAnimatorFunc& updfunc) {
        m_vecModifierVault.push_back(updfunc);
    }
};

/** @class BaseDrawable:
 *  Base class for all items that draw on their member canvas.
 *  See: BaseShape's are lightweight items that draw themselves to a CCanvas, but don't own a
 *CCanvas.
 */
class BaseDrawable : public Disposable {
public:

    explicit BaseDrawable(const CPoint& m_pt_position)
        : m_ptPosition{m_pt_position}
    {}

    /** Get current text Position.
     *  Gets the current text position of this instance.
     *  @return the point of the text position.
     */
    CPoint GetPosition() const { return m_ptPosition; }

    /** Set text Position.
     *  Sets the text position of this instance used by RenderPut(const CCanvas* canvas).
     *  @param position The value of the text position.
     */
    void SetPosition(const CPoint& position) { m_ptPosition = position; }

private:

    CPoint m_ptPosition;
};
}
}
