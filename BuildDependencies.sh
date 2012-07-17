#!/bin/sh
#@echo off

progname=BuildDependencies

TMPDIR=DEPS
CURDIR=%CD%
SCRDIR=%~dp0
echo The LIB: ${LIB}
echo The TMPDIR: ${TMPDIR}
echo The CURDIR: ${CURDIR}
echo The SCRDIR: ${SCRDIR}
echo The PATH: ${PATH}

BuildRoot="/usr"
BuildPrefix="--prefix=${BuildRoot}"

ADD_CPPFLAGS="-I${BuildRoot}/include"
ADD_LDFLAGS="-L${BuildRoot}/lib"
ADDITIONAL="CPPFLAGS=${ADD_CPPFLAGS} LDFLAGS=${ADD_LDFLAGS}"


# Printing a long string crashes Solaris 7 /usr/bin/printf.
as_echo='\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\'
as_echo=$as_echo$as_echo$as_echo$as_echo$as_echo
as_echo=$as_echo$as_echo$as_echo$as_echo$as_echo$as_echo
# Prefer a ksh shell builtin over an external printf program on Solaris,
# but without wasting forks for bash or zsh.
if test -z "$BASH_VERSION$ZSH_VERSION" \
    && (test "X`print -r -- $as_echo`" = "X$as_echo") 2>/dev/null; then
  as_echo='print -r --'
  as_echo_n='print -rn --'
elif (test "X`printf %s $as_echo`" = "X$as_echo") 2>/dev/null; then
  as_echo='printf %s\n'
  as_echo_n='printf %s'
else
  if test "X`(/usr/ucb/echo -n -n $as_echo) 2>/dev/null`" = "X-n $as_echo"; then
    as_echo_body='eval /usr/ucb/echo -n "$1$as_nl"'
    as_echo_n='/usr/ucb/echo -n'
  else
    as_echo_body='eval expr "X$1" : "X\\(.*\\)"'
    as_echo_n_body='eval
      arg=$1;
      case $arg in #(
      *"$as_nl"*)
	expr "X$arg" : "X\\(.*\\)$as_nl";
	arg=`expr "X$arg" : ".*$as_nl\\(.*\\)"`;;
      esac;
      expr "X$arg" : "X\\(.*\\)" | tr -d "$as_nl"
    '
    export as_echo_n_body
    as_echo_n='sh -c $as_echo_n_body as_echo'
  fi
  export as_echo_body
  as_echo='sh -c $as_echo_body as_echo'
fi

ECHO=${as_echo-'printf %s\n'}
ECHOD=${as_echo-'printf %s\n'}


func_mktempdir ()
{

	#$ECHO "$progname: ${opt_mode+$opt_mode: }$*"
	$ECHO "$progname: creating directory $TMPDIR"

      if test ! -d "$TMPDIR"; then
        # Failing that, at least try and use $RANDOM to avoid a race
        #my_tmpdir="${my_template}-${RANDOM-0}$$"
		mkdir ${TMPDIR}
      fi
}

func_fetchdependencyonly ()
{

	$ECHO "$progname: getting $*"
	pushd $TMPDIR

#      if test ! -f "$2.fetched"; then
	  	 wget -c "$1$2"
#		 echo > "$2.fetched"
#	  fi 

	popd
}

# workaround, google code certificate
func_fetchdependencyWA ()
{

	$ECHO "$progname: getting $*"
	pushd $TMPDIR

      if test ! -f "$2.extracted"; then
	  	 wget --no-check-certificate -c "$1$2"
		 tar xfz "$2"
		 echo > "$2.extracted"
	  fi 

	popd
}

func_fetchdependency ()
{

	$ECHO "$progname: getting $*"
	pushd $TMPDIR

      if test ! -f "$2.extracted"; then
	  	 wget -c "$1$2"
		 tar xfz "$2"
		 if [ $? -ne 0 ]; then  echo "!!!error";	exit 1;	fi
		 echo > "$2.extracted"
	  fi 

	popd
}

