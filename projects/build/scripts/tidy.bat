@echo off

set PATH=%PATH%;D:\cygwin\bin;
REM cd "D:\Program Files\UniversalIndentGUI_win32"
REM which perltidy

REM IF (%1)==() GOTO error
IF (%1)==() ( 
   call :indentDir "." "pl"
   GOTO ende
)
dir /b /ad %1 >nul 2>nul && GOTO indentDir
IF NOT EXIST %1 GOTO error
goto indentFile

:indentDir
set searchdir=%1

IF (%2)==() GOTO assignDefaultSuffix
set filesuffix=%2

GOTO run

:assignDefaultSuffix
::echo !!!!DEFAULT SUFFIX!!!
REM set filesuffix=*
set filesuffix=pl

:run
FOR /F "tokens=*" %%G IN ('DIR /B /S %searchdir%\*.%filesuffix%') DO (
echo Indenting file "%%G"
REM perl "D:/Program Files/UniversalIndentGUI_win32/indenters/perltidy" -pro="D:/Program Files/UniversalIndentGUI_win32/indenters/perltidy.cfg" "%%G" -o=indentoutput.tmp
perl "D:\cygwin\usr\local\bin\perltidy" -pro="D:/Program Files/UniversalIndentGUI_win32/indenters/perltidy.cfg" "%%G" -o=indentoutput.tmp
move /Y indentoutput.tmp "%%G"

)
GOTO ende

:indentFile
echo Indenting one file %1
REM perl "D:/Program Files/UniversalIndentGUI_win32/indenters/perltidy" -pro="D:/Program Files/UniversalIndentGUI_win32/indenters/perltidy.cfg" "%1" -o=indentoutput.tmp
perl "D:\cygwin\usr\local\bin\perltidy" -pro="D:/Program Files/UniversalIndentGUI_win32/indenters/perltidy.cfg" "%1" -o=indentoutput.tmp
move /Y indentoutput.tmp "%1"


GOTO ende

:error
echo .
echo ERROR: As parameter given directory or file does not exist!
echo Syntax is: tidy.bat dirname filesuffix
echo Syntax is: tidy.bat filename
echo Example: tidy.bat temp cpp
echo .


:ende
REM pause