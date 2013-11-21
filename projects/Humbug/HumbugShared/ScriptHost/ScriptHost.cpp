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
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "plainc_hooks.h"
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
  
  lua_State* lua;

  void greet()
  {
	  std::cout << "hello world!\n";
  }

  class testclass
  {
  public:
	  testclass(const std::string& s): m_string(s) {}
	  void print_string() { std::cout << m_string << "\n"; }

  private:
	  std::string m_string;
  };

  /** ScriptHost, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  void ScriptHost::RunScript(const std::string& script) const {
	  using namespace luabind;

	  int s(0);
	  lua = luaL_newstate();
	  luaopen_base(lua);
	  luaopen_math(lua);
	  luaopen_string(lua);
	  luaopen_table(lua);
	  open(lua);

	  module(lua)
		  [
			  def("greet", &greet)
		  ];


	  testclass a("asd");

	  module(lua)
		  [
			  class_<testclass>("testclass")
			  .def(constructor<const std::string&>())
			  .def("print_string", &testclass::print_string)
		  ];

	  // A script 
	  const char *luascript = "io=ioCreate()\n" \
		  "ioWrite( io, \"Hello World from String!\")\n" \
		  "ioDelete(io)";
	  plainc::Register( lua );

	  std::cout << "------------------------------------------------" << std::endl;
	  std::cout << "Calling from string: " << std::endl;
	  s = luaL_loadstring( lua, luascript );
	  if ( s == 0 ) {
		  lua_pcall( lua, 0, LUA_MULTRET, 0 );
	  }

	  // A file 
	  //std::string& luaFileContent = m_Loader.FL_LOADASSTRING("lua/hello.lua");
	  s = luaL_loadstring( lua, script.c_str() );
	  if ( s == 0 ) {
		  lua_pcall( lua, 0, LUA_MULTRET, 0 );
	  }

	  std::cout << "------------------------------------------------" << std::endl;

	  lua_close(lua);

  }
}
