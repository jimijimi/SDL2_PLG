/* 
   Keyboard input. Listing 4-9 PLG book page 113
   Ported to SDL2 by Jaime Ortiz. August 14, 2015
   See COPYING for licence information.
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
	
	window = SDL_CreateWindow( "SDL Keyboard demo",
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

	printf( "Press Q to quit.\n" );
	
	while( SDL_WaitEvent( &event ) != 0 ){
		SDL_Keysym keysym;
		
		switch ( event.type ){
		case SDL_KEYDOWN:
			printf( "Key pressed." );
			keysym = event.key.keysym;
			printf( "SDL keysym is %i. ",
				keysym.sym );
			printf( "(%s )",
				SDL_GetKeyName( keysym.sym ) );

			if( event.key.keysym.mod & KMOD_LSHIFT ){
				printf( "Left shift is down.\n" );
			}
			else{
				printf( "Left shift is up.\n" );
			}

			if ( keysym.sym == SDLK_q ){
				printf( "'Q' pressed, exiting.\n" );
				exit( 0 );
			}
				
			break;
		case SDL_KEYUP:
			printf( "Key released. " );
			printf( "SDL keysym is %i. ",
				keysym.sym );

			if ( event.key.keysym.mod & KMOD_LSHIFT ){
				printf( "Left Shift is down.\n" );
			}
			else{
				printf( "Left Shift is up.\n" );
			}
			break;
		case SDL_QUIT:
			printf( "Quit event. Bye.\n" );
			exit( 0 );
		}
		
	}
		
	SDL_DestroyWindow( window );

	return 0;
}

  
