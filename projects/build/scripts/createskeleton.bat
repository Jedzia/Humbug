REM use this in a project/_ProjectName_ folder

mkdir docs
mkdir docs\%1
mkdir Model
mkdir Model\%1
mkdir po
mkdir po\lib
mkdir src
mkdir src\%1
mkdir src\UnitTests

echo >> CMakeLists.txt

echo >> po\CMakeLists.txt
echo >> src\CMakeLists.txt
echo >> src\%1\CMakeLists.txt
echo >> src\UnitTests\CMakeLists.txt