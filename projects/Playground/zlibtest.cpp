#ifndef LINUX
//////////////////////////////////////////
//                                      //
// Using zlib                           //
//                                      //
// You found this at bobobobo's weblog, //
// http://bobobobo.wordpress.com        //
//                                      //
// Creation date:  Feb 22/08            //
// Last modified:  Feb 23/08            //
//                                      //
//////////////////////////////////////////

//////////////////////////////////////////
//////////////////////////////////////////
///////////  BEFORE YOU START  ///////////
//////////////////////////////////////////
//////////////////////////////////////////

// Visit <a href="http://zlib.net/">zlib.net</a>, bookmark it,
// and <a href="http://www.zlib.net/zlib123-dll.zip">grab the dll version of zlib</a>.

// Once you get zlib, as the docs say:
// "Copy ZLIB1.DLL to the SYSTEM or the
//  SYSTEM32 directory."

// C:\WINDOWS\System32 may not work for you
// if you're on 64-bit.  Instead, use
// the C:\WINDOWS\System directory.

// If you don't do this, you get this error
// when you try to launch any program
// that uses "zlib1.dll":

/*
     "THIS APPLICATION has failed to start
      because zlib1.dll was not found.
      Re-installing the application
      may fix this problem."
*/

// This is because Windows can't find
// the dll.

// The other option is to place the
// .dll file in the same directory
// as the EXECUTABLE that uses the
// dll.  So, you'd copy out zlib1.dll
// into the Using_zlib\debug folder,
// since that's where visual studio
// dumps the final executable after building.

/////////////////////
// QUICK NOTES ABOUT .LIB AND .DLL FILES:
//
// .LIB FILES:
//
// .lib files are library files and they
// are used for static linking.  That is,
// they contain precompiled code that other
// applications can link to.  When you link
// your application with a .lib library, then
// the .lib library's code is intermixed
// with your own code in the final executable.

// .DLL FILES:
//
// .dll files are dynamically linked library files 
// and applications link to them at runtime.

/////////////
// WHAT'S A DLL?

// What's a DLL anyway?

// DLL stands for DYNAMICALLY
// LINKED LIBARY.

// Why "LIBRARY"?  Well, clearly because
// the .DLL is just a LIBRARY of
// FUNCTIONS that you can CALL.

// ZLIB is really just a bunch of
// subroutines that you use to zip
// and unzip data.

// "DYNAMICALLY LINKED":  Because
// the actual code of ZLIB (that performs
// the zipping and unzipping operations),
// is going to REMAIN STORED inside of
// zlib.dll.

// Even though your program that you write
// will make calls to zlib's functions,
// THERE WILL BE NO _ACTUAL_ ZLIB CODE
// IN __YOUR__ FINAL EXECUTABLE.

// In other words, the actual ZIP /UNZIP
// code routines WILL NOT be packed into
// YOUR final executable that you build
// with your code when you use zlib.dll.

// Instead, your code will contain REFERENCES TO
// the actual executable code pieces inside
// of zlib.dll, and WINDOWS will resolve
// ("LINK") your application's calls with
// the .dll file's subroutines DYNAMICALLY
// (AT RUN TIME).

// Hence the term "dynamically linked library".
// Because the LINKING of the code happens
// DYNAMICALLY ("dynamically" just means
// "at run time", just like "dynamically allocated
// memory" is memory that you allocate at
// run time using malloc()).

// Its a little bit like the JVM,
// .NET and the idea of JITting.

///////////////////
// WHY USE A DLL?
// 
// WHY dynamically link?  WHY store code that my
// app needs to run OUTSIDE of my app's executable?

// The benefits of dynamically linking are many:
//
//   1.  A single .dll library file can be used
//       by any number of programs.

//   2.  (Directly follows from 1.)  If you update
//       the INTERNAL WORKINGS of a DLL file (for a bug fix
//       or something), you USUALLY will not have to
//       change ANYTHING about the apps that simply
//       USE and call functions that reside in that
//       .DLL file.

