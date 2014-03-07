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

#include "boost/noncopyable.hpp"
#include "boost/smart_ptr/scoped_ptr.hpp"
#include "boost/smart_ptr/shared_ptr.hpp"
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <string>
#include <vector>
//#include "ScriptHost.h"


namespace luabind {
	template<typename ListType>
	struct default_converter<std::vector<ListType> > : native_converter_base<std::vector<ListType> > {
		static int compute_score(lua_State* L, int index) {
			return lua_type(L, index) == LUA_TTABLE ? 0 : -1;
		}

		std::vector<ListType> from(lua_State* L, int index) {
			std::vector<ListType> list;
			for (luabind::iterator i(luabind::object(luabind::from_stack(L, index))), end; i != end; ++i)
				list.push_back(luabind::object_cast<ListType>(*i));

			return list;
		}

		void to(lua_State* L, const std::vector<ListType>& l) {
			luabind::object list = luabind::newtable(L);
			for (size_t i = 0; i < l.size(); ++i)
				list[i+1] = l[i];

			list.push(L);
		}
	};
}

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

      typedef boost::shared_ptr<LuaScript<Callee, X1, X2> > Script;
	  //        boost::shared_ptr<LuaScript<int ,double, double>::static_binder<World>>
      typedef LuaScript<Callee, X1, X2> type;

      ~LuaScript(){
          //ScriptHost::closeLua(m_L);
	  lua_close(m_L);
      }
      
	  /** LuaScript, run_script:
       *  Detailed description.
       *  @param supply TODO
       * @param ret1 TODO
       * @param ret2 TODO
       */
      int run_script(const Callee& supply) {
          //ret1 = 2 * supply;
          //ret2 = 4 * supply;
          host = supply;

          //std::cout << "" << __FUNCTION__ << " ticks: " << supply;
          //std::cout << " x: " << ret1;
          //std::cout << " y: " << ret2;
          //std::cout << " data1: " << data1 << std::endl;

          lua_pushvalue(m_L, -1);
          int ret = lua_pcall( m_L, 0, LUA_MULTRET, 0 );

          if (ret != 0) {
              std::cout << "[run_script] error running : " << lua_tostring(m_L, -1) << std::endl;
          }
		  return ret;
      } 
	  
	  // run_script
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

      /** static_binder, GetData1:
       *  Detailed description.
       *  @return TODO
       */
      X1 GetData1() const { return data1; }

      /** static_binder, SetData1:
       *  Detailed description.
       *  @param val TODO
       */
      void SetData1(X1 val) { data1 = val; }

      /** static_binder, GetData2:
       *  Detailed description.
       *  @return TODO
       */
      X2 GetData2() const { return data2; }

      /** static_binder, SetData2:
       *  Detailed description.
       *  @param val TODO
       */
      void SetData2(X2 val) { data2 = val; }

      /** @class static_binder:
       *  Detailed description.
       *  @param s TODO
       * @return TODO
       */
      template<class Obj>
      class static_binder : boost::noncopyable {
public:

          ~static_binder(){
			  if (!m_name)
			  {
				  std::string nm("Script Object is not initialized with a name. Use operator(\"Name\") to register it.");
				  throw std::runtime_error( nm.c_str() );
			  }

			  if (!m_cl)
			  {
				  std::string nm("Script Object '");
				  nm += m_name;
				  nm += "' is not initialized with object class definitions. Use .def_readonly(), etc. to register it.";
				  throw std::runtime_error( nm.c_str() );
			  }

              luabind::module(m_L)
              [
                  *m_cl
              ];

              delete m_cl;
              luabind::push<Obj>(m_L, m_value);
			  //std::string classname(m_name);
			  //classname += "_";
			  //lua_setglobal(m_L, m_name);
			  if (m_inst_name)
			  {
				  //lua_setglobal(m_L, classname.c_str());
				  lua_setglobal(m_L, m_inst_name);
			  }
			  else
			  {
				  lua_setglobal(m_L, m_name);
			  }

          }
          /*void operator[](luabind::scope s)
             {}*/

          /*void operator()(luabind::class_<Obj> const& c){
                  //luabind::class_<World>
             }*/

          luabind::class_<Obj>& operator()(const char* name, const char* instance = NULL){
			  if (m_name)
			  {
				  std::string nm("Script Object '");
				  nm += name;
				  nm += "' is already set. Create a new one with LuaScript::AddStatic().";
				  throw std::runtime_error( nm.c_str() );
			  }

			  //std::string classname =  name;
			  //classname += "_";
			  //m_cl = new luabind::class_<Obj> (classname.c_str());
			  
			  m_cl = new luabind::class_<Obj> (name);
			  m_name =  name;
			  m_inst_name =  instance;
              return *m_cl;
          }
          /*luabind::class_<Obj>& D(const char* name){
                  m_name = name;
                  m_cl = new luabind::class_<Obj> (name);
                  return *m_cl;
             }*/

          /*luabind::class_<Obj>& operator->(){
                  //luabind::class_<World>
                  cl = new luabind::class_<Obj> ("World");

                  return *cl;
             }*/

private:

          static_binder(lua_State* L, Obj& value )
              : m_L(L), m_value(value), m_cl(NULL), m_name(NULL), m_inst_name(NULL){
              // Todo: check values.
          }
          luabind::class_<Obj>* m_cl;
          lua_State* m_L;
          Obj& m_value;
		  const char* m_name;
		  const char* m_inst_name;

          /** @class LuaScript:
           *  Detailed description.
           *  @param value TODO
           * @return TODO
           */
          friend class LuaScript;
      };

      template<class T>
      boost::shared_ptr<static_binder<T >> AddStatic(T & value) {
		  // Todo: check for double registration.
          return boost::shared_ptr<static_binder<T >> (
              new static_binder<T>(m_L, value)
              );
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

	/*  //void testme();
	  void testme()
	  {
		  int stackp = -1;

		
		  luabind::object o(luabind::globals(m_L)["myVar"]);
		  if (o)
		  {
			  // is_valid
			  // ...

			  int luatype = luabind::type(o);
			  if (luabind::type(o) == LUA_TNUMBER)
			  {
				  int otherValue = luabind::object_cast<int>(o);
				  otherValue++;
			  }
		  }



		  luabind::object o2(luabind::globals(m_L)["t"]);
		  if (o2)
		  {
			  // is_valid
			  // ...

			  int luatype = luabind::type(o2);
			  if (luabind::type(o2) == LUA_TTABLE)
			  {
				  luabind::table otherValue = luabind::object_cast<luabind::table>(o2);
				  int abc = 4;
				  abc++;
			  }
		  }

		  return;
		  bool isValid = true;
		  do 
		  {
			  luabind::object o(luabind::from_stack(m_L, stackp));
			  isValid = o.is_valid();
			  if (isValid)
			  {
				  // is_valid
				  // ...

				  int luatype = luabind::type(o);
				  if (luabind::type(o) == LUA_TTABLE)
				  {
					  int abc = 0;
					  abc++;

				  }

				  stackp--;
			  }

		  } while (isValid);

		  
	  }*/


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
          data1(666), data2(777){
          //std::cout << " Callee: " << sizeof(Callee) << std::endl;
          std::cout << "LuaScript ctor Callee: " << typeid(Callee).name() << std::endl;
          pushglobal( boost::ref( this ), "Host");
      }
      lua_State* m_L;
      std::string m_scriptText;

      Callee host;
      X1 data1;
      X2 data2;
      /** ScriptHost:
       *  Detailed description.
       *  $(javaparam)
       */
      friend class ScriptHost;
  };
}
#endif // ifndef SCRIPTHOST_LUASCRIPT_H
