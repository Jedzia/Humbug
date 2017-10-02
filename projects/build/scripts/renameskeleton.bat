@echo off
@REM Version=1.0.1.0
@REM Info=rename project recursive. renameskeleton.bat BasicCompiler TargetProjectName
set STD=%1
@set CURDIR=%CD%

@echo off
setlocal disableDelayedExpansion
for /f "delims=" %%F in ('dir /b /ad /s %STD%*') do (
  set "fname=%%~nxF"
  set "fpath=%%~dpF"
  setlocal enableDelayedExpansion
  
  echo ren "!fpath:%STD%=%2!!fname!" "!fname:%STD%=%2!"
  ren "!fpath:%STD%=%2!!fname!" "!fname:%STD%=%2!"
  endlocal
)

@echo off
setlocal disableDelayedExpansion
for /f "delims=" %%F in ('dir /b /s %STD%*') do (
  set "fname=%%~nxF"
  set "fpath=%%~dpF"
  setlocal enableDelayedExpansion
  echo ren "!fpath:%STD%=%2!!fname!" "!fname:%STD%=%2!"
  ren "!fpath:%STD%=%2!!fname!" "!fname:%STD%=%2!"
  endlocal
)

set UP_STD=%STD%
CALL :UpCase  UP_STD
set UP_NO1=%2
CALL :UpCase  UP_NO1



fnr.exe --cl --dir "%CURDIR%" --fileMask "*.*"  --excludeFileMask "*.dll, *.exe, *.zip, %CURDIR%\projects\build\scripts\renameskeleton.bat" --includeSubDirectories --caseSensitive --find "%STD%" --replace "%2"
fnr.exe --cl --dir "%CURDIR%" --fileMask "*.*"  --excludeFileMask "*.dll, *.exe, *.zip, %CURDIR%\projects\build\scripts\renameskeleton.bat" --includeSubDirectories --caseSensitive --find "%UP_STD%" --replace "%UP_NO1%"

GOTO:EOF

:UpCase
:: Subroutine to convert a variable VALUE to all UPPER CASE.
:: The argument for this subroutine is the variable NAME.
FOR %%i IN ("a=A" "b=B" "c=C" "d=D" "e=E" "f=F" "g=G" "h=H" "i=I" "j=J" "k=K" "l=L" "m=M" "n=N" "o=O" "p=P" "q=Q" "r=R" "s=S" "t=T" "u=U" "v=V" "w=W" "x=X" "y=Y" "z=Z") DO CALL SET "%2=%%%2:%%~i%%"
GOTO:EOF
