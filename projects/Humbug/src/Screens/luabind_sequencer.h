/*
 * luabind_test.h
 *
 *  Created on: Apr 25, 2012
 *      Author: jschober
 */

#ifndef __LUABIND_SEQUENCER_H__
#define __LUABIND_SEQUENCER_H__

#ifdef _HAS_LUA_BIND_

#include "luabind_macros.h"

#include <string>

#include <message_queue.h>
#include <listener.h>
#include <sequencer.h>
#include <sequence_event_effect.h>
#include <sequence_timed_effect.h>

#include <boost/shared_ptr.hpp>

#include <stdio.h>
#include <stdarg.h>

// global sequencer
extern Sequencer sequencer;

namespace luasequencer
{
    void luaCall( lua_State* lua, const char* fn, const char *templ, ... )
    {
        va_list ap;
        va_start(ap, templ);
        char *buffer = new char[8092];
        vsprintf( buffer, templ, ap );
        va_end(ap);
        // split string into param array and push each param to lua stack ?? - or send one string ???

        lua_getfield( lua, LUA_GLOBALSINDEX, fn );
        lua_pushstring( lua, "Param1" );    // first param
        lua_pushinteger(lua, 1 );           // secand param
        lua_call(lua, 2, 0 );               // call 2 params, no return
        delete [] buffer;

    }

    void CreateMessageExports( lua_State* lua, luabind::module_& module )
    {
        LUA_DECLARE_CLASS_SCOPED( Message );
            LUA_DECLARE_CTOR( Message );
            LUA_DECLARE_METHOD( Message, asString );
        LUA_DEFINE_CLASS( module, Message );

        LUA_DECLARE_DERIVED_CLASS_SCOPED( StringMessage, Message );
            LUA_DECLARE_CTOR_1( StringMessage, const char* );
        LUA_DEFINE_CLASS( module, StringMessage );
    }

    void CreateMessageQueueExports( lua_State* lua, luabind::module_& module )
    {
        LUA_DECLARE_CLASS_SCOPED( MessageQueue );
            LUA_DECLARE_CTOR( MessageQueue );
            LUA_DECLARE_METHOD( MessageQueue, Send );
            LUA_DECLARE_METHOD( MessageQueue, IsEmpty );
            LUA_DECLARE_METHOD( MessageQueue, CancelWait );
            // explicit macro required of overloaded methods - or non void methods
            LUA_DECLARE_METHOD_PROTO( MessageQueue, Poll, (boost::shared_ptr<Message>(MessageQueue::*)(std::vector< typename  boost::shared_ptr<Message> >, bool))&MessageQueue::Poll );
            LUA_DECLARE_METHOD_PROTO( MessageQueue, Poll, (boost::shared_ptr<Message>(MessageQueue::*)())&MessageQueue::Poll );
            LUA_DECLARE_METHOD_PROTO( MessageQueue, Wait, (boost::shared_ptr<Message>(MessageQueue::*)(std::vector< typename  boost::shared_ptr<Message> >, bool))&MessageQueue::Wait );
            LUA_DECLARE_METHOD_PROTO( MessageQueue, Wait, (boost::shared_ptr<Message>(MessageQueue::*)())&MessageQueue::Wait );
            LUA_DECLARE_METHOD( MessageQueue, CancelWait );
            LUA_DECLARE_METHOD( MessageQueue, CancelWait );
        LUA_DEFINE_CLASS( module, MessageQueue );
    }

    void CreateEventListenerExports( lua_State* lua, luabind::module_& module )
    {
        LUA_DECLARE_CLASS_SCOPED( Listener );
            LUA_DECLARE_CTOR( Listener );
        LUA_DEFINE_CLASS( module, Listener );

        LUA_DECLARE_DERIVED_CLASS_SCOPED( EventListener, Listener );
            LUA_DECLARE_CTOR( EventListener );
            LUA_DECLARE_CTOR_1( EventListener, const MessagePtr& );
            LUA_DECLARE_METHOD( EventListener, WaitEvent );
            LUA_DECLARE_METHOD( EventListener, PollEvent );
            LUA_DECLARE_METHOD( EventListener, SetEventToListen );
            LUA_DECLARE_METHOD( EventListener, GetEventToListen );
        LUA_DEFINE_CLASS( module, EventListener );
    }

