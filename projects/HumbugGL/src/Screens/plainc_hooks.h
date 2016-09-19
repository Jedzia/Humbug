/*
 * plainc_hooks.cpp
 *
 *  Created on: Apr 25, 2012
 *      Author: jschober
 */

#ifndef __PLAINC_HOOKS_H__
#define __PLAINC_HOOKS_H__

#include <lua.hpp>

#include <iostream>

namespace plainc {

    class IO
    {
    public:
        void WriteLn( const char* c )
        {
            std::cout << c << std::endl;
        }
    };

    static int createIO( lua_State* lua )
    {
        void* io = (void*)new IO();
        lua_pushlightuserdata( lua, io );
        return 1;
    }

    static int deleteIO(  lua_State* lua )
    {
        int argc = lua_gettop( lua );
        if ( argc > 0  ) {
            IO* io = (IO*)lua_topointer( lua, 1 );
            delete io;
        }
        return 1;
    }

    static int WriteLnIO( lua_State* lua )
    {
        int argc = lua_gettop( lua );
        if ( argc > 1  ) {
            IO* io = (IO*)lua_topointer( lua, 1 );
            std::string p;
            for ( int i = 2; i <= argc; i++ ) {
                p += lua_tostring( lua, i );
            }
            io->WriteLn( p.c_str( ) );
        }
        return 1;
    }

    static int writeLn( lua_State* lua )
    {
        int argc = lua_gettop( lua );
        for ( int i = 1; i <= argc; i++ ) {
            const char *c = lua_tostring( lua, i );
            std::cout << c;
        }
        if ( argc > 0 ) {
            std::cout << std::endl;
        }
        lua_pushnumber( lua, argc );
        return 1;
    }

    const char *luascript = "io=ioCreate()\n" \
                            "ioWrite( io, \"Hello World from String!\")\n" \
                            "ioDelete(io)";

    void Register( lua_State* lua )
    {
        lua_register( lua, "writeLn", writeLn );

        lua_register( lua, "ioCreate", createIO );
        lua_register( lua, "ioDelete", deleteIO );
        lua_register( lua, "ioWrite", WriteLnIO );

    }

} // plain c

#endif /* __PLAINC_HOOKS_H__ */
