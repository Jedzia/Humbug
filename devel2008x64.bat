@ECHO off
title [Humbug] Visual Studio 2008 Command Prompt 

@set PLATFORM=x64
@set CURDIR=%CD%
@REM call explorer build
@REM call explorer projects\Humbug
@set PATH=%PATH%;%~dp0projects\build\PCLint\MSVC90;%~dp0projects\build\scripts

call "%DXSDK_DIR%\Utilities\Bin\dx_setenv.cmd"
call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x64
set PATH=D:\QT4-VS2008\bin;%PATH%;C:\Program Files\SVN\bin;D:\Program Files (x86)\ActivePerl_64_bit\Perl64\site\bin;D:\Program Files (x86)\ActivePerl_64_bit\Perl64\bin
REM set QTDIR=D:\QT4-VS2008
set SDLDIR=%~dp0build2010\DEPS\SDL-1.2.15
cd build2008x64
@REM call VStudio2005CMD

REM call %comspec% /k ""C:\Programme\Microsoft Visual Studio 8\VC\vcvarsall.bat"" x64

ECHO 
ECHO .
ECHO "C:\Program Files\CMake-2.8.5\bin\cmake-gui" ..\projects
ECHO .
ECHO msbuild Humbug.sln /v:n /p:Configuration=Debug /t:ALL_BUILD:Rebuild
ECHO msbuild Humbug.sln /v:n /p:Configuration=Debug /t:Humbug:Rebuild
ECHO "msbuild Humbug.sln /v:n /p:Configuration=Debug /t:Humbug && Humbug\src\Debug\Humbug.exe"
ECHO msbuild Humbug.sln /v:n /p:Configuration=Debug /t:HumbugConsole:Rebuild
ECHO msbuild Humbug.sln /t:Rebuild /v:diag /p:Configuration=Debug
ECHO msbuild Humbug.sln /v:d /p:Configuration=Debug
ECHO msbuild Humbug.sln /v:d /p:Configuration=Debug /t:Playground\throw_error
ECHO msbuild Humbug.sln /v:d /p:Configuration=Debug /t:Playground\throw_error:Rebuild
ECHO msbuild Humbug.sln /v:d /p:Configuration=Debug /t:Playground\csz_textdocument
ECHO Playground\Debug\csz_textdocument.exe
ECHO msbuild Humbug.sln /v:d /p:Configuration=Debug /t:Library\CppStructz
ECHO msbuild Humbug.sln /p:Configuration=Debug /t:UnitTests\boosttest-CppStructz_src_UnitTests-unit_test_example_01
ECHO msbuild Humbug.sln /p:Configuration=Debug /t:Playground\plugin\plugin
ECHO msbuild Humbug.sln /p:Configuration=Debug /t:Playground\templates_statemachine
ECHO msbuild Humbug.sln /v:n /p:Configuration=Debug /t:ALL_BUILD
ECHO "C:\Program Files\CMake-2.8.5\bin\ctest.exe" --force-new-ctest-process -C Debug
ECHO .

start /B "C:\Program Files\Notepad++\notepad++.exe" "%~dp0\projects\np.session"
REM start /B "devenv" "Humbug.sln"

call %comspec% /U /k ""%~dp0\startcmake.bat"" x64
