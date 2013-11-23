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

#include <string>
#include "boost/smart_ptr/scoped_ptr.hpp"
#include "boost/smart_ptr/shared_ptr.hpp"
#include <lua.hpp>
#include <luabind/luabind.hpp>

//#include <luabind/scope.hpp>

//typedef struct lua_State lua_State;

namespace shost {

	struct PropA
	{
		int a;

		void greet(){
			std::cout << "hello world from PropA!\n";
		}
	};
	
	template<class Callee, class X1, class X2>
	class luascript
	{
		struct Prop
		{
			Prop()
			{

			};

			~Prop()
			{

			};
			int a;

			void greet(){
				std::cout << "hello world from PropA!\n";
			}
			X1 dataX1;
		};

	public:
		typedef boost::shared_ptr<luascript<Callee, X1, X2>> ScriptPointer;
		typedef luascript<Callee, X1, X2> type;

		~luascript()
		{
			lua_close(m_L);
		};

		template<class Callee, class X1, class X2>
		void run_script(const Callee supply, X1& ret1, X2& ret2)
		{
			ret1 = 2 * supply;
			ret2 = 4 * supply;
			
			std::cout << "" << __FUNCTION__ << " ticks: " << supply;
			std::cout << " x: " << ret1;
			std::cout << " y: " << ret2 ;
			std::cout << " X1: " << data.dataX1 << std::endl;

			lua_pushvalue(m_L, -1); 
			int ret = lua_pcall( m_L, 0, LUA_MULTRET, 0 );
			if (ret != 0) {
				std::cout << "[run_script] error running : " << lua_tostring(m_L, -1) << std::endl;
			}

		};

		void init()
		{
			// do the module[L] init stuff here with a templated class ?

		};

	protected:

	private:
		template<class T>
		void push(T& value)
		{
			luabind::push<T>(m_L, value);
		}

		template<class T>
		void pushglobal(T& value, const char *var)
		{
			luabind::push<T>(m_L, value);
			setglobal(var);
		}

		void  setglobal(const char *var)
		{
			lua_setglobal(m_L, var);
		};

		luascript(lua_State* L, std::string scriptText)
			:m_L(L), m_scriptText(scriptText), dataX1(666)
		{
			//std::cout << " Callee: " << sizeof(Callee) << std::endl;
			std::cout << " Callee: " << typeid(Callee).name() << std::endl;
			data.dataX1 = 777;
			pushglobal( boost::ref( data ), "Host");
			//luabind::push<X1>(L, dataX1);
			//luabind::push<type>(L, boost::ref(*this));
			//lua_setglobal(L, "Host");

		};

		lua_State* m_L;
		std::string m_scriptText;

		Prop data;
		X1 dataX1;
		X2 dataX2;

		friend class ScriptHost;
	};


  class ScriptHost {
public:

      ScriptHost();
      ~ScriptHost();

      /** ScriptHost, Str:
       *  Detailed description.
       *  @return TODO
       */
      std::string Str() const { return str; }

      /** ScriptHost, Str:
       *  Detailed description.
       *  @param val TODO
       */
      void Str(std::string val) { str = val; }
	  //luabind::module_ RegisterModule(const std::string& script) const;

      /** ScriptHost, Language:
       *  Detailed description.
       *  @param x TODO
       *  @return TODO
       */
	  void RunScript(const std::string& script) const;

	  void RunScript2(const std::string& script) const;
	  void RunScript3(const std::string& script) const;
	  void RunScript4(const std::string& script) const;
	  void RunScript5(const std::string& script) const;
	  void RunScript6(const std::string& script);

	  template<class Callee, class X1, class X2>
	  void run_script(const Callee supply, X1& ret1, X2& ret2)
	  {

	  };

	  template<class Callee, class X1, class X2>
	  boost::shared_ptr<luascript<Callee, X1, X2>> generate(const std::string& script)
	  {
		  using namespace luabind;
		  lua_State *L =  initLua();
		  module(L)
			  [
				  class_<PropA>("PropA")
				  .def_readwrite("a", &PropA::a),
				  class_<Callee>("HostX"),
				  class_<luascript<Callee, X1, X2>::Prop>("HostType")
				  //.def_readwrite("X1", &luascript<Callee, X1, X2>::dataX1)
				  //.def_readwrite("X2", &luascript<Callee, X1, X2>::dataX2)
				  .def_readwrite("X1", &luascript<Callee, X1, X2>::Prop::dataX1)

			  ];

		  int s = luaL_loadstring( L, script.c_str() );
		  //luascript<Callee, X1, X2> *scr = new luascript<Callee, X1, X2>(initLua());
		  //scr::ScriptPointer result(scr);
		  boost::shared_ptr<luascript<Callee, X1, X2>> result(new luascript<Callee, X1, X2>(L, script));
		  return result;
		  //return 8;
	  };
	 
	  lua_State* initLua();
	  void closeLua(lua_State* L);

private:
	struct ScriptHostImpl;
	boost::scoped_ptr<ScriptHostImpl> pimpl_;

      int i;
      std::string str;
  };

}
#endif // ifndef GAMEOBJECTS_SCRIPTHOST_H
