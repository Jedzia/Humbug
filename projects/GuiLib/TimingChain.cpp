//
#include "stdafx.h"

//
#include "TimingChain.h"
//
#include "GUI/Visual/Hookable.h"

namespace gui {
    TimingChain::TimingChain(Hookable* updater) : m_pUpdater(updater), m_secStarttime(0), m_timTimer(updater)
    {
    }

    TimingChain& TimingChain::At(seconds time, Timing::ConditionalTimeFunc func, seconds time2)
    {
        //m_timTimer.IsBefore(time + m_secStarttime, func);
        seconds after = m_secStarttime;
        seconds before = time + m_secStarttime;
        m_timTimer.IsAfterAndBefore(after, before, func);
        
        m_secStarttime += time;
        return *this;
    }

    TimingChain& TimingChain::At(seconds after, seconds before, Timing::ConditionalTimeFunc func)
    {
        m_timTimer.IsAfterAndBefore(after, before, func);
        return *this;
    }

    void TimingChain::Commit(seconds loopAfter)
    {
        if (loopAfter && m_timTimer.IsAfter(m_secStarttime))
        {
            m_timTimer.Reset();
        }

        m_secStarttime = 0;
    }
}
