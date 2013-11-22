/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScriptHostIO.h class.
 * \folder     $(folder)
 * \file       ScriptHostIO.h
 * \date       2013-11-20
 * \author     Jedzia.
 *
 * modified    2013-11-20, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef SCRIPTHOST_SCRIPTHOSTIO_H
#define SCRIPTHOST_SCRIPTHOSTIO_H

namespace shost {
  class IO {
public:

      /** IO, WriteLn:
       *  Detailed description.
       *  @param c TODO
       */
      void WriteLn( const char* c ){
          std::cout << c << std::endl;
      }
  };

  class IOReg {
public:

      /** IOReg, createIO:
       *  Detailed description.
       *  @param lua TODO
       * @return TODO
       */
      static int createIO( lua_State* lua ){
          void* io = (void *)new IO();
          lua_pushlightuserdata( lua, io );
          return 1;
      }
      /** IOReg, deleteIO:
       *  Detailed description.
       *  @param lua TODO
       * @return TODO
       */
      static int deleteIO(  lua_State* lua ){
          int argc = lua_gettop( lua );

          if ( argc > 0  ) {
              IO* io = (IO *)lua_topointer( lua, 1 );
              delete io;
          }

          return 1;
      }
      /** IOReg, WriteLnIO:
       *  Detailed description.
       *  @param lua TODO
       * @return TODO
       */
      static int WriteLnIO( lua_State* lua ){
          int argc = lua_gettop( lua );

          if ( argc > 1  ) {
              IO* io = (IO *)lua_topointer( lua, 1 );
              std::string p;

              for ( int i = 2; i <= argc; i++ ) {
                  p += lua_tostring( lua, i );
              }
              io->WriteLn( p.c_str( ) );
          }

          return 1;
      }
      /** IOReg, writeLn:
       *  Detailed description.
       *  @param lua TODO
       * @return TODO
       */
      static int writeLn( lua_State* lua ){
          int argc = lua_gettop( lua );

          for ( int i = 1; i <= argc; i++ ) {
              const char* c = lua_tostring( lua, i );
              std::cout << c;
          }

          if ( argc > 0 ) {
              std::cout << std::endl;
          }

          lua_pushnumber( lua, argc );
          return 1;
      }
      /** IOReg, Register:
       *  Detailed description.
       *  @param lua TODO
       */
      static void Register( lua_State* lua ){
          lua_register( lua, "writeLn", writeLn );

          //lua_register( lua, "ioCreate", createIO );
          //lua_register( lua, "ioDelete", deleteIO );
          //lua_register( lua, "ioWrite", WriteLnIO );
          lua_register( lua, "write", WriteLnIO );
      }
  };

  struct PropA
  {
	  int a;
  };

  /** global, greet:
   *  Detailed description.
   *
   */
  void greet(){
      std::cout << "hello world!\n";
  }

  void greet2(){
	  std::cout << "hello st fnc greet2!\n";
  }

  class dummy
  {
  public:
	  void greet(){
		  std::cout << "greet !\n";
	  }
	  static void stgreet(){
		  std::cout << "greet !\n";
	  }

  };

  class SpriteModel
  {
  public:
	  SpriteModel()
		  : frame(0)
	  {

	  };

	  int Frame() const { return frame; }

	  void greet(){
		  std::cout << "greet !\n";
	  }
	  static void stgreet(){
		  std::cout << "greet !\n";
	  }
  private:
	  int frame;
  };

}

#endif // ifndef SCRIPTHOST_SCRIPTHOSTIO_H
