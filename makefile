# make file for the SDLv2 PLG examples.
# 2015 (c) J. Ortiz - See COPYING file for license information.

CCL=gcc
CFLAGSL=-Wall
CLIBSL=-LSDL2

CCW=cl
CFLAGSW=/MD
CINCW=/I"c:\\SDL2\\src\\SDL2-2.0.3\\include\\"
CLIBW=/link /LIBPATH:"C:\SDL2\src\SDL2-2.0.3\lib\x64" SDL2.lib SDL2main.lib
CO=/subsystem:console
CDEFS=/DWINDOWS


all:
	@echo "Hello"

initsdl_linux:
	$(CCL) \
	$(CFLAGSL) \
	initializing_sdl.c -o c4_1_initsdl \
	$(CLIBSL)

initsdl_win:
	$(CCW) \
	$(CFLAGSW) \
	$(CDEFS) $(CINCW) \
	initializing_sdl.c /Fe"c4_1_initsdl.exe"
	$(CLIBW) $(CO)




