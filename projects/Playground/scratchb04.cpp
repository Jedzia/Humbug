// Copyright 2010 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
// back-end
#include <boost/msm/back/state_machine.hpp>
//front-end
#include <boost/msm/front/state_machine_def.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

namespace  // Concrete FSM implementation
{
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
            a_row < Stopped, open_close, Open, &p::open_drawer                            >,
            a_row < Stopped, stop, Stopped, &p::stopped_again                          >,
            //    +---------+-------------+---------+---------------------+----------------------+
            a_row < Open, open_close, Empty, &p::close_drawer                         >,
            //    +---------+-------------+---------+---------------------+----------------------+
            a_row < Empty, open_close, Open, &p::open_drawer                          >,
            a_row < Empty, cd_detected, Stopped, &p::store_cd_info                        >,
            //    +---------+-------------+---------+---------------------+----------------------+
            //    +---------+-------------+---------+---------------------+----------------------+
            a_row < Paused, stop, Stopped, &p::stop_playback                        >,
            a_row < Paused, open_close, Open, &p::stop_and_open                        >
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

        p.stop();
        std::cout << "restart fsm" << std::endl;
        p.start();
    }
}

int main()
{
    test();
    return 0;
}
