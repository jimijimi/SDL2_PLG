# make file for the SDLv2 PLG examples.
# 2015 (c) J. Ortiz - See COPYING file for license information.

CCL=gcc
CFLAGSL=-Wall
CLIBSL=-LSDL2

CCW=cl
CFLAGSW=/MD
CINCW=/I"c:\\SDL2\\src\\SDL2-2.0.3\\include\\"
CLIBW=/link /LIBPATH:"C:\SDL2\src\SDL2-2.0.3\lib\x64" SDL2.lib SDL2main.lib SDL2_image.lib
CO=/subsystem:console
CDEFS=/DWINDOWS


all:
	@echo "Hello"
	echo targets
	echo      initsdl
	echo      pixeldrawing
	echo      blittingsurf
	echo      colorkey
	echo      alpha
	echo      anim1
	echo      anim2
	echo      anim21
	echo      mouse
	echo      keyboard
	echo      joystick
	echo      threads


initsdl_linux:
	$(CCL) \
	$(CFLAGSL) \
	initializing_sdl.c \
	-o c4_01_initsdl \
	$(CLIBSL)

initsdl_win:
	$(CCW) \
	$(CFLAGSW) \
	$(CDEFS) $(CINCW) \
	initializing_sdl.c \
	/Fe"c4_01_initsdl.exe" \
	$(CLIBW) $(CO)

#

pixeldrawing_linux:
	$(CCL) \
	$(CFLAGSL) \
	direct_pixel_drawing_sdl.c \
	-o c4_02_pixeldrawing \
	$(CLIBSL)

pixeldrawing_win:
	$(CCW) \
	$(CFLAGSW) \
	$(CDEFS) $(CINCW) \
	direct_pixel_drawing_sdl.c \
	/Fe"c4_02_pixeldrawing.exe" \
	$(CLIBW) $(CO)


#

blittingsurf_linux:
	$(CCL) \
	$(CFLAGSL) \
	blitting_surface_sdl.c \
	-o c4_03_blitting_surf \
	$(CLIBSL)

blittingsurf_win:
	$(CCW) \
	$(CFLAGSW) \
	$(CDEFS) $(CINCW) \
	blitting_surface_sdl.c \
	/Fe"c4_03_blittingsurf.exe" \
	$(CLIBW) $(CO)


#

colorkey_linux:
	$(CCL) \
	$(CFLAGSL) \
	colorkeys_sdl.c \
	-o c4_04_colorkeys \
	$(CLIBSL)

colorkey_win:
	$(CCW) \
	$(CFLAGSW) \
	$(CDEFS) $(CINCW) \
	colorkeys_sdl.c \
	/Fe"c4_04_colorkeys.exe" \
	$(CLIBW) $(CO)

#

alpha_linux:
	$(CCL) \
	$(CFLAGSL) \
	alpha_sdl.c \
	-o c4_05_alpha \
	$(CLIBSL)

alpha_win:
	$(CCW) \
	$(CFLAGSW) \
	$(CDEFS) $(CINCW) \
	alpha_sdl.c \
	/Fe"c4_05_alpha.exe" \
	$(CLIBW) $(CO)

