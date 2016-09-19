@ECHO off
call %~dp0%config\config.bat
REM call "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall.bat" x86
start /B  %comspec% /k ""%CMAKE_DIR%\bin\cmake-gui"" ..\projects