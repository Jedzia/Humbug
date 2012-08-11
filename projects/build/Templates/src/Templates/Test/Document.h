#ifndef TEMPLATES_TEST_DOCUMENT_H
#define TEMPLATES_TEST_DOCUMENT_H


#include "../global.h"
//
namespace templates {

namespace test {

// implement the state machine Document
class PLATFORM_DECL Document {
  protected:
    // Mother class of all the classes representing states
    class PLATFORM_DECL AnyState {
      public:
        virtual ~AnyState();

        // return the upper state
        virtual AnyState * _upper(Document &) = 0;

        // perform the 'do activity'
        virtual void _do(Document &);

        virtual void create(Document &);

        // the current state doesn't manage the event myTrigger, give it to the upper state
        virtual void myTrigger(Document & stm);

        // the current state doesn't manage the event clostDocument, give it to the upper state
        virtual void clostDocument(Document & stm);

    };
    
    // implement the state Document
    class PLATFORM_DECL Document_State : public AnyState {
      public:
        // implement the state Open
        class PLATFORM_DECL Open_State : public AnyState {
          public:
            virtual ~Open_State();

            // returns the state containing the current
            virtual AnyState * _upper(Document & stm);

            // to manage the event clostDocument
            virtual void clostDocument(Document & stm);

        };
        
        // implement the state Deleted
        class PLATFORM_DECL Deleted_State : public AnyState {
          public:
            virtual ~Deleted_State();

            virtual bool _completion(Document & stm);

            // to manage the event create
            virtual void create(Document & stm);

            // returns the state containing the current
            virtual AnyState * _upper(Document & stm);

        };
        
        // implement the state Closed
        class PLATFORM_DECL Closed_State : public AnyState {
          public:
            virtual ~Closed_State();

            virtual bool _completion(Document & stm);

            // to manage the event create
            virtual void create(Document & stm);

            // returns the state containing the current
            virtual AnyState * _upper(Document & stm);

            // to manage the event myTrigger
            virtual void myTrigger(Document & stm);

        };
        
        virtual ~Document_State();

        // memorize the instance of the state Open, internal
        Open_State _open_state;

        // memorize the instance of the state Closed, internal
        Closed_State _closed_state;

        // memorize the instance of the state Deleted, internal
        Deleted_State _deleted_state;

        // to manage the event create
        virtual void create(Document & stm);

        // returns the state containing the current
        virtual AnyState * _upper(Document &);

    };
    
    // memorize the instance of the state Document, internal
    Document_State _document_state;


  public:
    Document();

    virtual ~Document();

    // the operation you call to signal the event create
    bool create();

  friend class Document_State::Open_State;
  friend class Document_State::Closed_State;
  friend class Document_State::Deleted_State;
  friend class Document_State;
    // to execute the current state 'do activity'
    void doActivity();


  protected:
    // change the current state, internal
    inline void _set_currentState(AnyState & st);

    // execution done, internal
    void _final();

    // contains the current state, internal
    AnyState * _current_state;


  public:
    // the operation you call to signal the event myTrigger
    bool myTrigger();

    // the operation you call to signal the event clostDocument
    bool clostDocument();

};
// change the current state, internal
inline void Document::_set_currentState(Document::AnyState & st) {
    _current_state = &st;
}


} // namespace templates::test

} // namespace templates
#endif
