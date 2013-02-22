@echo off

pushd "%TMPDIR%\%1"
set BTMPLIB=%LIB%
set BTMPINCLUDE=%INCLUDE%
if "%PLATFORM%" == "x64" (
	set PlatBUILD=;Platform=x64
) else (
	set PlatBUILD=;Platform=Win32
)

IF EXIST "%2-%3.finished" GOTO ende

@REM msbuild /t:Rebuild /p:Configuration=Release %2 
@REM msbuild /p:Configuration=Debug %2 /property:VCBuildOverride=AdditionalIncludeDirectories=..\..\SDL-1.2.15\include
set INCLUDE=%PINCLUDE%
set LIB=%PLIB%;..\..\%4\Debug;..\%4\Debug
if "%3" == "ALL" (
	msbuild /p:Configuration=Debug%PlatBUILD% /p:"VCBuildAdditionalOptions= /useenv" %2
) else (
	msbuild /p:Configuration=Debug%PlatBUILD% /p:"VCBuildAdditionalOptions= /useenv" /t:%3 %2 %4
)
if %ERRORLEVEL% NEQ 0 goto error

set LIB=%PLIB%;..\..\%4\Release;..\%4\Release
if "%3" == "ALL" (
	msbuild /p:Configuration=Release%PlatBUILD% /p:"VCBuildAdditionalOptions= /useenv" %2
) else (
	msbuild /p:Configuration=Release%PlatBUILD% /p:"VCBuildAdditionalOptions= /useenv" /t:%3 %2 %4
)
if %ERRORLEVEL% NEQ 0 goto error

echo "ready" > "%2-%3.finished"

goto ende
:error
echo ERROR: Cannot build %3 target of %2.

:ende

set LIB=%BTMPLIB%
set INCLUDE=%BTMPINCLUDE%
popd