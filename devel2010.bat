@ECHO off
title [Humbug] Visual Studio 2010 Command Prompt 
@set builddir=build2010

@set PLATFORM=Win32
@set CURDIR=%CD%
@REM call explorer build2010
@REM call explorer projects\Humbug
@set PATH=%PATH%;%~dp0projects\build\PCLint\MSVC90;%~dp0projects\build\scripts

call %~dp0%config\config.bat
call "%DXSDK_DIR%\Utilities\Bin\dx_setenv.cmd" x86
cd "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\"
call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" x86
set PATH=E:\Devel\CPP\Libs\QT4\bin;D:\Program Files (x86)\ActivePerl_64_bit\Perl64\site\bin;D:\Program Files (x86)\ActivePerl_64_bit\Perl64\bin;%PATH%;C:\Program Files\SVN\bin;
REM set QTDIR=E:\Devel\CPP\Libs\QT4
SET SDLDIR=%~dp0%builddir%\DEPS\SDL-%SDLVER%

IF NOT EXIST "%builddir%" mkdir %builddir%
cd %builddir%
@REM call VStudio2005CMD

@REM irgendwas mit popd oder pushd
@REM call VStudio2005CMD
@REM $(FULL_CURRENT_PATH)
@REM %comspec% /k ""$(FULL_CURRENT_PATH)""

REM call %comspec% /k ""C:\Programme\Microsoft Visual Studio 8\VC\vcvarsall.bat"" x86

type %~dp0%config\WelcomeShell.txt

start /B "C:\Program Files\Notepad++\notepad++.exe" "%~dp0\projects\np.session"
REM start /B "devenv" "Humbug.sln"

call %comspec% /U /k ""%~dp0\startcmake.bat"" x86
