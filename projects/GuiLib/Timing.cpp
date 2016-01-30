//
#include "stdafx.h"

//
#include "Timing.h"
//
#include "GUI/Visual/Hookable.h"

namespace gui {
    void Timing::UpdateTimeFunction()
    {
        if(!m_fncUpdateTime) {
            return;
        }

        UpdateIdle(m_fncUpdateTime());
    }

    UpdateTimeFunc Timing::GetTimeUpdateFunction(const Hookable* hookable)
    {
        if(!hookable) {
            return NULL;
        }

        return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
    }

    Timing::Timing(UpdateTimeFunc updateFunction): Timing(0, updateFunction)
    {}

    Timing::Timing(Hookable* updater): Timing(0, GetTimeUpdateFunction(updater))
    {}

    Timing::Timing(int startupTicks, UpdateTimeFunc updateFunction): m_fncUpdateTime(updateFunction), m_iTicks(0), m_iStartTicks(startupTicks), m_fncLastCheck(NULL), m_timeLastCheck(0)
    {}

    Timing::Timing(int startupTicks, Hookable* updater): m_fncUpdateTime(GetTimeUpdateFunction(updater)), m_iTicks(0), m_iStartTicks(startupTicks), m_fncLastCheck(NULL),
                                                         m_timeLastCheck(0)
    {}

    seconds Timing::Convert(int ticks)
    {
        seconds result = static_cast<seconds>(ticks) / static_cast<seconds>(FRAMESPERSECOND);
        return result;
    }

    int Timing::TicksSinceStart()
    {
        UpdateTimeFunction();
        return m_iTicks - m_iStartTicks;
    }

    seconds Timing::SecondsSinceStart()
    {
        return Convert(TicksSinceStart());
    }

    bool Timing::IsBefore(seconds time, ConditionalTimeFunc func)
    {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing::IsBefore, boost::ref(*this), _1, _2);
        seconds now = SecondsSinceStart();
        bool result = now < time;
        if(result && func) {
            func();
        }

        return result;
    }

    bool Timing::IsAfter(seconds time, ConditionalTimeFunc func)
    {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing::IsAfter, boost::ref(*this), _1, _2);
        seconds now = SecondsSinceStart();
        bool result = now > time;
        if(result && func) {
            func();
        }

        return result;
    }

    bool Timing::IsAt(seconds time, ConditionalTimeFunc func)
    {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing::IsAt, boost::ref(*this), _1, _2);
        seconds now = SecondsSinceStart();
        bool result = now == time;
        if(result && func) {
            func();
        }

        return result;
    }

    bool Timing::IsAtOrAfter(seconds time, ConditionalTimeFunc func)
    {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing::IsAtOrAfter, boost::ref(*this), _1, _2);
        seconds now = SecondsSinceStart();
        bool result = now >= time;
        if(result && func) {
            func();
        }

        return result;
    }

    Timing::operator bool() const
    {
        bool result = m_fncLastCheck(m_timeLastCheck, NULL);
        return result;
    }
}
