sourceFiles := time.c movement.c objects.c controls.c main.c
buildDirectory := bin
cStandard := c11
defaultOptions := -std=$(cStandard) -fdiagnostics-color=always -g
programName := No-DLLs
compiler := gcc
SHELL := /bin/bash

windows-sdl:
	powershell -c "if (-not (Test-Path -Path $(buildDirectory))) {mkdir $(buildDirectory)}"
	$(compiler) $(defaultOptions) $(sourceFiles) -Ilib\SDL2\x86_64-w64-mingw32\include -Llib\SDL2\x86_64-w64-mingw32\lib -Wall -lmingw32 -lSDL2main -lSDL2  -o $(buildDirectory)/$(programName).exe

linux:
	if [[ ! -d $(buildDirectory) ]]; then mkdir $(buildDirectory); fi
	$(compiler) $(defaultOptions) $(sourceFiles) -o $(buildDirectory)/$(programName) -lm

linux-gtk:
	if [[ ! -d $(buildDirectory) ]]; then mkdir $(buildDirectory); fi
	$(compiler) $(defaultOptions) `pkg-config --cflags gtk4` $(sourceFiles) -o $(buildDirectory)/$(programName) `pkg-config --libs gtk4`

windows:
	powershell -c "if (-not (Test-Path -Path $(buildDirectory))) {mkdir $(buildDirectory)}"
	$(compiler) $(defaultOptions) $(sourceFiles) -o $(buildDirectory)/$(programName).exe

clean-linux:
	rm -rf $(buildDirectory)/*

clean-windows:
	powershell -c "rm -r -force $(buildDirectory)/*"