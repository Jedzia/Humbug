#ifndef TEMPLATES_TEST_TELEPHONE_H
#define TEMPLATES_TEST_TELEPHONE_H


#include "../global.h"
//
namespace templates {

namespace test {

// implement the state machine Telephone
class PLATFORM_DECL Telephone {
  protected:
    // Mother class of all the classes representing states
    class PLATFORM_DECL AnyState {
      public:
        virtual ~AnyState();

        // return the upper state
        virtual AnyState * _upper(Telephone &) = 0;

        // perform the 'do activity'
        virtual void _do(Telephone &);

        virtual void create(Telephone &);

        // the current state doesn't manage the event makecall, give it to the upper state
        virtual void makecall(Telephone & stm);

        // the current state doesn't manage the event makeOnHook, give it to the upper state
        virtual void makeOnHook(Telephone & stm);

    };
    
    // implement the state Telephone
    class PLATFORM_DECL Telephone_State : public AnyState {
      public:
        // implement the state Idle
        class PLATFORM_DECL Idle_State : public AnyState {
          public:
            virtual ~Idle_State();

            // returns the state containing the current
            virtual AnyState * _upper(Telephone & stm);

            // to manage the event makecall
            virtual void makecall(Telephone & stm);

        };
        
        // implement the state Cool
        class PLATFORM_DECL Cool_State : public AnyState {
          public:
            virtual ~Cool_State();

            // returns the state containing the current
            virtual AnyState * _upper(Telephone & stm);

            virtual bool _completion(Telephone & stm);

            // to manage the event create
            virtual void create(Telephone & stm);

        };
        
        // implement the state Dump
        class PLATFORM_DECL Dump_State : public AnyState {
          public:
            virtual ~Dump_State();

            // returns the state containing the current
            virtual AnyState * _upper(Telephone & stm);

        };
        
        // implement the state Active
        class PLATFORM_DECL Active_State : public AnyState {
          public:
            virtual ~Active_State();

            // returns the state containing the current
            virtual AnyState * _upper(Telephone & stm);

            // to manage the event makeOnHook
            virtual void makeOnHook(Telephone & stm);

            virtual bool _completion(Telephone & stm);

            // to manage the event create
            virtual void create(Telephone & stm);

            // perform the 'do activity'
            virtual void _do(Telephone & stm);

        };
        
        virtual ~Telephone_State();

        // memorize the instance of the state Idle, internal
        Idle_State _idle_state;

        // memorize the instance of the state Active, internal
        Active_State _active_state;

        // to manage the event create
        virtual void create(Telephone & stm);

        // returns the state containing the current
        virtual AnyState * _upper(Telephone &);

        // memorize the instance of the state Dump, internal
        Dump_State _dump_state;

        // memorize the instance of the state Cool, internal
        Cool_State _cool_state;

        // implement a junction, through an operation because shared, internal
        void _junction1(Telephone & stm);

    };
    

  public:
    bool power;


  protected:
    // memorize the instance of the state Telephone, internal
    Telephone_State _telephone_state;


  public:
    Telephone();

    virtual ~Telephone();

    // the operation you call to signal the event create
    bool create();

  friend class Telephone_State::Idle_State;
  friend class Telephone_State::Active_State;
  friend class Telephone_State;
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
    // the operation you call to signal the event makecall
    bool makecall();

    // the operation you call to signal the event makeOnHook
    bool makeOnHook();

  friend class Telephone_State::Dump_State;
  friend class Telephone_State::Cool_State;
};
// change the current state, internal
inline void Telephone::_set_currentState(Telephone::AnyState & st) {
    _current_state = &st;
}


} // namespace templates::test

} // namespace templates
#endif
