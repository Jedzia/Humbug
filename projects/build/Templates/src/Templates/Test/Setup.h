#ifndef TEMPLATES_TEST_SETUP_H
#define TEMPLATES_TEST_SETUP_H


#include "../global.h"
//
namespace templates {

namespace test {

// implement the state machine SetupProcess
class PLATFORM_DECL SetupProcess {
  protected:
    // Mother class of all the classes representing states
    class PLATFORM_DECL AnyState {
      public:
        virtual ~AnyState();

        // return the upper state
        virtual AnyState * _upper(SetupProcess &) = 0;

        // perform the 'do activity'
        virtual void _do(SetupProcess &);

        virtual void create(SetupProcess &);

    };
    
    // implement the state SetupProcess
    class PLATFORM_DECL SetupProcess_State : public AnyState {
      public:
        // implement the state Setup
        class PLATFORM_DECL Setup_State : public AnyState {
          public:
            virtual ~Setup_State();

            virtual bool _completion(SetupProcess & stm);

            // to manage the event create
            virtual void create(SetupProcess & stm);

            // returns the state containing the current
            virtual AnyState * _upper(SetupProcess & stm);

        };
        
        // implement the state Submarine
        class PLATFORM_DECL Submarine_State : public AnyState {
          public:
            // implement the state A
            class PLATFORM_DECL A_State : public AnyState {
              public:
                virtual ~A_State();

                virtual bool _completion(SetupProcess & stm);

                // returns the state containing the current
                virtual AnyState * _upper(SetupProcess & stm);

                // to manage the event create
                virtual void create(SetupProcess & stm);

                // perform the 'entry behavior'
                void _doentry(SetupProcess & stm);


              private:
                int inp;


              public:
                // perform the 'exit behavior'
                void _doexit(SetupProcess & stm);

                // perform the 'do activity'
                virtual void _do(SetupProcess & stm);

            };
            
            // implement the state FalschEingabe
            class PLATFORM_DECL FalschEingabe_State : public AnyState {
              public:
                virtual ~FalschEingabe_State();

                virtual bool _completion(SetupProcess & stm);

                // to manage the event create
                virtual void create(SetupProcess & stm);

                // returns the state containing the current
                virtual AnyState * _upper(SetupProcess & stm);

                // perform the 'do activity'
                virtual void _do(SetupProcess & stm);

            };
            
            // implement the state B
            class PLATFORM_DECL B_State : public AnyState {
              public:
                virtual ~B_State();

                // returns the state containing the current
                virtual AnyState * _upper(SetupProcess & stm);

                virtual bool _completion(SetupProcess & stm);

                // to manage the event create
                virtual void create(SetupProcess & stm);

            };
            
            virtual ~Submarine_State();

            virtual bool _completion(SetupProcess & stm);

            // returns the state containing the current
            virtual AnyState * _upper(SetupProcess & stm);

            // memorize the instance of the state A, internal
            A_State _a_state;

            // memorize the instance of the state B, internal
            B_State _b_state;

            // to manage the event create
            virtual void create(SetupProcess & stm);

            // to manage the exit point 'Abort', defined because probably shared
            void _exit1(SetupProcess & stm);

            // memorize the instance of the state FalschEingabe, internal
            FalschEingabe_State _falscheingabe_state;

        };
        
        // implement the state Cleanup
        class PLATFORM_DECL Cleanup_State : public AnyState {
          public:
            virtual ~Cleanup_State();

            virtual bool _completion(SetupProcess & stm);

            // to manage the event create
            virtual void create(SetupProcess & stm);

            // returns the state containing the current
            virtual AnyState * _upper(SetupProcess & stm);

        };
        
        virtual ~SetupProcess_State();

        // memorize the instance of the state Setup, internal
        Setup_State _setup_state;

        // memorize the instance of the state Cleanup, internal
        Cleanup_State _cleanup_state;

        // memorize the instance of the state Submarine, internal
        Submarine_State _submarine_state;

        // to manage the event create
        virtual void create(SetupProcess & stm);

        // returns the state containing the current
        virtual AnyState * _upper(SetupProcess &);

    };
    
    // memorize the instance of the state SetupProcess, internal
    SetupProcess_State _setupprocess_state;


  public:
    SetupProcess();

    virtual ~SetupProcess();

    // the operation you call to signal the event create
    bool create();

  friend class SetupProcess_State::Setup_State;
  friend class SetupProcess_State::Cleanup_State;
  friend class SetupProcess_State::Submarine_State;
  friend class SetupProcess_State;
    // to execute the current state 'do activity'
    void doActivity();


  protected:
    // change the current state, internal
    inline void _set_currentState(AnyState & st);

    // execution done, internal
    void _final();

    // contains the current state, internal
    AnyState * _current_state;

  friend class SetupProcess_State::Submarine_State::A_State;
  friend class SetupProcess_State::Submarine_State::B_State;
  friend class SetupProcess_State::Submarine_State::FalschEingabe_State;
};
// change the current state, internal
inline void SetupProcess::_set_currentState(SetupProcess::AnyState & st) {
    _current_state = &st;
}


} // namespace templates::test

} // namespace templates
#endif
