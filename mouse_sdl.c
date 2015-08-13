/*
  Listing 4-8 Programming Linux Games Book
  Ported to SDL2 by Jaime Ortiz. August 13, 2015.
  See COPYING file for license information.
*/

#ifdef WINDOWS
#include<SDL.h>
#else
#include<SDL/SDL.h>
#endif

#include<stdio.h>
#include<stdlib.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

int main( int argc, char ** argv ){
	SDL_Window *window = NULL;
	SDL_Surface *screen;
	SDL_Event event;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "Unable to initialize SDL: %s\n" );
	}

	atexit( SDL_Quit );
	
	window = SDL_CreateWindow( "SDL mouse",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   SCREEN_WIDTH, SCREEN_HEIGHT,
				   SDL_WINDOW_SHOWN );

	if ( !window ){
		printf( "Unable to set the Main Window. %s\n",
			SDL_GetError() );
		return 1;
	}
		
	screen = SDL_GetWindowSurface( window );

	if ( !screen ){
		printf( "Unable to set the screen. %s\n",
		       SDL_GetError() );
	}
	
	while( SDL_WaitEvent( &event ) != 0 ){
		switch ( event.type ){
		case SDL_MOUSEMOTION:
			printf( "Mouse motion." );
			printf( "New position is ( %i %i.)",
				event.motion.x,
				event.motion.y );
			printf( "That is a ( %i, %i) change.\n",
				event.motion.xrel,
				event.motion.yrel );
			break;
		case SDL_MOUSEBUTTONDOWN:
			printf( "Mouse button pressed." );
			printf( "Button %i at ( %i, %i )\n",
				event.button.button,
				event.button.x,
				event.button.y );
			break;
		case SDL_QUIT:
			printf( "Quit event. Bye.\n" );
			exit( 0 );
		}
		
	}
		
	SDL_DestroyWindow( window );

	return 0;
}

  
