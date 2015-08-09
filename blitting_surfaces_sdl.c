/*
  Listing 4-3 ( page 84 ) of Programming Linux Games
  converted to SDL2 by Jaime Ortiz.  August 2, 2015
 */

#ifdef WINDOWS
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

int main( int argc, char **argv )
{
	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;
	SDL_Surface* image = NULL;
	SDL_Rect src;
	SDL_Rect dest;
	
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "Unable to initialize SDL: %s\n",
			SDL_GetError() );
		return 1;
	}

	atexit( SDL_Quit );

	window = SDL_CreateWindow( "Initialize Window Example",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   SCREEN_WIDTH, SCREEN_HEIGHT,
				   SDL_WINDOW_SHOWN );

	if ( !window ){
		printf( "Unable to create window, %s\n",
			SDL_GetError() );
		return 1;
	}

	screen = SDL_GetWindowSurface( window );

	if ( !screen ){
		printf( "Unable to set the screen, %s\n",
			SDL_GetError() );
		return 1;
	}

	image = SDL_LoadBMP( "media/test-image.bmp" );

	if ( !image ){
		printf( "Unable to load bitmap\n" );
		return 1;
	}

	src.x = 0;
	src.y = 0;
	src.w = image -> w;
	src.h = image -> h;

	dest.x = 0;
	dest.y = 0;
	dest.w = image -> w;
	dest.h = image -> h;
	
	SDL_BlitSurface( image, &src, screen, &dest );
		
	SDL_UpdateWindowSurface( window );

	SDL_Delay( 5000 );

	SDL_FreeSurface( image );

	SDL_DestroyWindow( window );
	
	return 0;
}

