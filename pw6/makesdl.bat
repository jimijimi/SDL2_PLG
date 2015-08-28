:: windows bat file that tries to replicate the makefile behavior
:: 2015 (c) J.Ortiz -- See copying file for license information.
:: Last update: August 10, 2015.

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
set CLIBW=/link /LIBPATH:"C:\\SDL2\\src\\SDL2-2.0.3\\lib\\x64" SDL2.lib SDL2main.lib SDL2_image.lib SDL2_mixer.lib

set CINCTCLW=/I"c:\\tcl8.6.4\\include"
set CLIBTCLW=/LIBPATH:"C:\\tcl8.6.4\\lib" tcl86t.lib

set CO=/subsystem:console
set CDEFS=/DWINDOWS
set CLIBGL=opengl32.lib


:: SDL EXAMPLES

if "%1" == "pw" (
   set SRC=resources.c background.c particle.c scripting.c main.c
   set OUT=pw.exe
   goto COMPILERCOMMAND
)

echo targets:
echo      pw


goto EXIT

:COMPILERCOMMAND

cl %CFLAGS% %CDEFS% %CINCW% %CINCTCLW% %SRC% /Fe%OUT% %CLIBW% %CO% %CLIBTCLW%

goto OPER

:OPER

md objs
md pw
move *obj objs\
move *exe pw\


:EXIT
