/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the EnemyWave.cpp class.
 * \file       EnemyWave.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "EnemyWave.h"
//
#include "../../GUI/DebugOverlay.h"
#include <boost/foreach.hpp>
#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>

//#include "boost/function.hpp"
//#include "boost/lambda/lambda.hpp"
//#include <GuiLib/Filesystem/FileLoader.h>
//#include <GuiLib/GUI/Components/Text.h>
//#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Control.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
//#include <GuiLib/GUI/Visual/EventHandler.h>
//#include <cstdlib>
#include <GUI/Components/Rectangle.h>
//#include <GuiLib/Filesystem/FileLoader.h>
//#include <GuiLib/GUI/Components/CanvasRendererImpl.h>
//#include <GuiLib/GUI/Components/CoordSystem.h>
//#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/GUI/Components/Image.h>
//#include <GuiLib/GUI/Components/Image.h>
//#include <GuiLib/GUI/Components/SeamlessImage.h>
//#include <GuiLib/GUI/Components/Shapes/Line.h>
//#include <GuiLib/GUI/Components/Text.h>
//#include <GuiLib/GUI/Components/TextScroller.h>
//#include <GuiLib/GUI/Controls/Button.h>
//#include <GuiLib/GUI/Controls/Label.h>
//#include <GuiLib/GUI/Data/ColorData.h>
//#include <GuiLib/GUI/Sprite/Sprite.h>
//#include <GuiLib/GUI/Sprite/SpriteManager.h>
//#include <GuiLib/GUI/Visual/EventHandler.h>
//
//#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {
namespace levels {
namespace scroller_levela {




namespace msm = boost::msm;
namespace mpl = boost::mpl;

// events
struct play {};
struct end_pause {};
struct stop {};
struct pause {};
struct open_close {};
struct NextSong {};
struct PreviousSong {};

// A "complicated" event type that carries some data.
struct cd_detected
{
    cd_detected(std::string name)
        : name(name)
    {}

    std::string name;
};

// front-end: define the FSM structure 
struct player_ : public msm::front::state_machine_def<player_>
{
    template <class Event, class FSM>
    void on_entry(Event const&, FSM&) { std::cout << "entering: Player" << std::endl; }
    template <class Event, class FSM>
    void on_exit(Event const&, FSM&) { std::cout << "leaving: Player" << std::endl; }

    // The list of FSM states
    struct Empty : public msm::front::state<>
    {
        // every (optional) entry/exit methods get the event passed.
        template <class Event, class FSM>
        void on_entry(Event const&, FSM&) { std::cout << "entering: Empty" << std::endl; }
        template <class Event, class FSM>
        void on_exit(Event const&, FSM&) { std::cout << "leaving: Empty" << std::endl; }
    };
    struct Open : public msm::front::state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const&, FSM&) { std::cout << "entering: Open" << std::endl; }
        template <class Event, class FSM>
        void on_exit(Event const&, FSM&) { std::cout << "leaving: Open" << std::endl; }
    };

    struct Stopped : public msm::front::state<>
    {
        // when stopped, the CD is loaded
        template <class Event, class FSM>
        void on_entry(Event const&, FSM&) { std::cout << "entering: Stopped" << std::endl; }
        template <class Event, class FSM>
        void on_exit(Event const&, FSM&) { std::cout << "leaving: Stopped" << std::endl; }
    };

    // the player state machine contains a state which is himself a state machine
    // as you see, no need to declare it anywhere so Playing can be developed separately
    // by another team in another module. For simplicity I just declare it inside player
    struct Playing_ : public msm::front::state_machine_def<Playing_>
    {
        // when playing, the CD is loaded and we are in either pause or playing (duh)
        template <class Event, class FSM>
        void on_entry(Event const&, FSM&) { std::cout << "entering: Playing" << std::endl; }
        template <class Event, class FSM>
        void on_exit(Event const&, FSM&) { std::cout << "leaving: Playing" << std::endl; }

