/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScriptHost.cpp class.
 * \folder     $(folder)
 * \file       ScriptHost.cpp
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
//
#include "ScriptHost.h"
#include "plainc_hooks.h"
#include <lua.hpp>
#include <luabind/luabind.hpp>
//#include "HumbugLib/LogManager.h"

//#include <build/cmake/include/debug.h>

namespace shost {

	class IO
	{
	public:
		void WriteLn( const char* c )
		{
			std::cout << c << std::endl;
		}
	};

	class IOReg
	{
	public:
		static int createIO( lua_State* lua )
		{
			void* io = (void*)new IO();
			lua_pushlightuserdata( lua, io );
			return 1;
		};

		static int deleteIO(  lua_State* lua )
		{
			int argc = lua_gettop( lua );
			if ( argc > 0  ) {
				IO* io = (IO*)lua_topointer( lua, 1 );
				delete io;
			}
			return 1;
		};

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
		};

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
		};

		static void Register( lua_State* lua )
		{
			//lua_register( lua, "writeLn", writeLn );

			//lua_register( lua, "ioCreate", createIO );
			//lua_register( lua, "ioDelete", deleteIO );
			//lua_register( lua, "ioWrite", WriteLnIO );
			lua_register( lua, "write", WriteLnIO );

		};

	};


  ScriptHost::ScriptHost(){
      dbgOut(__FUNCTION__ );
      LOGSTREAM << "ScriptHost bIS THERE !!!!!!!!!!!!";
  }

  ScriptHost::~ScriptHost(void){
      dbgOut(__FUNCTION__);
  }

  lua_State* L;

  /** $(fclass), greet:
   *  Detailed description.
   *
   */
  void greet(){
      std::cout << "hello world!\n";
  }

  class testclass {
public:

      testclass(const std::string& s) : m_string(s) {}

      /** $(fclass), print_string:
       *  Detailed description.
       *
       */
      void print_string() { std::cout << m_string << "\n"; }

private:

      std::string m_string;
  };

  /*
  ** these libs are loaded by lua.c and are readily available to any Lua
  ** program
  */
  static const luaL_Reg loadedlibs[] = {
      {"_G", luaopen_base},
      {LUA_LOADLIBNAME, luaopen_package},
      {LUA_COLIBNAME, luaopen_coroutine},
      {LUA_TABLIBNAME, luaopen_table},
      {LUA_IOLIBNAME, luaopen_io},
      {LUA_OSLIBNAME, luaopen_os},
      {LUA_STRLIBNAME, luaopen_string},
      {LUA_BITLIBNAME, luaopen_bit32},
      {LUA_MATHLIBNAME, luaopen_math},
      {LUA_DBLIBNAME, luaopen_debug},
      {NULL, NULL}
  };

  /*
  ** these libs are preloaded and must be required before used
  */
  static const luaL_Reg preloadedlibs[] = {
      {NULL, NULL}
  };

  /** $(fclass), openLuaLib:
   *  Detailed description.
   *  @param L TODO
   * @param lib TODO
   */
  void openLuaLib (lua_State* L, const luaL_Reg* lib) {
      /* call open functions from 'loadedlibs' and set results to global table */
      luaL_requiref(L, lib->name, lib->func, 1);
      lua_pop(L, 1);              /* remove lib */
  }

  /** $(fclass), openLuaLib:
   *  Detailed description.
   *  @param L TODO
   * @param name TODO
   */
  void openLuaLib (lua_State* L, const char* name) {
      const luaL_Reg* lib;

      /* call open functions from 'loadedlibs' and set results to global table */
      for (lib = loadedlibs; lib->func; lib++) {
          if (strcmp(name, lib->name) == 0) {
              luaL_requiref(L, lib->name, lib->func, 1);
              lua_pop(L, 1);                      /* remove lib */
          }
      }
  }

  /** $(fclass), openLuaLibs:
   *  Detailed description.
   *  @param L TODO
   */
  void openLuaLibs (lua_State* L) {
      const luaL_Reg* lib;

      /* call open functions from 'loadedlibs' and set results to global table */
      for (lib = loadedlibs; lib->func; lib++) {
          luaL_requiref(L, lib->name, lib->func, 1);
          lua_pop(L, 1);          /* remove lib */
      }
  }

  char *copyGlobalString(lua_State *L, const char *name) {
	  char *s = NULL;
	  lua_getglobal(L,name);
	  if (!lua_isnil(L,-1))
		  s = strdup(lua_tostring(L,-1));
	  lua_pop(L,1);
	  return s;
  }
  /** ScriptHost, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  void ScriptHost::RunScript(const std::string& script) const {
      using namespace luabind;

      int s(0);
      L = luaL_newstate();
      //luaL_openlibs(L);
      //openLuaLibs (L);

      //luaL_Reg iolib; iolib.name = LUA_IOLIBNAME; iolib.func = luaopen_io;
      //openLuaLib (L, &iolib);

      //openLuaLib (L, LUA_LOADLIBNAME);
      openLuaLib (L, "_G");
      openLuaLib (L, LUA_IOLIBNAME);
	  
	  //IOReg::Register(L);
	  //IOReg::createIO(L);
	  /* variable with an unique address */
	  static const char* Key = "myVar";
	  static const char* value = "FromScriptHost";
	  

