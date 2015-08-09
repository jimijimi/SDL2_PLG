:: windows bat file that tries to replicate the makefile behavior
:: 2015 (c) J.Ortiz -- See copying file for license information.

:: usage: make [case] <enter>
:: to see the list of cases, type makesdl <enter>

@echo off

:: COMPILER OPTIONS
:: Change the paths according to your computer setup
:: you may need to recompile the libraries:
::    SDL2.lib
::    SDL2main.lib
::    SDL2_image
::    SDL2.dll
::    SDL2main.dll
::    SDL2_image.dll

set CFLAGS=/MD
set CINCW=/I"c:\\SDL2\\src\\SDL2-2.0.3\\include"
set CLIBW=/link /LIBPATH:"C:\\SDL2\\src\\SDL2-2.0.3\\lib\\x64" SDL2.lib SDL2main.lib SDL2_image.lib
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

if "%1" == "blittingsurf" (
   set SRC=blitting_surfaces_sdl.c
   set OUT=c4_3_blitsurf.exe
   goto COMPILERCOMMAND
)

if "%1" == "colorkey" (
   set SRC=colorkeys_sdl.c
   set OUT=c4_4_colorkeys.exe
   goto COMPILERCOMMAND
)

if "%1" == "alpha" (
   set SRC=alpha_sdl.c
   set OUT=c4_5_alpha.exe
   goto COMPILERCOMMAND
)

if "%1" == "anim1" (
   set SRC=anim1.c
   set OUT=c4_6_anim1.exe
   goto COMPILERCOMMAND
)

echo targets:
echo      initsdl
echo      pixeldrawing
echo      blittingsurf
echo      colorkey
echo      alpha
echo      anim1


goto EXIT

:COMPILERCOMMAND

cl %CFLAGS% %CDEFS% %CINCW% %SRC% /Fe%OUT% %CLIBW% %CO% %CIMG%

md objs
md exes
move *obj objs\
move *exe exes\

:EXIT
