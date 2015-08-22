#ifndef RESOURCES_H
#define RESOURCES_H

#ifdef WINDOWS
#include<SDL.h>
#else
#include<SDL/SDL.h>
#endif

extern SDL_Surface *ship_strip;
extern SDL_Surface *front_star_tiles;
extern SDL_Surface *back_star_tiles;
extern int num_star_tiles;

void LoadGameData( SDL_Surface ** );

void UnloadGameData( void );

#endif
