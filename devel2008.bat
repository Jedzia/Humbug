@ECHO off
title [HumbugGL] Visual Studio 2008 Command Prompt 
@set builddir=build2008

@set PLATFORM=Win32
@set CURDIR=%CD%
@REM call explorer build
@REM call explorer projects\HumbugGL
@set PATH=%PATH%;%~dp0projects\build\PCLint\MSVC90;%~dp0projects\build\scripts

call %~dp0%config\config.bat
call "%DXSDK_DIR%\Utilities\Bin\dx_setenv.cmd" x86
call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86
set PATH=D:\QT4-VS2008\bin;%PATH%;C:\Program Files\SVN\bin;D:\Program Files (x86)\ActivePerl_64_bit\Perl64\site\bin;D:\Program Files (x86)\ActivePerl_64_bit\Perl64\bin
REM set QTDIR=D:\QT4-VS2008
SET SDLDIR=%~dp0%builddir%\DEPS\SDL-%SDLVER%

IF NOT EXIST "%builddir%" mkdir %builddir%
cd %builddir%
@REM call VStudio2005CMD

REM call %comspec% /k ""C:\Programme\Microsoft Visual Studio 8\VC\vcvarsall.bat"" x86

type %~dp0%config\WelcomeShell.txt

start /B "C:\Program Files\Notepad++\notepad++.exe" "%~dp0\projects\np.session"
REM start /B "devenv" "HumbugGL.sln"

call %comspec% /U /k ""%~dp0\startcmake.bat"" x86
