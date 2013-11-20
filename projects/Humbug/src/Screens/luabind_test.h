/*
 * luabind_test.h
 *
 *  Created on: Apr 25, 2012
 *      Author: jschober
 */

#ifndef __LUABIND_TEST_H__
#define __LUABIND_TEST_H__

//#ifdef _HAS_LUA_BIND_

#include "luabind_macros.h"

#include <string>

// extend existing luabind namespace!
namespace luabind
{

    class A
    {
        std::string s;
    public:
        A()
        {
            std::cout << "A::A() called..." << std::endl;
        }

        A( const std::string& t ) : s(t)
        {
            std::cout << "A::A('" << t << "') called..." << std::endl;
        }

        void write( const char * a )
        {
            std::cout << s << ": " << a << std::endl;
        }

		void print_string() { std::cout << m_string << "\n"; }

	private:
		std::string m_string;
	};

    class B : public A
    {
    public:
        enum foo
        {
            IDLE = 15,
            BUSY
        };
        // Inner class
        class C
        {
        public:
            C()
            {
                std::cout << "C::C() called..." << std::endl;
            }
        };

        B() : A("class B")
        {
            std::cout << "B::B() called..." << std::endl;
        }

        B( const std::string& t ) : A(t)
        {
            std::cout << "B::B('" << t << "') called..." << std::endl;
        }

    };

    void say( const char * a, const char* b )
    {
        std::cout << a << " '" << b << "'" << std::endl;
    }

    const char *luascript = "pei.say( 'Say:',\"Hello World!\")\n" \
                            "a = pei.A('Title')\n" \
                            "a:write('foobar')" \
                            "b = pei.B()" \
                            "b:write('From B')" \
                            "c = pei.B.C()" \
                            ;

    void Register( lua_State* lua )
    {
        // do not forget to open()
        luabind::open(lua);

        //luabind::module_ module( lua, "pei" );

        //module[ luabind::def("say", &say ) ];

		module(lua)
			[
				class_<A>("A")
				.def(constructor<const std::string&>())
				.def("print_string", &A::print_string)
			];

        /*LUA_DECLARE_CLASS( A );
            //LUA_DECLARE_CTOR( A );
			//__luaA.def( luabind::constructor< __luaA >() );
            //LUA_DECLARE_CTOR_1( A, const std::string& );
            //LUA_DECLARE_METHOD( A, write );
        LUA_DEFINE_CLASS( module, A );*/

        /*LUA_DECLARE_INNER_CLASS( B, C );
            LUA_DECLARE_CTOR( C );
        LUA_END_DECLARE();

//        luabind::class_<B::C> c("C");
//        c.def(luabind::constructor<>());
        LUA_DECLARE_CLASS( B );
            LUA_BEGIN_ENUM( B, consts )
                luabind::value("IDLE", B::IDLE ),
                luabind::value("BUSY", B::BUSY )
            ];
            LUA_BEGIN_SCOPE( B )
                LUA_CLASS( C )
            LUA_END_SCOPE();
            LUA_DECLARE_CTOR( B );
            LUA_DECLARE_CTOR_1( B, const std::string& );
            LUA_DECLARE_METHOD( B, write );

        LUA_DEFINE_CLASS( module, B );*/


//        luabind::class_<A> a("A");
//        a.def(constructor<const std::string&>())
//         .def( "write", &A::write );
//        module[ a ];
    }
}

//#endif

#endif /* __LUABIND_TEST_H__ */
