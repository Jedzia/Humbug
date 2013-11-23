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
#include "ScriptHostIO.h"
#include "ScriptHostPrivate.h"
#include "plainc_hooks.h"
#include <math.h>
#include <lua.hpp>
#include <luabind/luabind.hpp>
//#include "HumbugLib/LogManager.h"

//#include <build/cmake/include/debug.h>

namespace shost {
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

  /** $(fclass), copyGlobalString:
   *  Detailed description.
   *  @param L TODO
   * @param name TODO
   * @return TODO
   */
  std::string copyGlobalString(lua_State* L, const char* name) {
      char* s = NULL;
      lua_getglobal(L, name);

      if ( !lua_isnil(L, -1) ) {
          s = strdup( lua_tostring(L, -1) );
      }

      lua_pop(L, 1);
	  std::string str(s);
	  delete s;

      return str;
  }

#include "ScriptHostImpl.h"

  ScriptHost::ScriptHost() :
      pimpl_(new ScriptHost::ScriptHostImpl ){
      dbgOut(__FUNCTION__ );
      LOGSTREAM << "ScriptHost bIS THERE !!!!!!!!!!!!";
  }

  ScriptHost::~ScriptHost(void){
      dbgOut(__FUNCTION__);
  }

  /** ScriptHost, RunScript:
   *  Detailed description.
   *  @param script TODO
   * @return TODO
   */
  void ScriptHost::RunScript(const std::string& script) const {
      using namespace luabind;

      int s(0);
      pimpl_->L = luaL_newstate();
      //luaL_openlibs(L);
      //openLuaLibs (L);

      //luaL_Reg iolib; iolib.name = LUA_IOLIBNAME; iolib.func = luaopen_io;
      //openLuaLib (L, &iolib);

      //openLuaLib (L, LUA_LOADLIBNAME);
      LuaReg::openLuaLib (pimpl_->L, "_G");
      LuaReg::openLuaLib (pimpl_->L, LUA_IOLIBNAME);

      {
        luabind::open(pimpl_->L);
        /*module(pimpl_->L)
                [
                        class_<testclass>("testclass")
                        .def(constructor<const std::string&>())
                        .def("print_string", &testclass::print_string)
                ];*/
		
		// *** Bind a class with functions that can be instantiated in Lua ***
		// module(pimpl_->L) or
        module_& bindModule = module(pimpl_->L);
        bindModule
        [
            class_<testclass>("testclass")
            .def( constructor<const std::string & >() )
            .def("print_string", &testclass::print_string)
			//.def("writeLn", &greet2)
			//.def(sc, )
        ];
		// create and push the testclass object
		testclass luaTestObj("Created in " __FILE__);
		pimpl_->pushglobal(luaTestObj, "game");


		// *** Bind a class with functions and make it a global var ***
		luabind::class_<dummy> sc = class_<dummy>("dummy")
			.def("greet", &dummy::greet)
		    //.def("greet2", greet2)
			;
			//.scope[
			//def("greet", &dummy::greet)
			//];
		bindModule[sc];
		dummy luaDummy;
		// To make the dummy var global in Lua do:
		//luabind::push(pimpl_->L, luaDummy);
		//lua_setglobal(pimpl_->L, "dummy");
		// or 
		//pimpl_->push(luaDummy);
		//pimpl_->setglobal("dummy");
		// or
		pimpl_->pushglobal(luaDummy, "dummy");


        /* Push a global string var */
        static const char* Key = "myVar";
        static const char* value = "FromScriptHost";

        lua_pushstring(pimpl_->L, "FromScriptHost");
        lua_setglobal(pimpl_->L, Key);

		// *** Bind a static function ***
		//IOReg::createIO(pimpl_->L);
		//luabind::def("sin", &std::sin);
		luabind::scope& fn = luabind::def("greet2", greet2);
		bindModule[fn];

        // A file
        s = luaL_loadstring( pimpl_->L, script.c_str() );

        if ( s == 0 ) {
			int ret = lua_pcall( pimpl_->L, 0, LUA_MULTRET, 0 );
			if (ret != 0) {
				std::cout << "error running : " << lua_tostring(pimpl_->L, -1) << std::endl;
			}
			else {
				//char *result = copyGlobalString(pimpl_->L, Key);
				std::cout << "Got <" << Key << "> from Lua:\"" << copyGlobalString(pimpl_->L, Key) << "\"" << std::endl;
				//delete result;
			}
        }
      }

      std::cout << "---------------------------------------------------------" << std::endl;

      lua_close(pimpl_->L);
  } // RunScript

