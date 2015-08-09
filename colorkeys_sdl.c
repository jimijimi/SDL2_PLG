/*
  Listing 4-4 ( page 89 )
  converted to SDL2 by Jaime Ortiz August 3, 2015
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


int main ( int argc, char ** argv )
{
	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;
	SDL_Surface* background = NULL;
	SDL_Surface* image = NULL;

	SDL_Rect src;
	SDL_Rect dest;

	Uint32 colorkey;

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "Unable to initialize SDL: %s\n",
			SDL_GetError( ) );
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

	background = SDL_LoadBMP( "media/background.bmp" );

	if ( !background ){
		printf( "Unable to load bitmap, %s\n",
			SDL_GetError() );
		return 1;
	}

	image = SDL_LoadBMP( "media/penguin.bmp" );

	if ( !image ){
		printf( "Unable to load bitmap, %s\n",
			SDL_GetError() );
		return 1;
	}	

	/* draw background */
	src.x = 0;
	src.y = 0;
	src.w = background -> w;
	src.h = background -> h;

	dest.x = 0;
	dest.y = 0;
	dest.w = background -> w;
	dest.h = background -> h;
	SDL_BlitSurface( background, &src, screen, &dest );

	/* draw penguin without colorkey */
	src.x = 0;
	src.y = 0;
	src.w = image -> w;
	src.h = image -> h;

	dest.x = 30;
	dest.y = 90;
	dest.w = image -> w;
	dest.h = image -> h;
	SDL_BlitSurface( image, &src, screen, &dest );

	colorkey = SDL_MapRGB( image -> format, 0, 0, 255 );

	SDL_SetColorKey( image, SDL_TRUE, colorkey );

	src.x = 0;
	src.y = 0;
	src.w = image -> w;
	src.h = image -> h;

	dest.x = screen -> w - image -> w - 30;
	dest.y = 90;
	dest.w = image -> w;
	dest.h = image -> h;

	SDL_BlitSurface( image, &src, screen, &dest );

	SDL_UpdateWindowSurface( window );

	SDL_Delay( 10000 );

	SDL_FreeSurface( background );
	SDL_FreeSurface( image );
			
	return 0;
}
