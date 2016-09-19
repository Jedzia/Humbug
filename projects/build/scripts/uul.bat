@echo off
@set CFGDIR=%~dp0../../../config
@set CURDIR=%CD%

REM dir %CFGDIR%
REM echo %CFGDIR%
REM echo %CD%

IF (%1)==() GOTO error
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
set filesuffix=*

:run
FOR /F "tokens=*" %%G IN ('DIR /B /S %searchdir%\*.%filesuffix%') DO (
echo Indenting file "%%G"
"%~dp0indenters/uncrustify.exe" -f "%%G" -c "%CFGDIR%/uncrustify.cfg" -o indentoutput.tmp
IF %ERRORLEVEL% NEQ 0 GOTO error
move /Y indentoutput.tmp "%%G"

)
GOTO ende

:indentFile
echo Indenting one file %1
REM see http://stackoverflow.com/questions/18981106/is-it-possible-to-validate-a-file-extension-using-a-bat-file
for /f "delims=" %%a  in ("%1") do set "Extension=%%~xa"
if /i "%Extension%"==".cpp" goto indentFileCPP
"%~dp0indenters/uncrustify.exe" -f "%1" -c "%CFGDIR%/uncrustify.cfg" -o indentoutput.tmp
IF %ERRORLEVEL% NEQ 0 GOTO error
GOTO indentFileCPPende
:indentFileCPP
"%~dp0indenters/uncrustify.exe" -f "%1" -c "%CFGDIR%/uncrustify-cpp.cfg" -o indentoutput.tmp
IF %ERRORLEVEL% NEQ 0 GOTO error

:indentFileCPPende
move /Y indentoutput.tmp "%1"


GOTO ende

:error
echo .
echo ERROR: As parameter given directory or file does not exist!
echo Syntax is: uncrusty.bat dirname filesuffix
echo Syntax is: uncrusty.bat filename
echo Example: uncrusty.bat temp cpp
echo .

:ende
