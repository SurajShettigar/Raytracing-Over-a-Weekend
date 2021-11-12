@echo off
 
:: Create build dir
set buildDir=%~dp0..\build
if not exist %buildDir% mkdir %buildDir%
pushd %buildDir%
 
:: Create obj dir
set objDir=.\obj
if not exist %objDir% (
    mkdir %objDir%
    mkdir %objDir%\math
    mkdir %objDir%\utils
    mkdir %objDir%\tests
    mkdir %objDir%\geo
    mkdir %objDir%\material
    @REM mkdir %objDir%\game
)
 
:: Needed folders
set extDir=%~dp0..\external
set scriptDir=%~dp0..\scripts
 
:: Use make to build default target
cd %scriptDir%\
mingw32-make
 
popd