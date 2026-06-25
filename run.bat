@echo off 

:: Configura o projeto usando o JSON (só precisa rodar uma vez, mas não faz mal rodar sempre)
cmake --preset default

:: Compila usando o JSON
cmake --build --preset build-release

:: Executa
build\hello-world.exe
