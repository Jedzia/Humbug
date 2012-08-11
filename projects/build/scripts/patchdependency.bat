@set PACURDIR=%CD%
REM mkdir %TMPDIR%
REM pushd %TMPDIR%/%2

if "%1" == "unzip" (
	unzip -o -qq "%3" -dtmp/%2
)

REM popd