  /** ScriptHost, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  void ScriptHost::RunScript4(const std::string& script) const {
      using namespace luabind;

      int s(0);
      pimpl_->L = luaL_newstate();
      //luaL_openlibs(pimpl_->L);
      //openLuaLibs (pimpl_->L);

      //luaL_Reg iolib; iolib.name = LUA_IOLIBNAME; iolib.func = luaopen_io;
      //openLuaLib (pimpl_->L, &iolib);

      //openLuaLib (pimpl_->L, LUA_LOADLIBNAME);
      LuaReg::openLuaLib (pimpl_->L, "_G");
      LuaReg::openLuaLib (pimpl_->L, LUA_IOLIBNAME);

      //IOReg::Register(pimpl_->L);
      //IOReg::createIO(pimpl_->L);
      /* variable with an unique address */
      static const char* Key = "myVar";
      static const char* value = "FromScriptHost";

//        /* store a number */
//        lua_pushlightuserdata(pimpl_->L, (void *)&Key);  /* push address */
//        //lua_pushnumber(pimpl_->L, 666);  /* push value */
//        lua_pushstring(pimpl_->L, value);  /* push string */
//        /* registry[&Key] = myNumber */
//        lua_settable(pimpl_->L, LUA_REGISTRYINDEX);

      //luabind::push()
      //lua_pushstring(pimpl_->L, Key);
      //lua_settable(pimpl_->L, -3);
      //lua_settable(pimpl_->L, LUA_REGISTRYINDEX);

      // push string variable <myVar> with "FromScriptHost" as content to Lua.
      lua_pushstring(pimpl_->L, "FromScriptHost");
      lua_setglobal(pimpl_->L, Key);

      //plainc::Register( pimpl_->L );
      const char* luascript = "io=ioCreate()\n" \
                              "ioWrite( io, \"Hello World from String!\")\n" \
                              "ioDelete(io)";

      // A file
      //std::string& luaFileContent = m_Loader.FL_LOADASSTRING("L/hello.lua");
      s = luaL_loadstring( pimpl_->L, script.c_str() );

      //s = luaL_loadstring( pimpl_->L, luascript );
      if ( s == 0 ) {
        int ret = lua_pcall( pimpl_->L, 0, LUA_MULTRET, 0 );

        if (ret != 0) {
            std::cout << "error running : " << lua_tostring(pimpl_->L, -1) << std::endl;
        }
        else {
            //lua_getglobal(pimpl_->L, Key);
            std::cout << "Got <" << Key << "> from Lua:(" << copyGlobalString(pimpl_->L, Key) << ")" << std::endl;
            //lua_pop
            //luabind::pcall_callback_fun()
        }
      }

      std::cout << "---------------------------------------------------------" << std::endl;

