
#include "../stdafx.h"
//
#include "Telephone.h"

//
#include <build/cmake/include/debug.h>
namespace templates {

namespace test {

Telephone::AnyState::~AnyState() {
}

// perform the 'do activity'
void Telephone::AnyState::_do(Telephone &) {
}

void Telephone::AnyState::create(Telephone &) {
}

// the current state doesn't manage the event makecall, give it to the upper state
void Telephone::AnyState::makecall(Telephone & stm) {
    AnyState * st = _upper(stm);
  
    if (st != 0)
      st->makecall(stm);
#ifdef VERBOSE_STATE_MACHINE
    else
      puts("DEBUG : transition makecall not expected");
#endif
}

// the current state doesn't manage the event makeOnHook, give it to the upper state
void Telephone::AnyState::makeOnHook(Telephone & stm) {
    AnyState * st = _upper(stm);
  
    if (st != 0)
      st->makeOnHook(stm);
#ifdef VERBOSE_STATE_MACHINE
    else
      puts("DEBUG : transition makeOnHook not expected");
#endif
}

Telephone::Telephone_State::Idle_State::~Idle_State() {
}

// returns the state containing the current
Telephone::AnyState * Telephone::Telephone_State::Idle_State::_upper(Telephone & stm) {
    return &stm._telephone_state;
}

// to manage the event makecall
void Telephone::Telephone_State::Idle_State::makecall(Telephone & stm) {
    if (stm.power) {
      stm._set_currentState(stm._telephone_state._active_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Telephone.Active");
#endif
      stm._telephone_state._active_state.create(stm);
    }
}

Telephone::Telephone_State::Cool_State::~Cool_State() {
}

// returns the state containing the current
Telephone::AnyState * Telephone::Telephone_State::Cool_State::_upper(Telephone & stm) {
    return &stm._telephone_state;
}

bool Telephone::Telephone_State::Cool_State::_completion(Telephone & stm) {
    {
      stm._set_currentState(stm._telephone_state._idle_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Telephone.Idle");
#endif
      return (bool) 1;
    }
}

// to manage the event create
void Telephone::Telephone_State::Cool_State::create(Telephone & stm) {
  	_completion(stm);
}

Telephone::Telephone_State::Dump_State::~Dump_State() {
}

// returns the state containing the current
Telephone::AnyState * Telephone::Telephone_State::Dump_State::_upper(Telephone & stm) {
    return &stm._telephone_state;
}

Telephone::Telephone_State::Active_State::~Active_State() {
}

// returns the state containing the current
Telephone::AnyState * Telephone::Telephone_State::Active_State::_upper(Telephone & stm) {
    return &stm._telephone_state;
}

// to manage the event makeOnHook
void Telephone::Telephone_State::Active_State::makeOnHook(Telephone & stm) {
    _do(stm);
    if (_completion(stm)) return;
    {
      stm._set_currentState(stm._telephone_state._idle_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Telephone.Idle");
#endif
    }
}

bool Telephone::Telephone_State::Active_State::_completion(Telephone & stm) {
    _do(stm);
    {
      stm._set_currentState(stm._telephone_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Telephone");
#endif
      stm._telephone_state._junction1(stm);
      return (bool) 1;
    }
}

// to manage the event create
void Telephone::Telephone_State::Active_State::create(Telephone & stm) {
  	_completion(stm);
}

// perform the 'do activity'
void Telephone::Telephone_State::Active_State::_do(Telephone & stm) {
#ifdef VERBOSE_STATE_MACHINE
  	puts("DEBUG : execute do behavior of .Telephone.Active");
#endif
  stm.power = false;
}

Telephone::Telephone_State::~Telephone_State() {
}

// to manage the event create
void Telephone::Telephone_State::create(Telephone & stm) {
    {
      stm._set_currentState(stm._telephone_state._idle_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Telephone.Idle");
#endif
    }
}

// returns the state containing the current
Telephone::AnyState * Telephone::Telephone_State::_upper(Telephone &) {
    return 0;
}

// implement a junction, through an operation because shared, internal
void Telephone::Telephone_State::_junction1(Telephone & stm) {
    if (stm.power) {
      stm._set_currentState(stm._telephone_state._dump_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Telephone.Dump");
#endif
    }
    else {
      stm._set_currentState(stm._telephone_state._cool_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Telephone.Cool");
#endif
      stm._telephone_state._cool_state.create(stm);
    }
}

Telephone::Telephone() {
    _current_state = 0;
}

Telephone::~Telephone() {
}

// the operation you call to signal the event create
bool Telephone::create() {
  if (_current_state == 0)
  (_current_state = &(*this)._telephone_state)->create(*this);
  return (_current_state != 0);
}

// to execute the current state 'do activity'
void Telephone::doActivity() {
    _current_state->_do(*this);
}

// execution done, internal
void Telephone::_final() {
    _current_state = 0;
#ifdef VERBOSE_STATE_MACHINE
    puts("DEBUG : final state reached");
#endif
}

// the operation you call to signal the event makecall
bool Telephone::makecall() {
    if (_current_state != 0) {
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : fire trigger makecall");
#endif
      _current_state->makecall(*this);
    }
    return (_current_state != 0);
}

// the operation you call to signal the event makeOnHook
bool Telephone::makeOnHook() {
    if (_current_state != 0) {
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : fire trigger makeOnHook");
#endif
      _current_state->makeOnHook(*this);
    }
    return (_current_state != 0);
}


} // namespace templates::test

} // namespace templates
