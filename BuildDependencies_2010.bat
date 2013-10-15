@echo off

@set TMPDIR=DEPS
@set CURDIR=%CD%
@set SCRDIR=%~dp0
REM echo The LIB: %LIB%

REM set PINCLUDE=$(DXSDK_DIR)Include;$(VCInstallDir)include;$(WindowsSdkDir)\include;$(FrameworkSDKDir)include;%INCLUDE%
set PINCLUDE=%INCLUDE%;%DXSDK_DIR%Include;..\..\SDL-1.2.15\include
REM set PLIB=$(DXSDK_DIR)Lib\x86;$(VCInstallDir)lib;$(WindowsSdkDir)\lib;$(FrameworkSDKDir)lib;$(VSInstallDir)lib;%LIB%
set PLIB=%LIB%;%DXSDK_DIR%Lib\x86;
REM goto SDL_gfx
 
IF "%ZLIBVER%"=="" SET ZLIBVER=1.2.8
REM call fetchdependency http://sourceforge.net/projects/libpng/files/zlib/1.2.5/  zlib-1.2.5.tar.gz
call fetchdependency http://zlib.net/ zlib-%ZLIBVER%.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call patchdependency unzip DEPS\zlib-1.2.8\contrib\vstudio "%SCRDIR%\Dependencies\zlibvc-1.2.8-ZLIB_WINAPI-fix.zip"
if %ERRORLEVEL% NEQ 0 goto error
if "%PLATFORM%" == "x64" (
	pushd "%TMPDIR%\zlib-%ZLIBVER%/contrib/masmx64"
	call bld_ml64.bat
	popd
) else (
	pushd "%TMPDIR%\zlib-%ZLIBVER%/contrib/masmx86"
	call bld_ml32.bat
	popd
)
if %ERRORLEVEL% NEQ 0 goto error
call builddependency zlib-%ZLIBVER%/contrib/vstudio/vc10 zlibvc.sln zlibvc /p:\"OUT=$(OutDir)\zlib1.dll\"
REM call builddependency zlib-%ZLIBVER%/contrib/vstudio/vc10 zlibvc.sln zlibstat
REM call builddependency zlib-%ZLIBVER%/contrib/vstudio/vc10 zlibvc.sln ALL
if %ERRORLEVEL% NEQ 0 goto error
REM goto ende

:SDL 
call fetchdependency http://www.libsdl.org/release/ SDL-1.2.15.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call patchdependency unzip DEPS "%SCRDIR%\Dependencies\SDL-1.2.15-build2010x64"
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL-1.2.15/VisualC SDL_2010.sln SDLmain
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL-1.2.15/VisualC SDL_2010.sln SDL
if %ERRORLEVEL% NEQ 0 goto error

:SDL_image 
call fetchdependency http://www.libsdl.org/projects/SDL_image/release/ SDL_image-1.2.12.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call patchdependency unzip DEPS\SDL_image-1.2.12\VisualC "%SCRDIR%\Dependencies\SDL_image-1.2.12-VS2010fix.zip"
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL_image-1.2.12/VisualC SDL_image.sln SDL_image SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error

:SDL_net 
call fetchdependency http://www.libsdl.org/projects/SDL_net/release/ SDL_net-1.2.8.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call patchdependency unzip DEPS\SDL_net-1.2.8\VisualC "%SCRDIR%\Dependencies\SDL_net-1.2.8-VS2010fix.zip"
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL_net-1.2.8/VisualC SDL_net_VS2010.sln SDL_net SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error

:SDL_mixer 
call fetchdependency http://www.libsdl.org/projects/SDL_mixer/release/ SDL_mixer-1.2.12.zip
if %ERRORLEVEL% NEQ 0 goto error
call patchdependency unzip DEPS\SDL_mixer-1.2.12 "%SCRDIR%\Dependencies\SDL_mixer-1.2.12-VS2010fix.zip"
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL_mixer-1.2.12/VisualC SDL_mixer_2010.sln SDL_mixer SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error

:SDL_ttf 
call fetchdependency http://www.libsdl.org/projects/SDL_ttf/release/ SDL_ttf-2.0.11.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call patchdependency unzip DEPS\SDL_ttf-2.0.11 "%SCRDIR%\Dependencies\SDL_ttf-2.0.11-VS2010fix"
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL_ttf-2.0.11/VisualC SDL_ttf_2010.sln SDL_ttf SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error
REM set PINCLUDE=%INCLUDE%;..\..\SDL-1.2.15\include;..\..\..\SDL-1.2.15\include
REM call builddependency SDL_ttf-2.0.11/VisualC SDL_ttf_2010.sln showfont SDL-1.2.15\VisualC\SDL
REM if %ERRORLEVEL% NEQ 0 goto error

:oglconsole
call fetchdependency http://downloads.sourceforge.net/project/oglconsole/oglconsole/0.2/ oglconsole-0.2.tar.gz
if %ERRORLEVEL% NEQ 0 goto error

if "%PLATFORM%" == "Win32" goto SDL_gfx
echo OUCH: SDL_gfx is not available as x64 build!
goto ende
:SDL_gfx 
call fetchdependency http://www.ferzkopp.net/Software/SDL_gfx-2.0/ SDL_gfx-2.0.23.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call patchdependency unzip DEPS\SDL_gfx-2.0.23 "%SCRDIR%\Dependencies\SDL_gfx-2.0.23-VS2010fix"
if %ERRORLEVEL% NEQ 0 goto error
set PINCLUDE=%INCLUDE%;..\SDL-1.2.15\include;..\
call builddependency SDL_gfx-2.0.23 SDL_gfx.sln SDL_gfx SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error



goto ende
:error
echo .
echo ERROR: Got some serious error!
echo .


:ende