      lua_close(pimpl_->L);
  } // RunScript

  /** ScriptHost, RunScript3:
   *  Detailed description.
   *  @param script TODO
   * @return TODO
   */
  void ScriptHost::RunScript3(const std::string& script) const {
      using namespace luabind;

      int s(0);
      pimpl_->L = luaL_newstate();
      //luaL_openlibs(pimpl_->L);
      //openLuaLibs (pimpl_->L);

      //luaL_Reg iolib; iolib.name = LUA_IOLIBNAME; iolib.func = luaopen_io;
      //openLuaLib (pimpl_->L, &iolib);

      //openLuaLib (pimpl_->L, LUA_LOADLIBNAME);
      LuaReg::openLuaLib (pimpl_->L, "_G");
      LuaReg::openLuaLib (pimpl_->L, LUA_IOLIBNAME);

      //plainc::Register( pimpl_->L );

      const char* luascript = "io=ioCreate()\n" \
                              "ioWrite( io, \"Hello World from String!\")\n" \
                              "ioDelete(io)";

      // A file
      //std::string& luaFileContent = m_Loader.FL_LOADASSTRING("lua/hello.lua");
      s = luaL_loadstring( pimpl_->L, script.c_str() );

      //s = luaL_loadstring( pimpl_->L, luascript );
      if ( s == 0 ) {
        lua_pcall( pimpl_->L, 0, LUA_MULTRET, 0 );
      }

      std::cout << "------------------------------------------------" << std::endl;

      lua_close(pimpl_->L);
  } // RunScript

  /** ScriptHost, RunScript2:
   *  Detailed description.
   *  @param script TODO
   * @return TODO
   */
  void ScriptHost::RunScript2(const std::string& script) const {
      using namespace luabind;

      int s(0);
      pimpl_->L = luaL_newstate();
      /* deprecated 5.0 stuff
              //luaopen_base(pimpl_->L);
              //luaopen_math(pimpl_->L);
              //luaopen_string(pimpl_->L);
              //luaopen_table(pimpl_->L);
              //luaopen_io(pimpl_->L);
              //luaL_openlibs(pimpl_->L);
              //open(pimpl_->L);
       */
      //openLuaLibs(pimpl_->L);

      //openLuaLib(pimpl_->L, luaL_Reg(LUA_IOLIBNAME, luaopen_io);

      module(pimpl_->L)
      [
          def("greet", &greet)
      ];

      testclass a("asd");

      module(pimpl_->L)
      [
          class_<testclass>("testclass")
          .def( constructor<const std::string & >() )
          .def("print_string", &testclass::print_string)
      ];

      // A script
      const char* luascript = "io=ioCreate()\n" \
                              "ioWrite( io, \"Hello World from String!\")\n" \
                              "ioDelete(io)";
      plainc::Register( pimpl_->L );

      std::cout << "------------------------------------------------" << std::endl;
      std::cout << "Calling from string: " << std::endl;
      s = luaL_loadstring( pimpl_->L, luascript );

      if ( s == 0 ) {
        lua_pcall( pimpl_->L, 0, LUA_MULTRET, 0 );
      }

      // A file
      //std::string& luaFileContent = m_Loader.FL_LOADASSTRING("lua/hello.lua");
      s = luaL_loadstring( pimpl_->L, script.c_str() );

      if ( s == 0 ) {
          lua_pcall( pimpl_->L, 0, LUA_MULTRET, 0 );
      }

      std::cout << "------------------------------------------------" << std::endl;

      lua_close(pimpl_->L);
  } // RunScript2


    
  void ScriptHost::RunScript5(const std::string& script) const {
      using namespace luabind;

      int s(0);
      pimpl_->L = luaL_newstate();
	  LuaReg::openLuaLibs(pimpl_->L);
	  luabind::open(pimpl_->L);

      module(pimpl_->L)
      [
          def("greet", &greet)
		  // get nicht, warum?
		  //, def("writeLn", &IOReg::writeLn)
      ];
	  
	  IOReg::Register(pimpl_->L);
	  module(pimpl_->L)
		  [
			  class_<PropA>("PropA")
			  .def_readwrite("a", &PropA::a)
		  ];

	  PropA b;
	  b.a = 666;
	  pimpl_->pushglobal(b, "b");


	  // A script
      const char* luascript =  "" 
							    "a=1\n" 
								"a=a+1\n" 
								"writeLn(\"a:\"..a)\n" 
								"writeLn(\"b.a:\"..b.a)\n" 
								"b.a=b.a+1\n" 
                                "greet()\n"
							  ;

      std::cout << "------------------------------------------------" << std::endl;
      std::cout << "Calling from string: " << std::endl;
      s = luaL_loadstring( pimpl_->L, luascript );

      if ( s == 0 ) {
		  lua_pushvalue(pimpl_->L, -1); 
		  int ret = lua_pcall( pimpl_->L, 0, LUA_MULTRET, 0 );
		  ret = lua_pcall( pimpl_->L, 0, LUA_MULTRET, 0 );
		if (ret != 0) {
			std::cout << "error running : " << lua_tostring(pimpl_->L, -1) << std::endl;
		}
		else {
			//char *result = copyGlobalString(pimpl_->L, Key);
			//std::cout << "Got <" << Key << "> from Lua:\"" << copyGlobalString(pimpl_->L, Key) << "\"" << std::endl;
			//delete result;
		}

      }
      std::cout << "------------------------------------------------" << std::endl;

      lua_close(pimpl_->L);
  } // RunScript2




  template<class Callee, class X1, class X2>
  class luascript
  {
  public:
	  luascript(){};
  	~luascript(){};

	void run_script(const Callee supply, X1& ret1, X2& ret2)
	{
		ret1 = 2 * supply;
		ret2 = 4 * supply;
	};

  protected:
  	
  private:
  };

  void ScriptHost::RunScript6(const std::string& script) const {
	  using namespace luabind;


	  int ticks = 60;
	  int x,y;
	  luascript<int, int, int> scr;
	  scr.run_script(ticks, x, y);

	  std::cout << "ticks: " << ticks;
	  std::cout << " x: " << x;
	  std::cout << " y: " << y << std::endl;

	  int s(0);
	  pimpl_->L = luaL_newstate();
	  LuaReg::openLuaLibs(pimpl_->L);
	  luabind::open(pimpl_->L);

	  module(pimpl_->L)
		  [
			  def("greet", &greet)
			  // get nicht, warum?
			  //, def("writeLn", &IOReg::writeLn)
		  ];

	  IOReg::Register(pimpl_->L);
	  module(pimpl_->L)
		  [
			  class_<PropA>("PropA")
			  .def_readwrite("a", &PropA::a)
		  ];

	  PropA b;
	  b.a = 666;
	  pimpl_->pushglobal(b, "b");


	  // A script
	  const char* luascript =  "" 
		  "a=1\n" 
		  "a=a+1\n" 
		  "writeLn(\"a:\"..a)\n" 
		  "writeLn(\"b.a:\"..b.a)\n" 
		  "b.a=b.a+1\n" 
		  "greet()\n"
		  ;

	  std::cout << "------------------------------------------------" << std::endl;
	  std::cout << "Calling from string: " << std::endl;
	  s = luaL_loadstring( pimpl_->L, luascript );

	  if ( s == 0 ) {
		  lua_pushvalue(pimpl_->L, -1); 
		  int ret = lua_pcall( pimpl_->L, 0, LUA_MULTRET, 0 );
		  ret = lua_pcall( pimpl_->L, 0, LUA_MULTRET, 0 );
		  if (ret != 0) {
			  std::cout << "error running : " << lua_tostring(pimpl_->L, -1) << std::endl;
		  }
		  else {
			  //char *result = copyGlobalString(pimpl_->L, Key);
			  //std::cout << "Got <" << Key << "> from Lua:\"" << copyGlobalString(pimpl_->L, Key) << "\"" << std::endl;
			  //delete result;
		  }

	  }
	  std::cout << "------------------------------------------------" << std::endl;

	  lua_close(pimpl_->L);
  } // RunScript2




/*  luabind::module_ ScriptHost::RegisterModule( const std::string& script ) const
  {
	  luabind::module_ bindModule = luabind::module(pimpl_->L);
	  return bindModule;
  }
*/
}