func_confdependency ()
{

	$ECHO ""
	#$ECHO "------------------------"
	$ECHO "$progname: Configuring $*"
	pushd $TMPDIR/$1

      if test ! -f "$1.configured"; then
	  	 ./configure $2 $3 $4 $5 $6 $7 $8 $9
		 if [ $? -ne 0 ]; then  echo "!!!error";	exit 1;	fi
		 echo > "$1.configured"
	  fi 
	popd
}

func_makedependency ()
{

	$ECHO "$progname: Building $*"
	pushd $TMPDIR/$1

      if test ! -f "$1.built"; then
		 make
		 if [ $? -ne 0 ]; then  echo "!!!error";	exit 1;	fi
		 echo > "$1.built"
	  fi 
	popd
}

func_makeinstall ()
{

	$ECHO "$progname: Installing $*"
	pushd $TMPDIR/$1

      if test ! -f "$1.installed"; then
		 make install
		 if [ $? -ne 0 ]; then  echo "!!!error";	exit 1;	fi
		 echo > "$1.installed"
	  fi 
	popd
}

func_build_project ()
{

	$ECHO "$progname: ========= Building $1 ========="
	_cur_prj=$1
	if test ! -f "$TMPDIR/${1}.done"; then
		func_fetchdependency $2 $3
		func_confdependency $1 ${BuildPrefix} $4 $5 $6 $7
		func_makedependency $1
		func_makeinstall $1
		echo > "$TMPDIR/${1}.done"
	else
		$ECHO "$progname: $1 already built."
	fi 
}


