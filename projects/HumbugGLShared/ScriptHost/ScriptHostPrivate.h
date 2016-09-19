/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScriptHostPrivate.h class.
 * \folder     $(folder)
 * \file       ScriptHostPrivate.h
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef SCRIPTHOST_SCRIPTHOSTPRIVATE_H
#define SCRIPTHOST_SCRIPTHOSTPRIVATE_H

namespace shost {
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

  class LuaReg {
public:

      /** LuaReg, openLuaLib:
       *  Detailed description.
       *  @param L TODO
       * @param lib TODO
       */
      static void openLuaLib (lua_State* L, const luaL_Reg* lib) {
          /* call open functions from 'loadedlibs' and set results to global table */
          luaL_requiref(L, lib->name, lib->func, 1);
          lua_pop(L, 1);          /* remove lib */
      }
      /** LuaReg, openLuaLib:
       *  Detailed description.
       *  @param L TODO
       * @param name TODO
       */
      static void openLuaLib (lua_State* L, const char* name) {
          const luaL_Reg* lib;

          /* call open functions from 'loadedlibs' and set results to global table */
          for (lib = loadedlibs; lib->func; lib++) {
              if (strcmp(name, lib->name) == 0) {
                  luaL_requiref(L, lib->name, lib->func, 1);
                  lua_pop(L, 1);                  /* remove lib */
              }
          }
      }
      /** LuaReg, openLuaLibs:
       *  Detailed description.
       *  @param L TODO
       */
      static void openLuaLibs (lua_State* L) {
          const luaL_Reg* lib;

          /* call open functions from 'loadedlibs' and set results to global table */
          for (lib = loadedlibs; lib->func; lib++) {
              luaL_requiref(L, lib->name, lib->func, 1);
              lua_pop(L, 1);      /* remove lib */
          }
      }
  };

  struct LuaVars {

    /** LuaVars, copyGlobalString:
   *  Copy the content of a global string.
   * @param L Lua State
   * @param name The name of the global variable, that holds the string data.
   * @return the content of the lua string variable specified by @param name as
   * std::string.
   */
  static std::string copyGlobalString(lua_State* L, const char* name) {
      char* s = NULL;
      lua_getglobal(L, name);

      if ( !lua_isnil(L, -1) ) {
          s = strdup( lua_tostring(L, -1) );
      }

      lua_pop(L, 1);
      std::string str(s);
	  // owner has to delete the character data.
      delete s;

      return str;
  }
};

}
#endif // ifndef SCRIPTHOST_SCRIPTHOSTPRIVATE_H
