
#include "../stdafx.h"
//
#include "Setup.h"

//
#include <build/cmake/include/debug.h>
namespace templates {

namespace test {

SetupProcess::AnyState::~AnyState() {
}

// perform the 'do activity'
void SetupProcess::AnyState::_do(SetupProcess &) {
}

void SetupProcess::AnyState::create(SetupProcess &) {
}

SetupProcess::SetupProcess_State::Setup_State::~Setup_State() {
}

bool SetupProcess::SetupProcess_State::Setup_State::_completion(SetupProcess & stm) {
    {
      stm._set_currentState(stm._setupprocess_state._submarine_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess.Submarine");
#endif
      stm._setupprocess_state._submarine_state.create(stm);
      return (bool) 1;
    }
}

// to manage the event create
void SetupProcess::SetupProcess_State::Setup_State::create(SetupProcess & stm) {
  	_completion(stm);
}

// returns the state containing the current
SetupProcess::AnyState * SetupProcess::SetupProcess_State::Setup_State::_upper(SetupProcess & stm) {
    return &stm._setupprocess_state;
}

SetupProcess::SetupProcess_State::Submarine_State::A_State::~A_State() {
}

bool SetupProcess::SetupProcess_State::Submarine_State::A_State::_completion(SetupProcess & stm) {
    _do(stm);
    if (inp > 0) {
      stm._setupprocess_state._submarine_state._a_state._doexit(stm);
      stm._set_currentState(stm._setupprocess_state._submarine_state._b_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess.Submarine.B");
#endif
      stm._setupprocess_state._submarine_state._b_state.create(stm);
      return (bool) 1;
    }
    else if (inp == -1) {
      stm._setupprocess_state._submarine_state._a_state._doexit(stm);
      stm._set_currentState(stm._setupprocess_state._submarine_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess.Submarine");
#endif
      stm._setupprocess_state._submarine_state._exit1(stm);
      return (bool) 1;
    }
    else if (inp == 0) {
      stm._setupprocess_state._submarine_state._a_state._doexit(stm);
      stm._set_currentState(stm._setupprocess_state._submarine_state._falscheingabe_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess.Submarine.FalschEingabe");
#endif
      stm._setupprocess_state._submarine_state._falscheingabe_state.create(stm);
      return (bool) 1;
    }
    return (bool) 0;
}

// returns the state containing the current
SetupProcess::AnyState * SetupProcess::SetupProcess_State::Submarine_State::A_State::_upper(SetupProcess & stm) {
    return &stm._setupprocess_state._submarine_state;
}

// to manage the event create
void SetupProcess::SetupProcess_State::Submarine_State::A_State::create(SetupProcess & stm) {
  	_doentry(stm);
  	_completion(stm);
}

// perform the 'entry behavior'
void SetupProcess::SetupProcess_State::Submarine_State::A_State::_doentry(SetupProcess & stm) {
#ifdef VERBOSE_STATE_MACHINE
  	puts("DEBUG : execute entry behavior of .SetupProcess.Submarine.A");
#endif
  puts("Enter number");
  std::cin >> inp;
}

// perform the 'exit behavior'
void SetupProcess::SetupProcess_State::Submarine_State::A_State::_doexit(SetupProcess & stm) {
#ifdef VERBOSE_STATE_MACHINE
  	puts("DEBUG : execute exit behavior of .SetupProcess.Submarine.A");
#endif
  puts("Exit");
}

// perform the 'do activity'
void SetupProcess::SetupProcess_State::Submarine_State::A_State::_do(SetupProcess & stm) {
#ifdef VERBOSE_STATE_MACHINE
  	puts("DEBUG : execute do behavior of .SetupProcess.Submarine.A");
#endif
  puts("Do");
}

SetupProcess::SetupProcess_State::Submarine_State::FalschEingabe_State::~FalschEingabe_State() {
}

bool SetupProcess::SetupProcess_State::Submarine_State::FalschEingabe_State::_completion(SetupProcess & stm) {
    _do(stm);
    {
      stm._set_currentState(stm._setupprocess_state._submarine_state._a_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess.Submarine.A");
#endif
      stm._setupprocess_state._submarine_state._a_state.create(stm);
      return (bool) 1;
    }
}

// to manage the event create
void SetupProcess::SetupProcess_State::Submarine_State::FalschEingabe_State::create(SetupProcess & stm) {
  	_completion(stm);
}

// returns the state containing the current
SetupProcess::AnyState * SetupProcess::SetupProcess_State::Submarine_State::FalschEingabe_State::_upper(SetupProcess & stm) {
    return &stm._setupprocess_state._submarine_state;
}

// perform the 'do activity'
void SetupProcess::SetupProcess_State::Submarine_State::FalschEingabe_State::_do(SetupProcess & stm) {
#ifdef VERBOSE_STATE_MACHINE
  	puts("DEBUG : execute do behavior of .SetupProcess.Submarine.FalschEingabe");
#endif
  puts("Fehler, Du Arsch. grösser als 0");
}

SetupProcess::SetupProcess_State::Submarine_State::B_State::~B_State() {
}

// returns the state containing the current
SetupProcess::AnyState * SetupProcess::SetupProcess_State::Submarine_State::B_State::_upper(SetupProcess & stm) {
    return &stm._setupprocess_state._submarine_state;
}

bool SetupProcess::SetupProcess_State::Submarine_State::B_State::_completion(SetupProcess & stm) {
    {
      stm._set_currentState(stm._setupprocess_state._submarine_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess.Submarine");
#endif
      stm._final();
      return (bool) 1;
    }
}

// to manage the event create
void SetupProcess::SetupProcess_State::Submarine_State::B_State::create(SetupProcess & stm) {
  	_completion(stm);
}

SetupProcess::SetupProcess_State::Submarine_State::~Submarine_State() {
}

bool SetupProcess::SetupProcess_State::Submarine_State::_completion(SetupProcess & stm) {
    {
      stm._set_currentState(stm._setupprocess_state._cleanup_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess.Cleanup");
#endif
      stm._setupprocess_state._cleanup_state.create(stm);
      return (bool) 1;
    }
}

// returns the state containing the current
SetupProcess::AnyState * SetupProcess::SetupProcess_State::Submarine_State::_upper(SetupProcess & stm) {
    return &stm._setupprocess_state;
}

// to manage the event create
void SetupProcess::SetupProcess_State::Submarine_State::create(SetupProcess & stm) {
    {
      stm._set_currentState(stm._setupprocess_state._submarine_state._a_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess.Submarine.A");
#endif
      stm._setupprocess_state._submarine_state._a_state.create(stm);
    }
}

// to manage the exit point 'Abort', defined because probably shared
void SetupProcess::SetupProcess_State::Submarine_State::_exit1(SetupProcess & stm) {
}

SetupProcess::SetupProcess_State::Cleanup_State::~Cleanup_State() {
}

bool SetupProcess::SetupProcess_State::Cleanup_State::_completion(SetupProcess & stm) {
    {
      stm._set_currentState(stm._setupprocess_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess");
#endif
      stm._final();
      return (bool) 1;
    }
}

// to manage the event create
void SetupProcess::SetupProcess_State::Cleanup_State::create(SetupProcess & stm) {
  	_completion(stm);
}

// returns the state containing the current
SetupProcess::AnyState * SetupProcess::SetupProcess_State::Cleanup_State::_upper(SetupProcess & stm) {
    return &stm._setupprocess_state;
}

SetupProcess::SetupProcess_State::~SetupProcess_State() {
}

// to manage the event create
void SetupProcess::SetupProcess_State::create(SetupProcess & stm) {
    {
      stm._set_currentState(stm._setupprocess_state._setup_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .SetupProcess.Setup");
#endif
      stm._setupprocess_state._setup_state.create(stm);
    }
}

// returns the state containing the current
SetupProcess::AnyState * SetupProcess::SetupProcess_State::_upper(SetupProcess &) {
    return 0;
}

SetupProcess::SetupProcess() {
    _current_state = 0;
}

SetupProcess::~SetupProcess() {
}

// the operation you call to signal the event create
bool SetupProcess::create() {
  if (_current_state == 0)
  (_current_state = &(*this)._setupprocess_state)->create(*this);
  return (_current_state != 0);
}

// to execute the current state 'do activity'
void SetupProcess::doActivity() {
    _current_state->_do(*this);
}

// execution done, internal
void SetupProcess::_final() {
    _current_state = 0;
#ifdef VERBOSE_STATE_MACHINE
    puts("DEBUG : final state reached");
#endif
}


} // namespace templates::test

} // namespace templates