func_do_sdlimage_pre ()
{

	$ECHO "$progname: 		++++ SDL-Image dependencies ++++"
#	if test ! -f "$TMPDIR/sdl_image_deps.downloaded"; then
#		func_fetchdependencyonly http://sourceforge.net/projects/mingwrep/files/libjpeg/6b-1/libjpeg-6b-1.zip/download
#		func_fetchdependencyonly http://sourceforge.net/projects/mingwrep/files/libpng-bin/1.0.6-20000724/libpng-1.0.6-20000724.zip/download
#		func_fetchdependencyonly http://sourceforge.net/projects/mingwrep/files/libpng-devel/1.0.6-20000724/libpng-devel-1.0.6-20000724.zip/download
#		func_fetchdependencyonly http://sourceforge.net/projects/mingwrep/files/libtiff-bin/3.4-1/libtiff-3.4-1.zip/download
#		func_fetchdependencyonly http://sourceforge.net/projects/mingwrep/files/libtiff-devel/3.4-1/libtiff-devel-3.4-1.zip/download
#		func_fetchdependencyWA https://webp.googlecode.com/files/ libwebp-0.1.3.tar.gz
#		echo > "$TMPDIR/sdl_image_deps.downloaded"
#	fi

	#pushd $TMPDIR
	#unlzma libjpeg-6b-1.zip
	#popd

	#http://sourceforge.net/projects/libpng/files/libpng15/1.5.12/libpng-1.5.12.tar.gz/download
	SDLImage_Deps_FOUND=1

	# *** LIBPNG ***
	SDLImage_LIBPNG_FOUND=0
	func_fetchdependency http://sourceforge.net/projects/libpng/files/libpng15/1.5.12/ libpng-1.5.12.tar.gz
	func_confdependency libpng-1.5.12 ${BuildPrefix} 
	func_makedependency libpng-1.5.12
	func_makeinstall libpng-1.5.12

	if test -f /include/png.h; then
		SDLImage_LIBPNG_FOUND=1
	else
		SDLImage_Deps_FOUND=0
		SDLImage_NEEDED="${SDLImage_NEEDED}, libpng-1.5.12"
	fi 

	if test $SDLImage_LIBPNG_FOUND -eq 0; then
		curd=`pwd`
		$ECHO "$progname: 		"
		$ECHO "$progname: 		Got problems installing libpng-1.5.12."
		$ECHO "$progname: 		Please install manually."
		exit 1
	fi


	# *** LIBJPEG ***
	SDLImage_LIBJPEG_FOUND=0
	func_fetchdependency http://sourceforge.net/projects/libjpeg/files/libjpeg/6b/ jpegsrc.v6b.tar.gz
	func_confdependency jpeg-6b ${BuildPrefix} 
	func_makedependency jpeg-6b
	func_makeinstall jpeg-6b

	if test -f /usr/include/png.h; then
		SDLImage_LIBJPEG_FOUND=1
	else
		SDLImage_Deps_FOUND=0
		SDLImage_NEEDED="${SDLImage_NEEDED}, jpeg-6b"
	fi 

	if test $SDLImage_LIBJPEG_FOUND -eq 0; then
		curd=`pwd`
		$ECHO "$progname: 		"
		$ECHO "$progname: 		Got problems installing jpegsrc.v6b."
		$ECHO "$progname: 		Please install manually."
		exit 1
	fi

	# *** LIBTIFF ***
	SDLImage_LIBTIFF_FOUND=0
	func_fetchdependency ftp://ftp.remotesensing.org/pub/libtiff/ tiff-3.9.6.tar.gz
	func_confdependency tiff-3.9.6 ${BuildPrefix} 
	func_makedependency tiff-3.9.6
	func_makeinstall tiff-3.9.6

	if test -f /usr/include/tiff.h; then
		SDLImage_LIBTIFF_FOUND=1
	else
		SDLImage_Deps_FOUND=0
		SDLImage_NEEDED="${SDLImage_NEEDED}, tiff-3.9.6"
	fi 

	if test $SDLImage_LIBTIFF_FOUND -eq 0; then
		curd=`pwd`
		$ECHO "$progname: 		"
		$ECHO "$progname: 		Got problems installing tiff-3.9.6."
		$ECHO "$progname: 		Please install manually."
		exit 1
	fi


	
	if test $SDLImage_Deps_FOUND -eq 0; then
		curd=`pwd`
		$ECHO "$progname: 		"
		$ECHO "$progname: 		Please manually install the downloaded libraries."
		$ECHO "$progname: 		$SDLImage_NEEDED"
		$ECHO "$progname: 		Zip location is $curd"
		exit 1
	fi
	
	#$ ./configure --enable-experimental  --prefix=/usr --with-pngincludedir=/usr/include --with-pnglibdir=/usr/lib --with-jpegincludedir=/usr/include --with-jpeglibdir=/usr/lib
	func_confdependency libwebp-0.1.3 ${BuildPrefix} --enable-experimental --with-pngincludedir=/usr/include --with-pnglibdir=/usr/lib --with-jpegincludedir=/usr/include --with-jpeglibdir=/usr/lib
	#func_confdependency libwebp-0.1.3 --prefix= --enable-experimental 
	#SUBDIRS = src examples man
	#SUBDIRS = src man
	func_makedependency libwebp-0.1.3
	func_makeinstall libwebp-0.1.3
	
	SDLImage_LIBWEBP_FOUND=0
	if test -f /usr/include/webp/decode_vp8.h; then
		SDLImage_LIBWEBP_FOUND=1
	else
		SDLImage_Deps_FOUND=0
		SDLImage_NEEDED="${SDLImage_NEEDED}, WEBP"
	fi 

	if test $SDLImage_LIBWEBP_FOUND -eq 0; then
		curd=`pwd`
		$ECHO "$progname: 		"
		$ECHO "$progname: 		Got problems installing libwebp-0.1.3."
		$ECHO "$progname: 		Please install manually."
		exit 1
	fi
	
	
}

func_do_sdlttf_pre ()
{

	$ECHO "$progname: 		++++ SDL-TTF dependencies ++++"

	SDLTTF_Deps_FOUND=1

	if test -f /usr/include/freetype2/freetype/freetype.h; then
		SDLTTF_LIBFreeType2_FOUND=1
	else
		SDLTTF_Deps_FOUND=0
	fi 

	if test $SDLTTF_Deps_FOUND -eq 0; then
		if test ! -f "$TMPDIR/sdl_ttf_deps.downloaded"; then
			func_fetchdependency http://sourceforge.net/projects/freetype/files/freetype2/2.4.10/ freetype-2.4.10.tar.gz
			echo > "$TMPDIR/sdl_ttf_deps.downloaded"
		fi
		func_confdependency freetype-2.4.10 ${BuildPrefix}
		func_makedependency freetype-2.4.10
		func_makeinstall freetype-2.4.10
		cp $TMPDIR/freetype-2.4.10/devel/ft2build.h  $TMPDIR/$1
		cp $TMPDIR/freetype-2.4.10/devel/ftoption.h  $TMPDIR/$1
		SDLTTF_Deps_FOUND=1
	fi	

	if test -f /usr/include/freetype2/freetype/freetype.h; then
		SDLTTF_LIBFreeType2_FOUND=1
	else
		SDLTTF_Deps_FOUND=0
		SDLTTF_NEEDED="${SDLTTF_NEEDED}, FreeType2"
	fi 
	
	if test $SDLTTF_Deps_FOUND -eq 0; then
		curd=`pwd`
		$ECHO "$progname: 		"
		$ECHO "$progname: 		Please manually install the downloaded libraries."
		$ECHO "$progname: 		$SDLTTF_NEEDED"
		$ECHO "$progname: 		Zip location is $curd"
		exit 1
	fi
}



