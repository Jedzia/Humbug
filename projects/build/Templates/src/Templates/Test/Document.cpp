
#include "../stdafx.h"
//
#include "Document.h"

//
#include <build/cmake/include/debug.h>
namespace templates {

namespace test {

Document::AnyState::~AnyState() {
}

// perform the 'do activity'
void Document::AnyState::_do(Document &) {
}

void Document::AnyState::create(Document &) {
}

// the current state doesn't manage the event myTrigger, give it to the upper state
void Document::AnyState::myTrigger(Document & stm) {
    AnyState * st = _upper(stm);
  
    if (st != 0)
      st->myTrigger(stm);
#ifdef VERBOSE_STATE_MACHINE
    else
      puts("DEBUG : transition myTrigger not expected");
#endif
}

// the current state doesn't manage the event clostDocument, give it to the upper state
void Document::AnyState::clostDocument(Document & stm) {
    AnyState * st = _upper(stm);
  
    if (st != 0)
      st->clostDocument(stm);
#ifdef VERBOSE_STATE_MACHINE
    else
      puts("DEBUG : transition clostDocument not expected");
#endif
}

Document::Document_State::Open_State::~Open_State() {
}

// returns the state containing the current
Document::AnyState * Document::Document_State::Open_State::_upper(Document & stm) {
    return &stm._document_state;
}

// to manage the event clostDocument
void Document::Document_State::Open_State::clostDocument(Document & stm) {
    {
      stm._set_currentState(stm._document_state._closed_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Document.Closed");
#endif
      stm._document_state._closed_state.create(stm);
    }
}

Document::Document_State::Deleted_State::~Deleted_State() {
}

bool Document::Document_State::Deleted_State::_completion(Document & stm) {
    {
      stm._set_currentState(stm._document_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Document");
#endif
      stm._final();
      return (bool) 1;
    }
}

// to manage the event create
void Document::Document_State::Deleted_State::create(Document & stm) {
  	_completion(stm);
}

// returns the state containing the current
Document::AnyState * Document::Document_State::Deleted_State::_upper(Document & stm) {
    return &stm._document_state;
}

Document::Document_State::Closed_State::~Closed_State() {
}

bool Document::Document_State::Closed_State::_completion(Document & stm) {
    if (false) {
      stm._set_currentState(stm._document_state._deleted_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Document.Deleted");
#endif
      stm._document_state._deleted_state.create(stm);
      return (bool) 1;
    }
    return (bool) 0;
}

// to manage the event create
void Document::Document_State::Closed_State::create(Document & stm) {
  	_completion(stm);
}

// returns the state containing the current
Document::AnyState * Document::Document_State::Closed_State::_upper(Document & stm) {
    return &stm._document_state;
}

// to manage the event myTrigger
void Document::Document_State::Closed_State::myTrigger(Document & stm) {
    if (_completion(stm)) return;
    {
      stm._set_currentState(stm._document_state._open_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Document.Open");
#endif
    }
}

Document::Document_State::~Document_State() {
}

// to manage the event create
void Document::Document_State::create(Document & stm) {
    {
      stm._set_currentState(stm._document_state._closed_state);
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : current state is now .Document.Closed");
#endif
      stm._document_state._closed_state.create(stm);
    }
}

// returns the state containing the current
Document::AnyState * Document::Document_State::_upper(Document &) {
    return 0;
}

Document::Document() {
    _current_state = 0;
}

Document::~Document() {
}

// the operation you call to signal the event create
bool Document::create() {
  if (_current_state == 0)
  (_current_state = &(*this)._document_state)->create(*this);
  return (_current_state != 0);
}

// to execute the current state 'do activity'
void Document::doActivity() {
    _current_state->_do(*this);
}

// execution done, internal
void Document::_final() {
    _current_state = 0;
#ifdef VERBOSE_STATE_MACHINE
    puts("DEBUG : final state reached");
#endif
}

// the operation you call to signal the event myTrigger
bool Document::myTrigger() {
    if (_current_state != 0) {
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : fire trigger myTrigger");
#endif
      _current_state->myTrigger(*this);
    }
    return (_current_state != 0);
}

// the operation you call to signal the event clostDocument
bool Document::clostDocument() {
    if (_current_state != 0) {
#ifdef VERBOSE_STATE_MACHINE
      puts("DEBUG : fire trigger clostDocument");
#endif
      _current_state->clostDocument(*this);
    }
    return (_current_state != 0);
}


} // namespace templates::test

} // namespace templates
