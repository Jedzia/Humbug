/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScriptHostImpl.h class.
 * \folder     $(folder)
 * \file       ScriptHostImpl.h
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/

struct ScriptHost::ScriptHostImpl {
    lua_State* L;
    int x;

    /** ScriptHostImpl, push:
     *  Detailed description.
     *  @param value TODO
     */
    template<class T>
    void push(T& value){
        luabind::push<T>(L, value);
    }
    /** ScriptHostImpl, pushglobal:
     *  Detailed description.
     *  @param value TODO
     * @param var TODO
     */
    template<class T>
    void pushglobal(T& value, const char* var){
        luabind::push<T>(L, value);
        setglobal(var);
    }
    /** ScriptHostImpl, setglobal:
     *  Detailed description.
     *  @param var TODO
     */
    void  setglobal(const char* var){
        lua_setglobal(L, var);
    }
};
