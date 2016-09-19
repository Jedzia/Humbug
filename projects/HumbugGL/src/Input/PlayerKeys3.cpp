/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the PlayerKeys3.cpp class.
 * \folder     $(folder)
 * \file       PlayerKeys3.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"

//
#include "PlayerKeys3.h"

using namespace gob;

//#include <build/cmake/include/debug.h>
namespace humbug {

PlayerKeys3::PlayerKeys3(
        float x,
        float y,
        bool accumulate,
        bool stopOnRelease,
        float maxSpeed)
    : m_position(x,
            y),
    m_InitialPosition(x, y), m_fSpeed(0), m_iLastTick(0), m_fCurrentSpeed(0), m_fMaxSpeed(maxSpeed), m_bStopOnRelease(
            stopOnRelease), m_bAccumulate(accumulate){
    dbgOut(__FUNCTION__);
}

PlayerKeys3::~PlayerKeys3(void){
    dbgOut(__FUNCTION__);
}

/** PlayerKeys3, HookEventloop:
 *  Detailed description.
 *  @param keyevent TODO
 * @return TODO
 */
void PlayerKeys3::HookEventloop( SDL_Event* keyevent ){
    m_KeyboardHandler.HandleKeyboardEvent(keyevent);

    switch (keyevent->key.keysym.sym) {
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
    //m_direction = GVector2D::Zero();

    if ( m_KeyboardHandler.IsPressed(SDLK_a) || m_KeyboardHandler.IsPressed(SDLK_LEFT) ) {
        m_direction = m_direction + GVector2D::Left() * mul;
        //m_direction = GVector2D::Left();
    }

    if ( m_KeyboardHandler.IsPressed(SDLK_d) || m_KeyboardHandler.IsPressed(SDLK_RIGHT) ) {
        m_direction = m_direction + GVector2D::Right() * mul;
        //m_direction = GVector2D::Right();
    }

    if (m_KeyboardHandler.IsPressed(SDLK_w) || m_KeyboardHandler.IsPressed(SDLK_UP)) {
        m_direction = m_direction + GVector2D::Down() * mul;
        //m_direction = GVector2D::Down();
    }

    if (m_KeyboardHandler.IsPressed(SDLK_s) || m_KeyboardHandler.IsPressed(SDLK_DOWN)) {
        m_direction = m_direction + GVector2D::Up() * mul;
        //m_direction = GVector2D::Up();
    }

    if ( m_direction == GVector2D::Zero() ) {
        return;
    }

    m_direction.Normalise();

    //HookIdle();
}   // HookEventloop

/** PlayerKeys3, HookIdle:
 *  Here we update the player movement.
 *  @return TODO
 */
void PlayerKeys3::HookIdle(int ticks, float speed){
    //These continue to accelerate the character if the user is holding
    // down a button.
    float tickDelta = ticks - m_iLastTick;
    m_fCurrentSpeed += ( tickDelta / 50 ) * speed;

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
    m_position = m_position + m_direction;

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

/** PlayerKeys3, Reset:
 *  Stop movement and return to the initial position set by the constructor.
 */
void PlayerKeys3::Reset(){
    Stop();
    m_position = m_InitialPosition;
    //m_iLastTick = 0;
}

/** PlayerKeys3, Stop:
 *  Immediately stops all movement.
 */
void PlayerKeys3::Stop(){
    m_fCurrentSpeed = 0;
    m_fSpeed = 0;
    m_direction = GVector2D::Zero();
}

/** PlayerKeys3, operator <<:
 *  Detailed description.
 *  @param o TODO
 * @param r TODO
 * @return TODO
 */
std::ostream& operator<<(std::ostream& o, const PlayerKeys3& r) {
    return o << "PlayerKeys3[ X="   /*<< r.GetX() << ", Y=" << r.GetY()
                                       << ", W=" << r.GetW() << ", H=" << r.GetH()
                                       <<*/
           " ]";
}
}