// 	  /* store a number */
// 	  lua_pushlightuserdata(L, (void *)&Key);  /* push address */
// 	  //lua_pushnumber(L, 666);  /* push value */
// 	  lua_pushstring(L, value);  /* push string */
// 	  /* registry[&Key] = myNumber */
// 	  lua_settable(L, LUA_REGISTRYINDEX);
	  
	  //luabind::push()
	  //lua_pushstring(L, Key);
	  //lua_settable(L, -3);
	  //lua_settable(L, LUA_REGISTRYINDEX);

	  // push string variable <myVar> with "FromScriptHost" as content to Lua. 
	  lua_pushstring(L, "FromScriptHost");
	  lua_setglobal(L, Key);


      //plainc::Register( L );
      const char* luascript = "io=ioCreate()\n" \
                              "ioWrite( io, \"Hello World from String!\")\n" \
                              "ioDelete(io)";

      // A file
      //std::string& luaFileContent = m_Loader.FL_LOADASSTRING("L/hello.L");
      s = luaL_loadstring( L, script.c_str() );

      //s = luaL_loadstring( L, luascript );
      if ( s == 0 ) {
        int ret = lua_pcall( L, 0, LUA_MULTRET, 0 );
		if (ret != 0)
		{
			std::cout << "error running : " << lua_tostring(L, -1) << std::endl;
		}
		else
		{
			//lua_getglobal(L, Key);
			std::cout << "Got <" << Key << "> from Lua:(" << copyGlobalString(L, Key) << ")" << std::endl;
			//lua_pop
		}

      }

      std::cout << "---------------------------------------------------------" << std::endl;

      lua_close(L);
  } // RunScript

  /** ScriptHost, RunScript3:
   *  Detailed description.
   *  @param script TODO
   * @return TODO
   */
  void ScriptHost::RunScript3(const std::string& script) const {
      using namespace luabind;

      int s(0);
      L = luaL_newstate();
      //luaL_openlibs(L);
      //openLuaLibs (L);

      //luaL_Reg iolib; iolib.name = LUA_IOLIBNAME; iolib.func = luaopen_io;
      //openLuaLib (L, &iolib);

      //openLuaLib (L, LUA_LOADLIBNAME);
      openLuaLib (L, "_G");
      openLuaLib (L, LUA_IOLIBNAME);

      //plainc::Register( L );

      const char* luascript = "io=ioCreate()\n" \
                              "ioWrite( io, \"Hello World from String!\")\n" \
                              "ioDelete(io)";

      // A file
      //std::string& luaFileContent = m_Loader.FL_LOADASSTRING("L/hello.L");
      s = luaL_loadstring( L, script.c_str() );

      //s = luaL_loadstring( L, luascript );
      if ( s == 0 ) {
        lua_pcall( L, 0, LUA_MULTRET, 0 );
      }

      std::cout << "------------------------------------------------" << std::endl;

      lua_close(L);
  } // RunScript

  /** ScriptHost, RunScript2:
   *  Detailed description.
   *  @param script TODO
   * @return TODO
   */
  void ScriptHost::RunScript2(const std::string& script) const {
      using namespace luabind;

      int s(0);
      L = luaL_newstate();
      /* deprecated 5.0 stuff
              //luaopen_base(L);
              //luaopen_math(L);
              //luaopen_string(L);
              //luaopen_table(L);
              //luaopen_io(L);
              //luaL_openlibs(L);
              //open(L);
       */
      //openLuaLibs(L);

      //openLuaLib(L, luaL_Reg(LUA_IOLIBNAME, luaopen_io);

      module(L)
      [
          def("greet", &greet)
      ];

      testclass a("asd");

      module(L)
      [
          class_<testclass>("testclass")
          .def( constructor<const std::string & >() )
          .def("print_string", &testclass::print_string)
      ];

      // A script
      const char* luascript = "io=ioCreate()\n" \
                              "ioWrite( io, \"Hello World from String!\")\n" \
                              "ioDelete(io)";
      plainc::Register( L );

      std::cout << "------------------------------------------------" << std::endl;
      std::cout << "Calling from string: " << std::endl;
      s = luaL_loadstring( L, luascript );

      if ( s == 0 ) {
        lua_pcall( L, 0, LUA_MULTRET, 0 );
      }

      // A file
      //std::string& luaFileContent = m_Loader.FL_LOADASSTRING("L/hello.L");
      s = luaL_loadstring( L, script.c_str() );

      if ( s == 0 ) {
          lua_pcall( L, 0, LUA_MULTRET, 0 );
      }

      std::cout << "------------------------------------------------" << std::endl;

      lua_close(L);
  } // RunScript2
}
