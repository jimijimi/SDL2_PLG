/* 
   Keyboard input.
   Listing 4-10 PLG book page 117
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

	SDL_Joystick *js = NULL;

	int num_js = 0;
	int i = 0;
	int quit_flag = 0;


	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK ) < 0 ){
		printf( "Unable to initialize SDL: %s\n", SDL_GetError() );
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

	num_js = SDL_NumJoysticks();

	printf( "SDL recognizes %i joystick(s) on this system.\n", num_js );

	if ( num_js = 0 ){
		printf( "No joysticks were detected.\n" );
		return 1;
	}

	for ( i = 0 ; i < num_js; i ++ ){
		js = SDL_JoystickOpen( i );

		if ( !js ){
			printf( "Unable to open Joystick %i.\n", i );
		}
		else{
			printf( "Joystick %i\n", i );
			printf( "\tName:       %s\n", SDL_JoystickName( js ) );
			printf( "\tAxes:       %i\n", SDL_JoystickNumAxes( js ) );
			printf( "\tTrackballs: %i\n", SDL_JoystickNumBalls( js ) );
			printf( "\tButtons:    %i\n", SDL_JoystickNumButtons( js ) );

			SDL_JoystickClose( js );
		}
	}

	js = SDL_JoystickOpen( 0 );

	if ( !js ){
		printf( "Unable to open Joystick 0. %s\n",  SDL_GetError( ) );
		return 1;
	}

	quit_flag = 0;
	
	
	while( SDL_WaitEvent( &event ) != 0 && quit_flag == 0 ){
		SDL_Keysym keysym;
		
		switch ( event.type ){
		case SDL_KEYDOWN:
			if ( event.key.keysym.sym == SDLK_q ){
				printf( "'Q' pressed, exiting.\n" );
				quit_flag = 1;
			}
			break;
		case SDL_JOYAXISMOTION:
			printf( "Joystick %i, axis %i movement to %i\n",
				event.jaxis.which,
				event.jaxis.axis,
				event.jaxis.value );
			break;
		case SDL_JOYBUTTONUP:
		case SDL_JOYBUTTONDOWN:
			printf( "Joystick %i button %i: %i\n",
				event.jbutton.which,
				event.jbutton.button,
				event.jbutton.state );
			break;
		case SDL_QUIT:
			printf( "Quit event. Bye.\n" );
			exit( 0 );
		}
		
	}

	SDL_JoystickClose( js );
			
	SDL_DestroyWindow( window );

	return 0;
}

  
