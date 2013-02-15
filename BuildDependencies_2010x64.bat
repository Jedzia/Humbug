@echo off

@set TMPDIR=DEPS
@set CURDIR=%CD%
@set SCRDIR=%~dp0
REM echo The LIB: %LIB%

REM set PINCLUDE=$(DXSDK_DIR)Include;$(VCInstallDir)include;$(WindowsSdkDir)\include;$(FrameworkSDKDir)include;%INCLUDE%
set PINCLUDE=%INCLUDE%;%DXSDK_DIR%Include;..\..\SDL-1.2.15\include
REM set PLIB=$(DXSDK_DIR)Lib\x64;$(VCInstallDir)lib;$(WindowsSdkDir)\lib;$(FrameworkSDKDir)lib;$(VSInstallDir)lib;%LIB%
set PLIB=%LIB%;%DXSDK_DIR%Lib\x64;
REM goto SDL_gfx
 
call fetchdependency http://www.libsdl.org/release/ SDL-1.2.15.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL-1.2.15/VisualC SDL_2010.sln SDLmain
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL-1.2.15/VisualC SDL_2010.sln SDL
if %ERRORLEVEL% NEQ 0 goto error

call fetchdependency http://www.libsdl.org/projects/SDL_image/release/ SDL_image-1.2.12.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL_image-1.2.12/VisualC SDL_image.sln SDL_image SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error

call fetchdependency http://www.libsdl.org/projects/SDL_net/release/ SDL_net-1.2.8.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL_net-1.2.8/VisualC SDL_net_VS2008.sln SDL_net SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error

:SDL_mixer
REM call fetchzdependency http://www.libsdl.org/projects/SDL_mixer/release/ SDL_mixer-1.2.12.tar.gz 
call fetchzdependency http://www.libsdl.org/projects/SDL_mixer/release/ SDL_mixer-1.2.12.zip
if %ERRORLEVEL% NEQ 0 goto error
set PINCLUDE=%INCLUDE%;..\..\SDL-1.2.15\include;..\..\..\SDL-1.2.15\include
call builddependency SDL_mixer-1.2.12/VisualC SDL_mixer.sln SDL_mixer SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error

:SDL_ttf
call fetchdependency http://www.libsdl.org/projects/SDL_ttf/release/ SDL_ttf-2.0.11.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL_ttf-2.0.11/VisualC SDL_ttf.sln SDL_ttf SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error
REM set PINCLUDE=%INCLUDE%;..\..\SDL-1.2.15\include;..\..\..\SDL-1.2.15\include
REM call builddependency SDL_ttf-2.0.11/VisualC SDL_ttf.sln showfont SDL-1.2.15\VisualC\SDL
REM if %ERRORLEVEL% NEQ 0 goto error

:oglconsole
call fetchdependency http://downloads.sourceforge.net/project/oglconsole/oglconsole/0.2/ oglconsole-0.2.tar.gz
if %ERRORLEVEL% NEQ 0 goto error

:SDL_gfx
call fetchdependency http://www.ferzkopp.net/Software/SDL_gfx-2.0/ SDL_gfx-2.0.23.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
REM call patchdependency unzip SDL_gfx-2.0.23 "%SCRDIR%\Dependencies\SDL_gfx-2.0.23-VisualC.zip"
REM if %ERRORLEVEL% NEQ 0 goto error
REM call builddependency SDL_gfx-2.0.23/VisualC SDL_gfx.sln SDL_gfx SDL-1.2.15\VisualC\SDL
set PINCLUDE=%INCLUDE%;..\SDL-1.2.15\include;..\
call builddependency SDL_gfx-2.0.23 SDL_gfx_VS2008.sln SDL_gfx SDL-1.2.15\VisualC\SDL
REM copy %TMPDIR%\SDL_gfx-2.0.23\Release\SDL_gfx.lib %TMPDIR%\SDL_gfx-2.0.23\Test\
REM del %TMPDIR%\SDL_gfx-2.0.23\Test\Debug
REM call builddependency SDL_gfx-2.0.23 SDL_gfx_VS2008.sln ALL SDL-1.2.15\VisualC\SDL
REM if %ERRORLEVEL% NEQ 0 goto error



goto ende
:error
echo .
echo ERROR: Got some serious error!
echo .


:ende
