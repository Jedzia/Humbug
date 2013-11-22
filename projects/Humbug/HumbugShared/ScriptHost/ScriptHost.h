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
//#include <luabind/scope.hpp>

namespace shost {
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
private:
	struct ScriptHostImpl;
	boost::scoped_ptr<ScriptHostImpl> pimpl_;

      int i;
      std::string str;
  };
}
#endif // ifndef GAMEOBJECTS_SCRIPTHOST_H
