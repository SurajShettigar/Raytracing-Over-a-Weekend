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
    mkdir %objDir%\raytracer
    mkdir %objDir%\raytracer\geo
    mkdir %objDir%\raytracer\material
    mkdir %objDir%\raytracer\utils
)
 
:: Needed folders
set extDir=%~dp0..\external
set scriptDir=%~dp0..\scripts
 
:: Use make to build default target
cd %scriptDir%\
mingw32-make
 
popd