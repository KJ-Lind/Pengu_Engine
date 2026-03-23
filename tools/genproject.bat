@echo off
cd %~dp0..
del build
mkdir build
call tools\gendeps.bat
call tools\premake5.exe vs2022