        // The list of FSM states
        struct Song1 : public msm::front::state<>
        {
            template <class Event, class FSM>
            void on_entry(Event const&, FSM&) { std::cout << "starting: First song" << std::endl; }
            template <class Event, class FSM>
            void on_exit(Event const&, FSM&) { std::cout << "finishing: First Song" << std::endl; }

        };
        struct Song2 : public msm::front::state<>
        {
            template <class Event, class FSM>
            void on_entry(Event const&, FSM&) { std::cout << "starting: Second song" << std::endl; }
            template <class Event, class FSM>
            void on_exit(Event const&, FSM&) { std::cout << "finishing: Second Song" << std::endl; }
        };
        struct Song3 : public msm::front::state<>
        {
            template <class Event, class FSM>
            void on_entry(Event const&, FSM&) { std::cout << "starting: Third song" << std::endl; }
            template <class Event, class FSM>
            void on_exit(Event const&, FSM&) { std::cout << "finishing: Third Song" << std::endl; }
        };
        // the initial state. Must be defined
        typedef Song1 initial_state;
        // transition actions
        void start_next_song(NextSong const&)       { std::cout << "Playing::start_next_song\n"; }
        void start_prev_song(PreviousSong const&)       { std::cout << "Playing::start_prev_song\n"; }
        // guard conditions

        typedef Playing_ pl; // makes transition table cleaner
        // Transition table for Playing
        struct transition_table : mpl::vector4<
            //      Start     Event         Next      Action               Guard
            //    +---------+-------------+---------+---------------------+----------------------+
            a_row < Song1, NextSong, Song2, &pl::start_next_song                       >,
            a_row < Song2, PreviousSong, Song1, &pl::start_prev_song                       >,
            a_row < Song2, NextSong, Song3, &pl::start_next_song                       >,
            a_row < Song3, PreviousSong, Song2, &pl::start_prev_song                       >
            //    +---------+-------------+---------+---------------------+----------------------+
        > {};
        // Replaces the default no-transition response.
        template <class FSM, class Event>
        void no_transition(Event const& e, FSM&, int state)
        {
            std::cout << "no transition from state " << state
                << " on event " << typeid(e).name() << std::endl;
        }
    };
    // back-end
    typedef msm::back::state_machine<Playing_> Playing;


    // state not defining any entry or exit
    struct Paused : public msm::front::state<>
    {
    };

    // the initial state of the player SM. Must be defined
    typedef Empty initial_state;

    // transition actions
    void start_playback(play const&)       { std::cout << "player::start_playback\n"; }
    void open_drawer(open_close const&)    { std::cout << "player::open_drawer\n"; }
    void close_drawer(open_close const&)   { std::cout << "player::close_drawer\n"; }
    void store_cd_info(cd_detected const& cd) { std::cout << "player::store_cd_info\n"; }
    void stop_playback(stop const&)        { std::cout << "player::stop_playback\n"; }
    void pause_playback(pause const&)      { std::cout << "player::pause_playback\n"; }
    void resume_playback(end_pause const&)      { std::cout << "player::resume_playback\n"; }
    void stop_and_open(open_close const&)  { std::cout << "player::stop_and_open\n"; }
    void stopped_again(stop const&){ std::cout << "player::stopped_again\n"; }
    // guard conditions

    typedef player_ p; // makes transition table cleaner

    // Transition table for player
    struct transition_table : mpl::vector<
        //      Start     Event         Next      Action               Guard
        //    +---------+-------------+---------+---------------------+----------------------+
                a_row <     Stopped,     play,          Playing,        &p::start_playback>,
                a_row <     Stopped,     open_close,    Open,           &p::open_drawer>,
                a_row <     Stopped,     stop,          Stopped,        &p::stopped_again>,
        //    +---------+-------------+---------+---------------------+----------------------+
                a_row <     Open,        open_close,    Empty,          &p::close_drawer>,
        //    +---------+-------------+---------+---------------------+----------------------+
                a_row <     Empty,       open_close,    Open,           &p::open_drawer>,
                a_row <     Empty,       cd_detected,   Stopped,        &p::store_cd_info>,
        //    +---------+-------------+---------+---------------------+----------------------+
                a_row <     Playing,     stop,          Stopped,        &p::stop_playback>,
                a_row <     Playing,     pause,         Paused,         &p::pause_playback>,
                a_row <     Playing,     open_close,    Open,           &p::stop_and_open>,
        //    +---------+-------------+---------+---------------------+----------------------+
                a_row <     Paused,      end_pause,     Playing,        &p::resume_playback>,
                a_row <     Paused,      stop,          Stopped,        &p::stop_playback>,
                a_row <     Paused,      open_close,    Open,           &p::stop_and_open>
        //    +---------+-------------+---------+---------------------+----------------------+
    > {};