//       Updating the DLL is a little bit like updating
//       a website.  As long as the URL address and page names and
//       interfaces all stay the same, the site owner can
//       update and change the internal workings of the
//       web site (say, to prevent hacking) completely
//       invisibly to the website's users.

//   3.  Reduces final executable size and memory
//       footprint.  Windows itself uses a lot 
//       of DLL's internally.  When you call CreateWindowEx(),
//       that function call is resolved at RUN TIME,
//       __NOT__ at compile time.  The actual code
//       to create a window is in a DLL.  Your app
//       just calls it.

//       For example, say you have made a Warcraft 3-like
//       game.

//       You have written a ton of code that
//       is used to render the characters in your game.

//       TWO main applications need to use that same
//       drawing code:
//          1)  The game itself
//          2)  The Map editor

//       What is the main problem with COPYING the
//       same code over from the game itself
//       into the map editor?

//             A)  bloat.
//             B)  TWO PLACES to remember to update
//                 for bug fixes.
//       
//       INSTEAD OF REPEATING that same drawing code
//       into the TWO projects (BOTH war3.exe AND mapedit.exe),
//       you instead write a SINGLE DLL file and
//       have BOTH war3.exe and mapedit.exe LINK
//       to that same DLL file.

//       This way, if you update the drawing routines,
//       you only update them one place (the .dll).

//       Since the DLL code DOES NOT get
//       linked into all of the executables that use it,
//       you can make quick bug fixes to the DLL
//       file, and completely revamp its inner workings,
//       WITHOUT having to re-compile the applications
//       that are using the DLL.

//       However, keep in mind that if you
//       CHANGE the inputs or outputs of a dll, THEN,
//       then you will need to update and
//       re-compile the programs that use that dll.

// So at the end of the day, a .dll file 
// just contains a bunch of CODE.

// The difference comes in in HOW the
// Windows operating system manages
// that code.

///////////////////////////
// WHAT'S THIS FILE?
//
// This project shows you how to use zlib.
// Its a console project, because there's
// no need to create a window to demonstrate
// use of zlib.

// "words.txt" was generated from the 5 letter
// words listed @ http://www.math.toronto.edu/~jjchew/scrabble/lists/common-5.html

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#else
#endif

// the zlib.h header file contains
// function prototypes and a lot
// of information about zlib!
//#include "zlibdll/include/zlib.h"
#include "zlib.h"

// link the static lib
//#pragma comment (lib, "zlibdll/lib/zdll.lib" )


