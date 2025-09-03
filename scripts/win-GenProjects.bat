@echo off
pushd ..\
call third_party\bin\premake\premake5.exe vs2022
popd
PAUSE