:: windows bat file that tries to replicate the makefile behavior
:: 2015 (c) J.Ortiz -- See copying file for license information.

:: usage:  make <case>

@echo off

:: COMPILER OPTIONS

set CFLAGS=/MD
set CINCW=/I"c:\\SDL2\\src\\SDL2-2.0.3\\include"
set CLIBW=/link /LIBPATH:"C:\\SDL2\\src\\SDL2-2.0.3\\lib\\x64" SDL2.lib SDL2main.lib
set CO=/subsystem:console
set CDEFS=/DWINDOWS

:: SDL EXAMPLES

if "%1" == "initsdl" (
   set SRC=initializing_sdl.c
   set OUT=c4_1_initsdl.exe
   goto COMPILERCOMMAND
)

if "%1" == "pixeldrawing" (
   set SRC=direct_pixel_drawing_sdl.c
   set OUT=c4_2_pixeldrawing.exe
   goto COMPILERCOMMAND
)

goto EXIT

:COMPILERCOMMAND

cl %CFLAGS% %CDEFS% %CINCW% %SRC% /Fe%OUT% %CLIBW% %CO%

:EXIT
