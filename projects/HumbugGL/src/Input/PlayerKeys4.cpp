/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the PlayerKeys4.cpp class.
 * \folder     $(folder)
 * \file       PlayerKeys4.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"

//
#include "PlayerKeys4.h"

using namespace gob;
using namespace gui::components;

//#include <build/cmake/include/debug.h>
namespace humbug {
PlayerKeys4::PlayerKeys4(
        CRectangle frame,
        float x,
        float y,
        bool accumulate,
        bool stopOnRelease,
        float maxSpeed)
    : m_position(x, y), m_InitialPosition(x, y),
    m_rectFrame(frame), m_fSpeed(0), m_iLastTick(0), m_fCurrentSpeed(1), m_fMaxSpeed(maxSpeed), m_bStopOnRelease(
            stopOnRelease), m_bAccumulate(accumulate) {
    dbgOut(__FUNCTION__);
}

PlayerKeys4::~PlayerKeys4(void) {
    dbgOut(__FUNCTION__);
}

/** PlayerKeys4, HookEventloop:
 *  Detailed description.
 *  @param keyevent TODO
 * @return TODO
 */
void PlayerKeys4::HookEventloop(SDL_Event* keyevent) {
    m_KeyboardHandler.HandleKeyboardEvent(keyevent);

    switch(keyevent->key.keysym.sym) {
//    case SDLK_LEFT:
//    case SDLK_a:
//        if (m_bAccumulate)
//            m_direction = m_direction + GVector2D::Left() * mul;
//        else
//            m_direction = GVector2D::Left() * mul;
//        break;
//    case SDLK_RIGHT:
//    case SDLK_d:
//        if (m_bAccumulate)
//            m_direction = m_direction + GVector2D::Right() * mul;
//        else
//            m_direction = GVector2D::Right() * mul;
//        break;
//    case SDLK_UP:
//    case SDLK_w:
//        if (m_bAccumulate)
//            m_direction = m_direction + GVector2D::Down() * mul;
//        else
//            m_direction = GVector2D::Down() * mul;
//        break;
//    case SDLK_DOWN:
//    case SDLK_s:
//        if (m_bAccumulate)
//            m_direction = m_direction + GVector2D::Up() * mul;
//        else
//            m_direction = GVector2D::Up() * mul;
//        break;
    case SDLK_SPACE:
        Stop();
        break;
    case SDLK_KP_ENTER:
        Reset();
        break;
    default:
        break;
    }       // switch

    //if (!m_bAccumulate)
    float mul = 1;
    m_direction = GVector2D::Zero();

    if(m_KeyboardHandler.IsPressed(SDLK_a) || m_KeyboardHandler.IsPressed(SDLK_LEFT)) {
        m_direction = m_direction + GVector2D::Left() * mul;
        //m_direction = GVector2D::Left();
    }

    if(m_KeyboardHandler.IsPressed(SDLK_d) || m_KeyboardHandler.IsPressed(SDLK_RIGHT)) {
        m_direction = m_direction + GVector2D::Right() * mul;
        //m_direction = GVector2D::Right();
    }

    if(m_KeyboardHandler.IsPressed(SDLK_w) || m_KeyboardHandler.IsPressed(SDLK_UP)) {
        //if (m_direction == GVector2D::Down())
        {
        }
        m_direction = m_direction + GVector2D::Down() * mul;
        //m_direction = GVector2D::Down();
    }

    if(m_KeyboardHandler.IsPressed(SDLK_s) || m_KeyboardHandler.IsPressed(SDLK_DOWN)) {
        m_direction = m_direction + GVector2D::Up() * mul;
        //m_direction = GVector2D::Up();
    }

    if(m_direction == GVector2D::Zero()) {
        m_fCurrentSpeed = 1;
        return;
    }

    m_fCurrentSpeed++;
    m_direction.Normalise();

    //HookIdle();
}   // HookEventloop

/** PlayerKeys4, HookIdle:
 *  Here we update the player movement.
 *  @return TODO
 */
void PlayerKeys4::HookIdle(int ticks, float speed) {
    //These continue to accelerate the character if the user is holding
    // down a button.
    float tickDelta = ticks - m_iLastTick;
    //m_fCurrentSpeed += ( tickDelta / 50 ) * speed;

    /*if ( m_direction == GVector2D::Zero() ) {
        m_fCurrentSpeed = 0;
       }

       if (m_fCurrentSpeed > speed) {
        m_fCurrentSpeed = speed;
       }

       if (m_fMaxSpeed != 0.0f && m_fCurrentSpeed > m_fMaxSpeed)
       {
        m_fCurrentSpeed = m_fMaxSpeed;
       }*/

    //m_position = m_position + (m_direction * m_fCurrentSpeed);
    m_position = m_position + m_direction * m_fCurrentSpeed;
    int xMin = m_rectFrame.GetX();
    int yMin = m_rectFrame.GetY();
    int xMax = m_rectFrame.GetX() + m_rectFrame.GetW();
    int yMax = m_rectFrame.GetY() + m_rectFrame.GetH();
    if(m_position.x < xMin) {
        m_position.x = xMin;
    }
    else if(m_position.x > xMax) {
        m_position.x = xMax;
    }

    if(m_position.y < yMin) {
        m_position.y = yMin;
    }
    else if(m_position.y > yMax) {
        m_position.y = yMax;
    }

    /*if (charx < 0) {
        charx = 0;
       }
       else if (charx > 1024) {
        charx = 1024;
       }

       if (chary < 0) {
        chary = 0;
       }
       else if (chary > 768) {
        chary = 768;
       }*/
    m_iLastTick = ticks;
}   // HookIdle

/** PlayerKeys4, Reset:
 *  Stop movement and return to the initial position set by the constructor.
 */
void PlayerKeys4::Reset() {
    Stop();
    m_position = m_InitialPosition;
    //m_iLastTick = 0;
}

/** PlayerKeys4, Stop:
 *  Immediately stops all movement.
 */
void PlayerKeys4::Stop() {
    m_fCurrentSpeed = 1;
    m_fSpeed = 0;
    m_direction = GVector2D::Zero();
}

bool PlayerKeys4::IsPressed(SDL_Keycode keyCode)
{
    return m_KeyboardHandler.IsPressed (keyCode);
}

/** PlayerKeys4, operator <<:
     *  Detailed description.
     *  @param o TODO
     * @param r TODO
     * @return TODO
     */
std::ostream& operator<<(std::ostream& o, const PlayerKeys4& r) {
    return o << "PlayerKeys4[ X="   /*<< r.GetX() << ", Y=" << r.GetY()
                                       << ", W=" << r.GetW() << ", H=" << r.GetH()
                                       <<*/
           " ]";
}
}
