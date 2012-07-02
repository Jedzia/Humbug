@ECHO off
title [Humbug] Visual Studio 2008 Command Prompt 
@set CURDIR=%CD%
@REM call explorer build
@REM call explorer projects\Humbug
@set PATH=%PATH%;%~dp0projects\build\PCLint\MSVC90;%~dp0projects\build\scripts

call "C:\Program Files\Microsoft DirectX SDK (June 2010)\Utilities\Bin\dx_setenv.cmd"
call "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86
set PATH=D:\QT4-VS2008\bin;%PATH%;C:\Program Files\SVN\bin;C:\ActivePerl\site\bin;C:\ActivePerl\bin
set QTDIR=D:\QT4-VS2008
cd build
@REM call VStudio2005CMD

REM call %comspec% /k ""C:\Programme\Microsoft Visual Studio 8\VC\vcvarsall.bat"" x86

ECHO 
ECHO .
ECHO "C:\Program Files\CMake-2.8.5\bin\cmake-gui" ..\projects
ECHO .
ECHO msbuild Humbug.sln /v:n /p:Configuration=Debug /t:ALL_BUILD:Rebuild
ECHO msbuild Humbug.sln /v:n /p:Configuration=Debug /t:Humbug:Rebuild
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

call %comspec% /U /k ""%~dp0\startcmake.bat"" x86
