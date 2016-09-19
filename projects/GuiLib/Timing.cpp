//
#include "stdafx.h"

//
#include "Timing.h"
//
#include "GUI/Visual/Hookable.h"

namespace gui {
void Timing::UpdateTimeFunction() {
    if(!m_fncUpdateTime) {
        // warning ! when no update function is set:
        // every call to here updates the timer
        // m_iTicks++;

        // you have to manually call void UpdateIdle(int ticks)
        return;
    }

    UpdateIdle(m_fncUpdateTime());
}

UpdateTimeFunc Timing::GetTimeUpdateFunction(const Hookable* hookable) {
    if(!hookable) {
        return NULL;
    }

    return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
}

Timing::Timing(UpdateTimeFunc updateFunction) : Timing(0, updateFunction)
{}

Timing::Timing(const Hookable* updater) : Timing(0, GetTimeUpdateFunction(updater))
{}

Timing::Timing(int startupTicks, UpdateTimeFunc updateFunction) : m_fncUpdateTime(updateFunction), m_iTicks(0), m_iStartTicks(startupTicks),
    m_fncLastCheck(NULL), m_timeLastCheck(0)
{}

Timing::Timing(int startupTicks, Hookable* updater) : m_fncUpdateTime(GetTimeUpdateFunction(updater)), m_iTicks(0), m_iStartTicks(
            startupTicks), m_fncLastCheck(NULL),
    m_timeLastCheck(0)
{}

seconds Timing::Convert(int ticks) {
    seconds result = static_cast<seconds>(ticks) / static_cast<seconds>(FRAMESPERSECOND);
    return result;
}

int Timing::TicksSinceStart() {
    UpdateTimeFunction();
    return m_iTicks - m_iStartTicks;
}

seconds Timing::SecondsSinceStart() {
    return Convert(TicksSinceStart());
}

float round(float d) {
    return floor(d + 0.5f);
}

float rangeMap(seconds now, float outMin, float outMax, float inMin, float inMax) {
    float slope = 1.0f * (outMax - outMin) / (inMax - inMin);
    //float result = outMin + round(slope * (now - inMin));
    float result = outMin + (slope * (now - inMin));

    return result;
}

float rangeMap(seconds now, float outMin, float outMax, float inMin, float inMax, float outMinClamp, float outMaxClamp) {
    float result = rangeMap(now, outMin, outMax, inMin, inMax);

    result = std::min(outMaxClamp, result);
    result = std::max(outMinClamp, result);

    return result;
}

float Timing::RangeMappedSinceStart(
        float now,
        float outStart, float outEnd,
        float inMin, float inMax,
        float outMinClamp, float outMaxClamp,
        TimeEasingFunc functor,
        float foutMinClamp, float foutMaxClamp, bool loop) {
    if(functor) {
        float functormap;
        if(loop) {
            functormap = rangeMap(std::fmod(now, inMax), 0, 1, inMin, inMax, foutMinClamp, foutMaxClamp);
        }
        else {
            functormap = rangeMap(now, 0, 1, inMin, inMax, foutMinClamp, foutMaxClamp);
        }

        return rangeMap(functor(functormap), outStart, outEnd, 0, 1, outMinClamp, outMaxClamp);
    }

    return rangeMap(now, outStart, outEnd, inMin, inMax, outMinClamp, outMaxClamp);
}

float Timing::RangeMappedSinceStart(
        float now,
        float outStart, float outEnd,
        seconds duration,
        TimeEasingFunc functor, bool loop,
        float foutMinClamp,
        float foutMaxClamp) {
    return RangeMappedSinceStart(now, outStart, outEnd, 0, duration, -std::numeric_limits<float>::max(),
            std::numeric_limits<float>::max(), functor, foutMinClamp, foutMaxClamp, loop);
}

float Timing::RangeMappedSinceStart(
        float outStart, float outEnd,
        float inMin, float inMax,
        float outMinClamp, float outMaxClamp,
        TimeEasingFunc functor,
        float foutMinClamp, float foutMaxClamp, bool loop) {
    return RangeMappedSinceStart(
            SecondsSinceStart(), outStart, outEnd, inMin, inMax, outMinClamp, outMaxClamp, functor, foutMinClamp, foutMaxClamp, loop);
}

float Timing::RangeMappedSinceStart(float outStart,
        float outEnd,
        seconds duration,
        TimeEasingFunc functor, bool loop,
        float foutMinClamp,
        float foutMaxClamp) {
    return RangeMappedSinceStart(outStart, outEnd, 0, duration,
//            outMin, outMax,
            -std::numeric_limits<float>::max(), std::numeric_limits<float>::max(),
            functor,
            foutMinClamp, foutMaxClamp, loop);
}

bool Timing::IsBefore(seconds time, const ConditionalTimeFunc& func) {
    m_timeLastCheck = time;
    m_fncLastCheck = boost::bind(&Timing::IsBefore, boost::ref(*this), _1, _2);
    seconds now = SecondsSinceStart();
    bool result = now < time;
    if(result && func) {
        func();
    }

    return result;
}

bool Timing::IsAfter(seconds time, const ConditionalTimeFunc& func) {
    m_timeLastCheck = time;
    m_fncLastCheck = boost::bind(&Timing::IsAfter, boost::ref(*this), _1, _2);
    seconds now = SecondsSinceStart();
    bool result = now > time;
    if(result && func) {
        func();
    }

    return result;
}

bool Timing::IsAfterAndBefore(seconds after, seconds before, const ConditionalTimeFunc& func) {
    //m_timeLastCheck = time;
    //m_fncLastCheck = boost::bind(&Timing::IsAfter, boost::ref(*this), _1, _2);
    //seconds now = SecondsSinceStart();
    bool result = IsAfter(after) && IsBefore(before);
    if(result && func) {
        func();
    }

    return result;
}

bool Timing::IsAt(seconds time, const ConditionalTimeFunc& func) {
    m_timeLastCheck = time;
    m_fncLastCheck = boost::bind(&Timing::IsAt, boost::ref(*this), _1, _2);
    seconds now = SecondsSinceStart();
    bool result = now == time;
    if(result && func) {
        func();
    }

    return result;
}

bool Timing::IsAtOrAfter(seconds time, const ConditionalTimeFunc& func) {
    m_timeLastCheck = time;
    m_fncLastCheck = boost::bind(&Timing::IsAtOrAfter, boost::ref(*this), _1, _2);
    seconds now = SecondsSinceStart();
    bool result = now >= time;
    if(result && func) {
        func();
    }

    return result;
}

Timing::operator bool() const {
    bool result = m_fncLastCheck(m_timeLastCheck, NULL);
    return result;
}

Modulo::Modulo(const int ring) : m_iRing(ring)
{ }

Modulo::Modulo(const seconds ringTime) : Modulo(static_cast<int>(ringTime * FRAMESPERSECOND))
{ }

int Modulo::operator()(int in) const {
    int t = in % (m_iRing);
    return t;
}

seconds Modulo::Timed(int in) const {
    return Timing::Convert(operator()(in));
}

seconds Modulo::NormTimed(int in) const {
    return Timing::Convert(operator()(in)) / (m_iRing - 1) * FRAMESPERSECOND;
}

/*seconds operator()(seconds in) const {
   int t = in % (m_iRing);
   if (t >= m_iRing / 2) {
   return  m_iRing - ((t - m_iRing / 2) * 2);
   }
   else {
   return t * 2;
   }
   }*/

RingBounce::RingBounce(const int ring) : m_iRing(ring)
{ }

RingBounce::RingBounce(const seconds ringTime) : RingBounce(static_cast<int>(ringTime * FRAMESPERSECOND))
{ }

seconds RingBounce::RingSeconds() const {
    return Timing::Convert(m_iRing);
}

int RingBounce::operator()(int in) const {
    int t = in % (m_iRing);
    if(t >= m_iRing / 2) {
        return m_iRing - ((t - m_iRing / 2) * 2);
    }
    else {
        return t * 2;
    }
}

seconds RingBounce::Timed(int in) const {
    return Timing::Convert(operator()(in));
}

seconds RingBounce::NormTimed(int in) const {
    return Timing::Convert(operator()(in)) / m_iRing * FRAMESPERSECOND;
}
}
