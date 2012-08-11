
mkdir %TMPDIR%
pushd %TMPDIR%
wget -c "%1%2"

unzip -qq -n %2 

popd