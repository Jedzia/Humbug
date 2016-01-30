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

    TimingChain& TimingChain::Add(seconds time, Timing::ConditionalTimeFunc func, seconds time2)
    {
        TimingChain* timing_chain = this;
        //TimingChain* timing_chain = new TimingChain(m_pUpdater);

        /*if (m_timTimer.IsAfter(time + m_secStarttime))
        {
            return *timing_chain;
        }

        m_timTimer.IsBefore(time + m_secStarttime, func);*/
        seconds after = m_secStarttime;
        seconds before = time + m_secStarttime;
        m_timTimer.IsAfterAndBefore(after, before, func);
        
        timing_chain->m_secStarttime = time + m_secStarttime;
        return *timing_chain;
    }

    TimingChain& TimingChain::At(seconds after, seconds before, Timing::ConditionalTimeFunc func)
    {
        m_timTimer.IsAfterAndBefore(after, before, func);
        return *this;
    }

    void TimingChain::Commit(seconds loopAfter)
    {
        m_secStarttime = 0;
    }
}
