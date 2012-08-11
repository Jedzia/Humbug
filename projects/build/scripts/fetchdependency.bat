
mkdir %TMPDIR%
pushd %TMPDIR%
wget -c "%1%2"

tar xfz %2 

popd