/*
  Listing 4-1 ( page 74 ) of Programming linux games
  converted to SDL2
 */

#ifdef WINDOWS
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main( int argc, char **argv )
{
	SDL_Window* window = NULL;

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

	printf( "Sucess!\n" );
	return 0;
}
