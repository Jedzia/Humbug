setlocal ENABLEDELAYEDEXPANSION
set t=%2
set ext=!t:~-3!
echo %ext%

mkdir %TMPDIR%
pushd %TMPDIR%

IF EXIST "%2.loaded" GOTO ende
wget -c "%1%2"
if %ERRORLEVEL% NEQ 0 goto error

rem tar xfz %2
if "%ext%" == "zip" (
	unzip -qq -n %2 
	REM # Todo: unzip does not spit out an errorlevel.
	if %ERRORLEVEL% NEQ 0 goto error
) else (
	TarTool %2
	if %ERRORLEVEL% NEQ 0 goto error
)


echo "ready" > "%2.loaded"
goto ende
:error
echo ERROR: Cannot fetch %2 from %1.
:ende
popd