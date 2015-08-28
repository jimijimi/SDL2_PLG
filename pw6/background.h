#ifndef BACKGROUND_H
#define BACKGROUND_H

#ifdef WINDOWS
#include<SDL.h>
#else
#include<SDL2/SDL.h>
#endif

void InitBackground( void );

void DrawBackground( SDL_Surface *dest, int camera_x, int camera_y );

void DrawParallax( SDL_Surface *dest, int camera_x, int camera_y );

#endif
