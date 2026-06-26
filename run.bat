@echo off 

:: Compila usando o JSON
cmake --build --preset build-release

:: Executa
build\hello-world.exe