    void CreateSequencerExports( lua_State* lua, luabind::module_& module )
    {
        LUA_DECLARE_CLASS_SCOPED( Sequencer );
            // link class enums (used in StateMessage)
            LUA_BEGIN_ENUM( Sequencer, SeqStates )
                LUA_ENUM_VALUE( IDLE,       Sequencer::IDLE     ) ,
                LUA_ENUM_VALUE( START,      Sequencer::START    ),
                LUA_ENUM_VALUE( RUNNING,    Sequencer::RUNNING  ),
                LUA_ENUM_VALUE( TERMINATE,  Sequencer::TERMINATE),
                LUA_ENUM_VALUE( STOPPED,    Sequencer::STOPPED  ),
                LUA_ENUM_VALUE( SUSPEND,    Sequencer::SUSPEND  ),
                LUA_ENUM_VALUE( RESUME,     Sequencer::RESUME   )
            LUA_END_ENUM();

            // declare an inner scope and put the inner class into it, -> class Sequencer::StateMessage : public Message {}
            LUA_DECLARE_INNER_DERIVED_CLASS_SCOPED( Sequencer, StateMessage, Message );
                LUA_DECLARE_CTOR_1( StateMessage, Sequencer::SeqStates );
            LUA_END_DECLARE();
            // now we can attach this "inner class" to the current scope (Sequencer)
            LUA_BEGIN_SCOPE( Sequencer )
                LUA_CLASS(StateMessage)
            LUA_END_SCOPE();

            // now methods, etc.
            LUA_DECLARE_CTOR( Sequencer );
            LUA_DECLARE_CTOR_1( Sequencer, const MessageQueuePtr& );

            LUA_DECLARE_METHOD( Sequencer, RegisterListener );
            LUA_DECLARE_METHOD( Sequencer, UnregisterListener );
            LUA_DECLARE_METHOD( Sequencer, SetMessageQueue );
            LUA_DECLARE_METHOD( Sequencer, GetMessageQueue );
            LUA_DECLARE_METHOD( Sequencer, Add );
            LUA_DECLARE_METHOD( Sequencer, Clear );
            LUA_DECLARE_METHOD( Sequencer, Start );
            LUA_DECLARE_METHOD( Sequencer, Stop );

        LUA_DEFINE_CLASS( module, Sequencer );
    }

    void CreateEffectExports( lua_State* lua, luabind::module_& module )
    {
        LUA_DECLARE_CLASS_SCOPED( SeqEffect );
            LUA_DECLARE_CTOR( SeqEffect );
            LUA_DECLARE_CTOR_1( SeqEffect, const MessageQueuePtr& );
            LUA_DECLARE_METHOD( SeqEffect, Init );
            LUA_DECLARE_METHOD( SeqEffect, SetMessageQueue );
            LUA_DECLARE_METHOD( SeqEffect, GetMessageQueue );
            LUA_DECLARE_METHOD( SeqEffect, Start );
            LUA_DECLARE_METHOD( SeqEffect, Stop );
        LUA_DEFINE_CLASS( module, SeqEffect );

        // Derived class. Base class must be exported, too. Can be smart ptr export (SCOPED)
        LUA_DECLARE_DERIVED_CLASS_SCOPED( SeqTimedEffect, SeqEffect );
            // default parameters require explicit entry
            LUA_DECLARE_CTOR_2( SeqTimedEffect, double, const MessagePtr& );
            LUA_DECLARE_CTOR_3( SeqTimedEffect, double, const MessagePtr&, int );
            LUA_DECLARE_CTOR_4( SeqTimedEffect, double, const MessagePtr&, int, const MessageQueuePtr& );
        LUA_DEFINE_CLASS( module, SeqTimedEffect );

        LUA_DECLARE_DERIVED_CLASS_SCOPED( SeqEventEffect, SeqEffect );
            // default parameters require explicit entry
            LUA_DECLARE_CTOR_2( SeqEventEffect, const MessagePtr&, const MessagePtr& );
            LUA_DECLARE_CTOR_3( SeqEventEffect, const MessagePtr&, const MessagePtr&, const MessageQueuePtr& );
        LUA_DEFINE_CLASS( module, SeqEventEffect );
    }

    void Register( lua_State* lua )
    {
        luabind::open(lua);

        // lua_state & namespace
        luabind::module_ module = LUA_CREATE_MODULE_NS( lua, pei );

        // now, this binds a listener to the sequencer and makes lua wait till the sequence ends
        CreateEventListenerExports( lua, module );
        // All Message Queue related exports
        CreateMessageExports( lua, module );
        // All built in effects
        CreateEffectExports( lua, module );
        // The Sequencer itself
        CreateSequencerExports( lua, module );
    }

}

#endif

#endif /* __LUABIND_SEQUENCER_H__ */