int main()
{
    srand(time(0));      // seed random number generator

    bool showOutput;     // make false if you don't want text output
    printf( "Show textual output?  [y/n]\n");
    if ( tolower(getchar()) == 'y' )
        showOutput = true;
    else
        showOutput = false;
    

    printf("*********************\n");
    printf("* zlib test file\n");
    printf("* Using version %s of zlib\n", zlibVersion() ) ;

    #pragma region _make some data to compress_
    const int NUM_WORDS = 8938;     // pre-counted constant

    char * randomWords[ NUM_WORDS ] = {
#include "words.txt"
    };

    const int NUM_WORDS_TO_USE = 80;

    // Fill dataOriginal with a random jumbling of
    // 80 * (5 letter words + 1 space)
    // (each word followed by a space).
    int sizeDataOriginal = 6 * NUM_WORDS_TO_USE + 1 ;
    printf("* Before compression:  your data is %d bytes\n", sizeDataOriginal );
    BYTE * dataOriginal = (BYTE*)malloc( sizeDataOriginal );
    
    for( int i = 0; i < 6 * NUM_WORDS_TO_USE; i += 6 )
    {
        int randomIndex = rand() % NUM_WORDS ;
        static char buf[6];
        strncpy( buf, randomWords[ randomIndex ], 5 );  // don't copy the NULL character.
        buf[5] = ' ';
        strncpy( (char*)(dataOriginal+i), buf, 6 );
    }

    dataOriginal[ sizeDataOriginal - 1 ] = NULL; // null terminator.
    // test it.
    printf("* \n* Here's the data we generated for you:\n\n--\n");
    if( showOutput )
    {
        for( int i = 0 ; i < sizeDataOriginal ; i++ )
        {
            putchar( dataOriginal[i] ); // coulda puts'd this
            // but wanted to be consistent.
        }
        printf("\n--\n\n");
    }
    else
        printf(" (suppressed)\n--\n\n");
    #pragma endregion

    #pragma region compress the data
    //////////////
    // compress it.
    // To compress some data, we'll use the compress()
    // function.

    // To use the compress function, we must
    // create a destination buffer to
    // hold the compressed data.

    // So how big should the compressed
    // data buffer be?
    
    // This may seem a bit weird at first,
    // but the array that is to hold the compressed
    // data must start out being AT LEAST 0.1% larger than
    // the original size of the data, + 12 extra bytes.
    
    // So, we'll just play it safe and alloated 1.1x
    // as much memory + 12 bytes (110% original + 12 bytes)

    ULONG sizeDataCompressed  = (sizeDataOriginal * 1.1) + 12;

    BYTE * dataCompressed = (BYTE*)malloc( sizeDataCompressed );

    // Now hold on, you ask.  WHY is the array
    // that's supposed to hold the COMPRESSED 
    // data ALREADY BIGGER than the original
    // data array?  This isn't compression!
    // This is meaningless expansion!
    
    // Well, you'll see that this extra space
    // in the compressed array is only TEMPORARY.
    // Just suffice it to say that zlib
    // "needs room to breathe".

    // When zlib performs compression, it will
    // need a bit of extra room to do its work.

    // When the compress() routine returns,
    // the compressedData array will have
    // been AUTOMATICALLY RESIZED by ZLIB
    // to being a smaller, compressed size.

    // We will also know the EXACT size of
    // that compressed data by looking at
    // the 'sizeDataCompressed' variable
    // AFTER the compress() routine runs.
    // That variable 'sizeCompressedData'
    // will updated by the compress() 
    // function when we call it!
    
    // Don't worry, the "compressed" data
    // will be smaller than the original
    // data was in the end!
    int z_result = compress(
        
        dataCompressed,         // destination buffer,
                                // must be at least
                                // (1.01X + 12) bytes as large
                                // as source.. we made it 1.1X + 12bytes

        &sizeDataCompressed,    // pointer to var containing
                                // the current size of the
                                // destination buffer.
                                // WHEN this function completes,
                                // this var will be updated to
                                // contain the NEW size of the
                                // compressed data in bytes.

        dataOriginal,           // source data for compression
        
        sizeDataOriginal ) ;    // size of source data in bytes

    switch( z_result )
    {
    case Z_OK:
        printf("***** SUCCESS! *****\n");
        break;

    case Z_MEM_ERROR:
        printf("out of memory\n");
        exit(1);    // quit.
        break;

    case Z_BUF_ERROR:
        printf("output buffer wasn't large enough!\n");
        exit(1);    // quit.
        break;
    }
     
    printf("*******************************\n");
    printf("* DATA COMPRESSION COMPLETE!! :\n");
    printf("*\n");
    printf("* Compressed size is %d bytes\n", sizeDataCompressed );
    printf("* This is what it looks like:\n\n--\n");

    // Now we want to print the compressed data out.
    // Can't just printf() it because 
    // the nulls will be all over the place, and there
    // isn't necessarily a null at the end.
    if( showOutput )
    {
        for( int i = 0; i < sizeDataCompressed; i++ )
        {
            putchar( dataCompressed[i] );
        }
        printf("\n--\n\n");
    }
    else
        printf(" (suppressed)\n--\n\n");
    #pragma endregion
    
    #pragma region save compressed data to disk
    //////////////////
    // Save that compressed data to disk.
    // Maybe its save game information or
    // something.
    printf("********************************\n");
    printf("* Saving compressed data to disk\n\n");

    ///////////////////////////////////////////////
    //////////////!!!!!!!!!!!!!!!!!!!!/////////////
    //////////////!!!IMPORTANT NOTE!!!/////////////
    // You see how I'm opening the file in "wb" mode,
    // NOT just "w" mode?????
    FILE * out = fopen( "savedData.dat", "wb" );
    // Well, "wb" means BINARY MODE for writing.
    // THIS IS EXTREMELY IMPORTANT.  IF YOU DON'T
    // USE "wb" TO WRITE YOUR FILES, AND YOU DON'T
    // USE "rb" TO READ YOUR FILES, YOU FILE
    // WILL BE VERY SLIGHTLY CORRUPTED,
    // WINDOWS PROMISES YOU THAT!!

    // One of the reasons for the corruption is
    // under Windows, if you write out a
    // NEWLINE (ASCII code 10, escape sequence "\n",
    // aka the "LINEFEED" (LF)) to the output stream, 
    // then Windows puts out a 13 FIRST, then a 10.

    // 13 is the ascii code for CARRIAGE RETURN (CR),
    // and 10 is ascii code for the Linefeed (LF).

    // Now that seems awfully stupid.  Why would Windows
    // output hex 0D 0A when I clearly asked it to
    // output just 0A?

    // The answer is that Windows uses TWO CHARACTERS
    // to designate the new line:  (CRLF), NOT just LF.

    // Unix uses just LF.  Macs use just CR.  (Windows is
    // the only weirdo that uses 2 characters for a newline).

    // SO, this is significant because everytime you write
    // the integer value 10 to the output stream, IF you're
    // NOT writing in binary mode, Windows thinks you're
    // trying to write text.  So NATURALLY, if you write
    // the integer value 10 out in one of the bytes, 
    // Windows recognizes this is a linefeed and
    // write out 13 10 instead.

    // This introduces extra data into your output
    // and is enough to significantly corrupt the result.

    if( out == NULL )
    {
        printf("Couldn't open output file for writing\n");
        exit(1);    //quit
    }
    fwrite( dataCompressed, sizeDataCompressed, 1, out );
    fclose( out );
    out = NULL;
    #pragma endregion

    #pragma region read in data from disk
    ///////////////
    // Next, we'll READ the compressed data
    // from the file, then DECOMPRESS it, to
    // prove that it'll be the same as
    // the original data.
    printf("********************************\n");
    printf("* Reading in data from save file\n");
    
    //////////////!!!!!!!!!!IMPORTANT:  note "rb"
    // NOT just "r".
    FILE * readFile = fopen("savedData.dat", "rb");
    if( readFile == NULL )
    {
        printf("Couldn't open input file for reading\n");
        exit(1);    //quit
    }

    // get size of file
    fseek( readFile, 0, SEEK_END );
    ULONG fileLength = ftell( readFile );
    rewind( readFile );

    // allocate enough mems to hold entire file
    // alternatively, we could "memory map" the          //HANDLE h = CreateFileMapping( 0, 0, 0, 0, 0, 0 );
    // file contents using the CreateFileMapping and     //MapViewOfFile( h, 0, 0, 0, 0 );
    // MapViewOfFile funcs.
    BYTE * dataReadInCompressed = (BYTE*)malloc( fileLength );

    // read in entire file
    fread( dataReadInCompressed, fileLength, 1, readFile );

    // close file
    fclose( readFile );
    readFile = NULL;

    printf("*\n* This is what I read from the saved file:\n"); 
    printf("\n--\n");
    if( showOutput )
    {
        for( int i = 0 ; i < fileLength ; i++ )
        {
            putchar( dataReadInCompressed[i] );
        }
        printf("\n--\n\n");
    }
    else
        printf(" (suppressed)\n--\n\n");
    #pragma endregion

    #pragma region decompress the read-in data
    ///////////////
    // Next, we'll decompress that
    // data we just read in from disk.

    // How large should we make the array
    // into which the UNZIPPED/UNCOMPRESSED
    // data will go?

    // WELL, there's the catch with ZLIB.
    // You never know how big compressed data
    // will blow out to be.  It can blow up
    // to being anywhere from 2 times as big,
    // or it can be (exactly the same size),
    // or it can be up to 10 times as big
    // or even bigger!
    
    // So, you can tell its a really bad idea
    // to try to GUESS the proper size that the
    // uncompressed data will end up being.

    // You're SUPPOSED TO HAVE SAVED THE INFORMATION
    // about the original size of the data at
    // the time you compress it.
    
    // There's a note on how to do that easily
    // at the bottom of this file, in the end notes.

    // FOR NOW, we're just going to 
    // use the dataSizeOriginal variable.
    printf("*******************************\n");
    printf("* Decompressing your data . . .\n");
    ULONG sizeDataUncompressed = sizeDataOriginal;
    BYTE * dataUncompressed = (BYTE*)malloc( sizeDataUncompressed );
    
    //////////////
    // now uncompress
    z_result = uncompress(
        
        dataUncompressed,       // destination for the uncompressed
                                // data.  This should be the size of
                                // the original data, which you should
                                // already know.

        &sizeDataUncompressed,  // length of destination (uncompressed)
                                // buffer

        dataReadInCompressed,   // source buffer - the compressed data

        sizeDataCompressed );   // length of compressed data in bytes

    switch( z_result )
    {
    case Z_OK:
        printf("***** SUCCESS! *****\n");
        break;

    case Z_MEM_ERROR:
        printf("out of memory\n");
        exit(1);    // quit.
        break;

    case Z_BUF_ERROR:
        printf("output buffer wasn't large enough!\n");
        exit(1);    // quit.
        break;
    }


    printf("************************\n");
    printf("* Uncompressed size is %d bytes\n", sizeDataUncompressed );
    printf("* Your UNCOMPRESSED data looks like this:\n");

    printf("\n--\n");
    if( showOutput )
    {
        for( int i = 0 ; i < sizeDataUncompressed ; i++ )
        {
            putchar( dataUncompressed[i] );
        }
        printf("\n--\n\n");
    }
    else
        printf(" (suppressed)\n--\n\n");
    #pragma endregion

    #pragma region compare decompressed data with original data
    if( memcmp( dataOriginal, dataUncompressed, sizeDataOriginal ) == 0 )
    {
        printf("* SEE?  It was EXACTLY the same.\n");
    }
    else
    {
        printf( "\n\n=====================================\n"
                "Oh. . . dear.  There is a problem.  The uncompressed data "
                "isn't exactly the same as the original data.  Your data "
                "may be corrupted.  WHOOPS!!\n"
                "Please make sure if that you are reading and writing "
                "any file i/o in BINARY MODE." );
    }
    #pragma endregion

    free( dataOriginal );
    free( dataCompressed );
    free( dataReadInCompressed );
    free( dataUncompressed );
    
}