    // Replaces the default no-transition response.
    template <class FSM, class Event>
    void no_transition(Event const& e, FSM&, int state)
    {
        std::cout << "no transition from state " << state
            << " on event " << typeid(e).name() << std::endl;
    }

};
// Pick a back-end
typedef msm::back::state_machine<player_> player;

//
// Testing utilities.
//
static char const* const state_names[] = { "Stopped", "Open", "Empty", "Playing", "Paused" };

void pstate(player const& p)
{
    std::cout << " -> " << state_names[p.current_state()[0]] << std::endl;
}

void test()
{
    player p;
    // needed to start the highest-level SM. This will call on_entry and mark the start of the SM
    p.start();
    // go to Open, call on_exit on Empty, then action, then on_entry on Open
    p.process_event(open_close()); pstate(p);
    p.process_event(open_close()); pstate(p);
    p.process_event(cd_detected("louie, louie"));
    p.process_event(play());

    // at this point, Play is active 
    // make transition happen inside it. Player has no idea about this event but it's ok.
    p.process_event(NextSong()); pstate(p); //2nd song active
    p.process_event(NextSong()); pstate(p);//3rd song active
    p.process_event(PreviousSong()); pstate(p);//2nd song active

    p.process_event(pause()); pstate(p);
    // go back to Playing
    // as you see, it starts back from the original state
    p.process_event(end_pause());  pstate(p);
    p.process_event(pause()); pstate(p);
    p.process_event(stop());  pstate(p);
    // event leading to the same state
    p.process_event(stop());  pstate(p);
    // stop the fsm (call on_exit's, including the submachines)
    p.process_event(play());
    std::cout << "stop fsm" << std::endl;
    p.stop();
    std::cout << "restart fsm" << std::endl;
    p.start();
}

int main()
{
    test();
    return 0;
}





struct EnemyWave::EnemyWaveImpl {
    int x;

};

