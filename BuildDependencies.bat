@echo off
REM echo The LIB: %LIB%
REM goto ende

REM set PINCLUDE=$(DXSDK_DIR)Include;$(VCInstallDir)include;$(WindowsSdkDir)\include;$(FrameworkSDKDir)include;%INCLUDE%
set PINCLUDE=%INCLUDE%;..\..\SDL-1.2.15\include
REM set PLIB=$(DXSDK_DIR)Lib\x86;$(VCInstallDir)lib;$(WindowsSdkDir)\lib;$(FrameworkSDKDir)lib;$(VSInstallDir)lib;%LIB%
set PLIB=%LIB%
 
call fetchdependency http://www.libsdl.org/release/ SDL-1.2.15.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL-1.2.15/VisualC SDL.sln SDL
if %ERRORLEVEL% NEQ 0 goto error


call fetchdependency http://www.libsdl.org/projects/SDL_image/release/ SDL_image-1.2.12.tar.gz
if %ERRORLEVEL% NEQ 0 goto error
call builddependency SDL_image-1.2.12/VisualC SDL_image.sln SDL_image SDL-1.2.15\VisualC\SDL
if %ERRORLEVEL% NEQ 0 goto error

goto ende
:error
echo .
echo ERROR: Got some serious error!
echo .


:ende