/////////
// END NOTES:

// So in this tutorial, when I saved the
// data out to a file, I just used fwrite()
// and dumped the array of bytes with no
// information ABOUT what the file is
// whatsoever.

// in real life, that's probably not a good idea.
// You want to always output at the beginning
// of your compressed data AT LEAST the size
// the data will be when it becomes uncompressed.
// This is the only way you can know how big
// to make the "receiving array" for the uncompressed data.

// ZLIB has no "tell_me_the_size_of_this_thing_
// when_it_gets_uncompressed() function.

// You MUST keep that data in the file itself.

// So, you might create a structure like thus
// and like so:

/*

struct saveFile
{
    ULONG compressedSize;   // size of the data array, compressed
    ULONG uncompressedSize; // size when data gets uncompressed
    char what[16];          // what is this file?  may want to
                            // indicate what kind of data is saved here.

    // add whatever other info you need
    // here.

    BYTE * data;            // the actual compressed data

};

*/

// Then, just fwrite out the data,
// with a couple of fwrites().

// When you fread it, you fread the
// size fields first . . . you know
// what to do.

/* 
     ____   __   __      __   __  ___
    / _  \ /  / /  /    /  /  \ \/  /
   / _/ / /  / /  /    /  /    \   /
  / _/ \ /  / /  /__  /  /__   /  /
 /_____//__/ /______//______/ /__/

*/
#else
int main(int ac, char* av[]) {
} // main
#endif // ifndef LINUX

