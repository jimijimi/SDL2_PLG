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
	initializing_sdl.c \
	-o c4_1_initsdl \
	$(CLIBSL)

initsdl_win:
	$(CCW) \
	$(CFLAGSW) \
	$(CDEFS) $(CINCW) \
	initializing_sdl.c \
	/Fe"c4_1_initsdl.exe" \
	$(CLIBW) $(CO)

#

pixeldrawing_linux:
	$(CCL) \
	$(CFLAGSL) \
	direct_pixel_drawing_sdl.c \
	-o c4_2_pixeldrawing \
	$(CLIBSL)

pixeldrawing_win:
	$(CCW) \
	$(CFLAGSW) \
	$(CDEFS) $(CINCW) \
	direct_pixel_drawing_sdl.c \
	/Fe"c4_2_pixeldrawing.exe" \
	$(CLIBW) $(CO)


#

blittingsurf_linux:
	$(CCL) \
	$(CFLAGSL) \
	blitting_surface_sdl.c \
	-o c4_3_blitting_surf \
	$(CLIBSL)

blittingsurf_win:
	$(CCW) \
	$(CFLAGSW) \
	$(CDEFS) $(CINCW) \
	blitting_surface_sdl.c \
	/Fe"c4_3_blittingsurf.exe" \
	$(CLIBW) $(CO)



