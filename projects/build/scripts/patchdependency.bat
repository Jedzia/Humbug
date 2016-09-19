@set PACURDIR=%CD%
REM mkdir %TMPDIR%
REM pushd %TMPDIR%/%2

if "%1" == "unzip" (
	unzip -o -qq "%3" -d%2
REM echo	unzip -o -qq "%3" -d%2
)

REM popd