
mkdir %TMPDIR%
pushd %TMPDIR%
wget -c "%1%2"

rem tar xfz %2
TarTool %2

popd