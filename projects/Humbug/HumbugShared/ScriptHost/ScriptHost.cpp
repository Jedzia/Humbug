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
  ScriptHost::ScriptHost(){
      dbgOut(__FUNCTION__ );
      LOGSTREAM << "ScriptHost bIS THERE !!!!!!!!!!!!";
  }

  ScriptHost::~ScriptHost(void){
      dbgOut(__FUNCTION__);
  }

  lua_State* L;

  void greet(){
      std::cout << "hello world!\n";
  }

  class testclass {
public:

      testclass(const std::string& s) : m_string(s) {}

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

  void openLuaLib (lua_State* L, const luaL_Reg* lib) {
      /* call open functions from 'loadedlibs' and set results to global table */
      luaL_requiref(L, lib->name, lib->func, 1);
      lua_pop(L, 1);              /* remove lib */
  }

  void openLuaLib (lua_State* L, const char *name) {
	  const luaL_Reg* lib;

	  /* call open functions from 'loadedlibs' and set results to global table */
	  for (lib = loadedlibs; lib->func; lib++) {
		  if (strcmp(name, lib->name) == 0)
		  {
			  luaL_requiref(L, lib->name, lib->func, 1);
			  lua_pop(L, 1);          /* remove lib */
		  }
	  }
  }

  void openLuaLibs (lua_State* L) {
      const luaL_Reg* lib;

      /* call open functions from 'loadedlibs' and set results to global table */
      for (lib = loadedlibs; lib->func; lib++) {
          luaL_requiref(L, lib->name, lib->func, 1);
          lua_pop(L, 1);          /* remove lib */
      }
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
                  }
                  }
