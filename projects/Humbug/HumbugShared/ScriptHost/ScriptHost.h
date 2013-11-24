/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScriptHost.h class.
 * \folder     $(folder)
 * \file       ScriptHost.h
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef SCRIPTHOST_SCRIPTHOST_H
#define SCRIPTHOST_SCRIPTHOST_H

#include "LuaScript.h"
#include "boost/smart_ptr/scoped_ptr.hpp"
#include "boost/smart_ptr/shared_ptr.hpp"
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <string>

namespace shost {
  /** ScriptHost:
   *  Detailed description.
   *  @return TODO
   */
  class ScriptHost {
public:

      ScriptHost();
      ~ScriptHost();

      /** ScriptHost, Str:
       *  Detailed description.
       *  @return TODO
       */
      std::string Str() const { return str; }

      /** $(class), Str:
       *  Detailed description.
       *  @param val TODO
       */
      void Str(std::string val) { str = val; }

      void RunScript(const std::string& script) const;

      void RunScript2(const std::string& script) const;

      void RunScript3(const std::string& script) const;

      void RunScript4(const std::string& script) const;

      void RunScript5(const std::string& script) const;

      void RunScript6(const std::string& script);

      /** $(class), generate:
       *  Detailed description.
       *  @param script TODO
       * @return TODO
       */
      template<class Callee, class X1, class X2>
      boost::shared_ptr<LuaScript<Callee, X1,
		  X2> > generate(const std::string& script, const std::string& host, const std::string& x1, const std::string& x2){
          using namespace luabind;
          lua_State* L = initLua();
          luabind::module(L)
          [
              //class_<Callee>("HostX"),
              class_<LuaScript<Callee, X1, X2 >> ("HostType")
              //.def_readwrite("X1", &LuaScript<Callee, X1, X2>::dataX1)
              //.def_readwrite("X2", &LuaScript<Callee, X1, X2>::dataX2)
			  .def_readonly(host.c_str(), &LuaScript<Callee, X1, X2>::host)
			  .def_readwrite(x1.c_str(), &LuaScript<Callee, X1, X2>::dataX1)
			  .def_readwrite(x2.c_str() , &LuaScript<Callee, X1, X2>::dataX2)
          ];

          // Compile the script. Todo: error checking
          int s = luaL_loadstring( L, script.c_str() );
          boost::shared_ptr<LuaScript<Callee, X1, X2> > result( new LuaScript<Callee, X1, X2>(L, script) );
          return result;
      } // generate
      static lua_State * initLua();

      static void closeLua(lua_State* L);

private:

      struct ScriptHostImpl;
      boost::scoped_ptr<ScriptHostImpl> pimpl_;

      int i;
      std::string str;
  };
}
#endif // ifndef GAMEOBJECTS_SCRIPTHOST_H
