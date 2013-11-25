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
      } // run_script
      /** static_binder, GetHost:
       *  Detailed description.
       *  @return TODO
       */
      Callee GetHost() const { return host; }

      /** static_binder, SetHost:
       *  Detailed description.
       *  @param val TODO
       */
      void SetHost(Callee val) { host = val; }

      /** static_binder, GetDataX1:
       *  Detailed description.
       *  @return TODO
       */
      X1 GetDataX1() const { return dataX1; }

      /** static_binder, SetDataX1:
       *  Detailed description.
       *  @param val TODO
       */
      void SetDataX1(X1 val) { dataX1 = val; }

      /** static_binder, GetDataX2:
       *  Detailed description.
       *  @return TODO
       */
      X2 GetDataX2() const { return dataX2; }

      /** static_binder, SetDataX2:
       *  Detailed description.
       *  @param val TODO
       */
      void SetDataX2(X2 val) { dataX2 = val; }

      /** @class static_binder:
       *  Detailed description.
       *  @param s TODO
       * @return TODO
       */
      template<class Obj>
      class static_binder {
	  private:
		  static_binder(lua_State* L, Obj& value )
			  : m_L(L), m_value(value), m_cl(NULL), m_name(NULL)
		  {
		  }
public:

          ~static_binder(){
              luabind::module(m_L)
              [
                  *m_cl
              ];

              delete m_cl;
			  luabind::push<Obj>(m_L, m_value);
			  lua_setglobal(m_L, m_name);
          }
          /** ScriptHost, operator []:
           *  Detailed description.
           *  @param s TODO
           * @return TODO
           */
          void operator[](luabind::scope s)
          {}
          /*void operator()(luabind::class_<Obj> const& c){
                  //luabind::class_<World>
             }*/
          luabind::class_<Obj>& operator()(const char *name){
              //luabind::class_<World>
			  m_name = name;
              m_cl = new luabind::class_<Obj> (name);
              return *m_cl;
          }

		  /*luabind::class_<Obj>& operator->(){
			  //luabind::class_<World>
			  cl = new luabind::class_<Obj> ("World");

			  return *cl;
		  }*/

private:

          luabind::class_<Obj>* m_cl;
          lua_State* m_L;
		  Obj& m_value;
		  const char *m_name;

		  friend class LuaScript;
      };

      template<class T>
      boost::shared_ptr<static_binder<T >> AddStatic(T & value) {
          static_binder<T>* bnd = new static_binder<T>(m_L, value);
          return boost::shared_ptr<static_binder<T >> (bnd);
      }

      /** ScriptHost, AddStatic2:
       *  Detailed description.
       *  @param value TODO
       * @return TODO
       */
      template<class T>
      luabind::class_<T> * AddStatic2(T& value) {
          //luabind::module_ *m = new luabind::module(m_L);
          /*luabind::class_<T> *cl = new luabind::class_<T> ("World");
           * m[
                  cl
             ];*/

          luabind::module_* m = new luabind::module_(m_L, 0);
          luabind::class_<T>* cl = new luabind::class_<T> ("World");
          (*m)[
              *cl
          ];

          return cl;
      }
      /** ScriptHost, module:
       *  Detailed description.
       *  @param name TODO
       * @return TODO
       */
      inline luabind::module_ module(char const* name = 0){
          return luabind::module_(m_L, name);
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
      /** ScriptHost, L:
       *  Detailed description.
       *  @return TODO
       */
      lua_State * L() const { return m_L; }

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
