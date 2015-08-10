/*
  Listing 4-4 ( page 89 )
  converted to SDL2 by Jaime Ortiz. August 8, 2015
  See COPYING file for license information.
*/

#ifdef WINDOWS
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200


int main ( int argc, char ** argv )
{
	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;
	SDL_Surface* background = NULL;
	SDL_Surface* image_with_alpha = NULL;
	SDL_Surface* image_without_alpha = NULL;
	
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

	background = IMG_Load( "media/background.png" );

	if ( !background ){
		printf( "Unable to load bitmap, %s\n",
			SDL_GetError() );
		return 1;
	}

	image_with_alpha = IMG_Load( "media/with-alpha.png" );

	if ( !image_with_alpha ){
		printf( "Unable to load bitmap, %s\n",
			SDL_GetError() );
		return 1;
	}

	image_without_alpha = IMG_Load( "media/without-alpha.png" );

	if ( !image_with_alpha ){
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

	/* draw first image with the alpha channel*/
	SDL_SetSurfaceAlphaMod( image_with_alpha, 255 );
	SDL_SetSurfaceBlendMode( image_with_alpha, SDL_BLENDMODE_BLEND );
	src.w = image_with_alpha -> w;
	src.h = image_with_alpha -> h;
	dest.w = src.w;
	dest.h = src.h;
	dest.x = 40;
	dest.y = 50;
	SDL_BlitSurface( image_with_alpha, &src, screen, &dest );

	/* draw second image without alpha channel */
	SDL_SetSurfaceAlphaMod( image_without_alpha, 128 );
	SDL_SetSurfaceBlendMode( image_without_alpha, SDL_BLENDMODE_BLEND );
	src.w = image_without_alpha -> w;
	src.h = image_without_alpha -> h;

	dest.x = 180;
	dest.y = 50;
	dest.w = src.w;
	dest.h = src.h;

	SDL_BlitSurface( image_without_alpha, &src, screen, &dest );

	SDL_UpdateWindowSurface( window );

	SDL_Delay( 10000 );

	SDL_FreeSurface( background );
	SDL_FreeSurface( image_with_alpha );
	SDL_FreeSurface( image_without_alpha );
			
	return 0;
}