#===================== Main ==================

func_mktempdir

# **** SDL Library ****
func_build_project SDL-1.2.15 http://www.libsdl.org/release/ SDL-1.2.15.tar.gz

# **** SDL_image Library ****
if test $MSYSTEM == "MINGW32"; then
	$ECHO "We are under MSYSTEM."
	func_do_sdlimage_pre
else
	$ECHO "Not MSYSTEM."
fi 
func_build_project SDL_image-1.2.12 http://www.libsdl.org/projects/SDL_image/release/ SDL_image-1.2.12.tar.gz ${ADDITIONAL}

# **** SDL_net Library ****
func_build_project SDL_net-1.2.8 http://www.libsdl.org/projects/SDL_net/release/ SDL_net-1.2.8.tar.gz

# **** SDL_mixer Library ****
#if test $MSYSTEM == "MINGW32"; then
#	func_do_sdlmixer_pre
#fi 
func_build_project SDL_mixer-1.2.12 http://www.libsdl.org/projects/SDL_mixer/release/ SDL_mixer-1.2.12.tar.gz

# **** SDL_ttf Library ****
if test $MSYSTEM == "MINGW32"; then
	func_do_sdlttf_pre SDL_ttf-2.0.11
fi 
func_build_project SDL_ttf-2.0.11 http://www.libsdl.org/projects/SDL_ttf/release/ SDL_ttf-2.0.11.tar.gz

# **** SDL_gfx Library ****
func_build_project SDL_gfx-2.0.23 http://www.ferzkopp.net/Software/SDL_gfx-2.0/ SDL_gfx-2.0.23.tar.gz


#:oglconsole
#call fetchdependency http://downloads.sourceforge.net/project/oglconsole/oglconsole/0.2/ oglconsole-0.2.tar.gz
#if %ERRORLEVEL% NEQ 0 goto error

#:SDL_gfx
#call fetchdependency http://www.ferzkopp.net/Software/SDL_gfx-2.0/ SDL_gfx-2.0.23.tar.gz
#if %ERRORLEVEL% NEQ 0 goto error
#REM call patchdependency unzip SDL_gfx-2.0.23 "%SCRDIR%\Dependencies\SDL_gfx-2.0.23-VisualC.zip"
#REM if %ERRORLEVEL% NEQ 0 goto error
#REM call builddependency SDL_gfx-2.0.23/VisualC SDL_gfx.sln SDL_gfx SDL-1.2.15\VisualC\SDL
#set PINCLUDE=%INCLUDE%;..\SDL-1.2.15\include;..\
#call builddependency SDL_gfx-2.0.23 SDL_gfx_VS2008.sln SDL_gfx SDL-1.2.15\VisualC\SDL
#REM copy %TMPDIR%\SDL_gfx-2.0.23\Release\SDL_gfx.lib %TMPDIR%\SDL_gfx-2.0.23\Test\
#REM del %TMPDIR%\SDL_gfx-2.0.23\Test\Debug
#REM call builddependency SDL_gfx-2.0.23 SDL_gfx_VS2008.sln ALL SDL-1.2.15\VisualC\SDL
#REM if %ERRORLEVEL% NEQ 0 goto error



#goto ende
#:error
#echo .
#echo ERROR: Got some serious error!
#echo .


#:ende


