/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the LuaScript class.
 * \folder     $(folder)
 * \file       LuaScript.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef SCRIPTHOST_LUASCRIPT_H
#define SCRIPTHOST_LUASCRIPT_H

#include "boost/smart_ptr/scoped_ptr.hpp"
#include "boost/smart_ptr/shared_ptr.hpp"
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <string>

namespace shost {
  /** @class LuaRegHelper:
   *  Detailed description.
   *  @param supply TODO
   * @param ret1 TODO
   * @param ret2 TODO
   */
  class LuaRegHelper {};

  /** @class LuaScript:
   *  Detailed description.
   *  @param supply TODO
   * @param ret1 TODO
   * @param ret2 TODO
   */
  template<class Callee, class X1, class X2>
  class LuaScript {
public:

      typedef boost::shared_ptr<LuaScript<Callee, X1, X2> > ScriptPointer;
      typedef LuaScript<Callee, X1, X2> type;

      ~LuaScript(){
          ScriptHost::closeLua(m_L);
      }
      /** LuaScript, run_script:
       *  Detailed description.
       *  @param supply TODO
       * @param ret1 TODO
       * @param ret2 TODO
       */
      
      void run_script(const Callee& supply) {
          //ret1 = 2 * supply;
          //ret2 = 4 * supply;
		  host = supply;

          //std::cout << "" << __FUNCTION__ << " ticks: " << supply;
          //std::cout << " x: " << ret1;
          //std::cout << " y: " << ret2;
          //std::cout << " dataX1: " << dataX1 << std::endl;

          lua_pushvalue(m_L, -1);
          int ret = lua_pcall( m_L, 0, LUA_MULTRET, 0 );

          if (ret != 0) {
              std::cout << "[run_script] error running : " << lua_tostring(m_L, -1) << std::endl;
          }
      }

	  Callee GetHost() const { return host; }
	  void SetHost(Callee val) { host = val; }
	  X1 GetDataX1() const { return dataX1; }
	  void SetDataX1(X1 val) { dataX1 = val; }
	  X2 GetDataX2() const { return dataX2; }
	  void SetDataX2(X2 val) { dataX2 = val; }

	  template<class T>
	  void AddStatic(T& value) {
	  }

protected:

private:

      /** LuaScript, push:
       *  Detailed description.
       *  @param value TODO
       */
      template<class T>
      void push(T& value) {
          luabind::push<T>(m_L, value);
      }
      /** LuaScript, pushglobal:
       *  Detailed description.
       *  @param value TODO
       * @param var TODO
       */
      template<class T>
      void pushglobal(T& value, const char* var) {
          luabind::push<T>(m_L, value);
          setglobal(var);
      }
      /** LuaScript, setglobal:
       *  Detailed description.
       *  @param var TODO
       */
      void  setglobal(const char* var){
          lua_setglobal(m_L, var);
      }
      /** LuaScript, ctor:
       *  Prevents the creation of LuaScript objects.
       * only the factory can create instances.
       *  @param var TODO
       */
      LuaScript(lua_State* L, std::string scriptText) :
          m_L(L),
          m_scriptText(scriptText),
          dataX1(666), dataX2(777){
          //std::cout << " Callee: " << sizeof(Callee) << std::endl;
          std::cout << " Callee: " << typeid(Callee).name() << std::endl;
          pushglobal( boost::ref( this ), "Host");
      }
      lua_State* m_L;
      std::string m_scriptText;

	  Callee host;
	  X1 dataX1;
	  X2 dataX2;
      /** ScriptHost:
       *  Detailed description.
       *  $(javaparam)
       */
      friend class ScriptHost;
  };
}
#endif // ifndef SCRIPTHOST_LUASCRIPT_H
