echo off
set curdir=%~dp0
set rootdir=%curdir%..
cd %rootdir%
echo %rootdir%
set builddir=%rootdir%\build
if exist %builddir% (
      rd /s /q %builddir%
)

mkdir build
cd build

::setting vcpkg when using breakpad with vcpkg
::cmake .. -DUSE_VCPKG=on -DVCPKG_ROOT=F:/git/vcpkg

cmake ..
cmake --build . -target all --config RelWithDebInfo