EnemyWave::EnemyWave(FileLoader& loader, CCanvas* canvas, CSpriteManager* sprMgr,
        DebugOverlay* dbgOverlay) : pimpl_(new EnemyWaveImpl),  m_pSprMgr(sprMgr), m_pCanvas(canvas), m_Loader(loader), m_pOverlay(dbgOverlay) {
    m_pSprEnemy1Ship =
        new CSprite(loader, "Sprites/Ship/Enemy01a.png", canvas, CPoint(64, 64));
    m_pSprEnemy1Ship->SprImage()->DstRect() = m_pSprEnemy1Ship->SprImage()->DstRect() / 2;
    m_pSprEnemy1Ship->SetHitBox(m_pSprEnemy1Ship->SprImage()->DstRect());
    int mainCanvasMiddleX = canvas->GetWidth() / 2;
    int mainSprEyeMiddleX = m_pSprEnemy1Ship->SprImage()->DstRect().GetW() / 2;
    sprPaintDimension = m_pSprEnemy1Ship->PaintDimension();
    mainDimension = canvas->GetDimension();
    //CRectangle rect = CRectangle() mainDimension.Pad(sprPaintDimension);
    CRectangle rect = CRectangle(mainDimension.GetX(), mainDimension.GetY(),
            mainDimension.GetW() - sprPaintDimension.GetW() / 2, mainDimension.GetH() - sprPaintDimension.GetH() / 2);
    int delta_y = canvas->GetHeight() - m_pSprEnemy1Ship->SprImage()->DstRect().GetH() - 128;
    //        updfuncShip = boost::make_shared<EnemyShip1Mover>(canvas, 120);
    //        updfuncShip->SetDebugOverlay(dbgOverlay);
    //        m_iSprEnemy1ShipId = sprMgr->AddSprite(m_pSprEnemy1Ship, "Enemy",
    // boost::ref(*updfuncShip.get()), this);
    m_iSprEnemy1ShipId = sprMgr->AddSprite(m_pSprEnemy1Ship, "Enemy", NULL, this);
    m_pSprEnemy1Ship->SetPosition(CPoint(200, 200));
    //        //CPoint pos = m_pSprEnemy1Ship->PaintLocation().Position(CRectangle::CompassRose::N)
    // -
    // m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::S).Up(-50);
    //        //CPoint pos =
    // m_pSprEnemy1Ship->PaintLocation().Position(CRectangle::CompassRose::N).Up(-64);
    //        CPoint pos(128, 128);
    //        //m_pSprMgr->AddSpriteDraw(m_iSprLaserId, pos, boost::bind(&PlayerShip::LaserUpdfunc2,
    // boost::ref(*this), _1, _2, _3), { "Enemy", "Test" });
    //        m_pSprMgr->AddSpriteDraw(m_iSprEnemy1ShipId, pos, boost::ref(*updfuncShip.get()), {
    // "Laser", "Ship" });
    m_pSprEnemy1Ship->SetVisibility(false);

    //m_iSprLaserId = CreateLaserSprite();
    m_pSprLaser =
        new CSprite(loader, "Sprites/Ship/Laser/Bullet01.png", canvas, CPoint(32, 32));
    CRectangle hitbox = CRectangle(m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::SW).Up(
                    -50), m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::NE).Up(50));
    m_pSprLaser->SetHitBox(hitbox.Pad(20, 0));
    //        CPoint posLas = m_pSprEnemy1Ship->PaintLocation().Position(CRectangle::CompassRose::N)
    // -
    // m_pSprLaser->PaintDimension().Position(CRectangle::CompassRose::S).Up(-50);
    //        m_pSprLaser->SetPosition(posLas);
    m_pSprLaser->SetVisibility(false);
    m_iSprLaserId = m_pSprMgr->AddSprite(m_pSprLaser, "EnemyBullet");

    const int rows = 4;
    const int columns = 4;
    //        const int rows = 2;
    //        const int columns = 2;
    //const int startPosX = 32;

    int screenXMiddle = canvas->GetDimension().GetW() / 2;
    int spriteShipWidth = sprPaintDimension.GetW();
    int spriteShipHeight = sprPaintDimension.GetH();
    int spriteShipHeightDouble = spriteShipHeight * 2;
    int spriteShipWidthHalf = spriteShipWidth / 2;
    int spriteShipWidthDouble = spriteShipWidth * 2;
    int spritesXMiddle = (spriteShipWidth * columns) / 2;

    int startPosX = screenXMiddle - spritesXMiddle;
    const int startPosY = 32;

    //m_pEnemyShip = boost::make_shared<EnemyShip>(m_pSprEnemy1Ship, m_iSprEnemy1ShipId,
    // m_pSprLaser, m_iSprLaserId, canvas, sprMgr, dbgOverlay);
    for(size_t row = 0; row < rows; row++)
    {
        int rowNotEven = row % 1;
        CPoint pos = CPoint(startPosX + rowNotEven * spriteShipWidthHalf, startPosY + row * spriteShipHeightDouble);

        for(size_t column = 0; column < columns; column++)
        {
            m_pEnemyShips.push_back(new EnemyShip(sprMgr, pos, m_iSprEnemy1ShipId, m_iSprLaserId, canvas,
                            dbgOverlay));
            pos.Move(spriteShipWidth, 0);
        }
    }

    //main();
}

void EnemyWave::HitBy(const CSprite& hitter,
        const CRectangle& paintHitbox,
        int id,
        const std::string& tag,
        CSpriteModifierData& mdata) {
}

void EnemyWave::HookIdle(int ticks, float speed) {
    CPoint movement = CPoint(1, 1);
    if(ticks % 300 > 150) {
        movement = CPoint(-1, -1);
    }

    //return;
    //m_pKeyHandler->HookIdle(ticks, speed);
//        BOOST_FOREACH(boost::ptr_vector<EnemyShip>::reference ship, m_pEnemyShips)
//        {
//            ship.SetOffset(ship.Offset() + movement);
//        }

    boost::ptr_vector<EnemyShip>::iterator sprIt = m_pEnemyShips.begin();
    while(sprIt != m_pEnemyShips.end()) {
        boost::ptr_vector<EnemyShip>::reference ship = (*sprIt);
        unsigned int id = ship.Id();
        if(ship.IsDisposed()) {
            // if markedForDeletion, remove it
            sprIt = m_pEnemyShips.erase(sprIt);
        }
        else {
            ship.SetOffset(ship.Offset() + movement);
            ++sprIt;
        }
    }
} // EnemyWave::HookIdle
}
}
}
