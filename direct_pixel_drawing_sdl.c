/*
  Listing 4-2 ( page 79 ) of Programming Linux Games
  converted to SDL2 by Jaime Ortiz. July 2015.
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

Uint16 CreateHicolorPixel( SDL_PixelFormat *, Uint8, Uint8, Uint8 );

int main( int argc, char **argv )
{
	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;
	
	Uint16 *raw_pixels;
	int x, y;

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
	
	SDL_LockSurface( screen );

	raw_pixels = ( Uint16 * ) screen -> pixels;

	for ( x = 0; x < 256; x ++ ){
		for ( y = 0; y < 256; y ++ ){
			Uint16 pixel_color = 0;
			int offset = 0;
			pixel_color = CreateHicolorPixel( screen -> format, x, 0, y );
			offset = screen -> pitch / 2 * y + x;
			raw_pixels[ offset ] = pixel_color;
		}
	}
	
	
	SDL_UnlockSurface( screen );
		
	SDL_UpdateWindowSurface( window );

	SDL_Delay( 5000 );

	return 0;
}


Uint16 CreateHicolorPixel( SDL_PixelFormat *fmt, Uint8 red, Uint8 green, Uint8 blue )
{
	Uint16 value;
	value = ( ( red >> fmt -> Rloss ) << fmt -> Rshift ) +
		( ( green >> fmt -> Gloss ) << fmt -> Gshift ) +
		( ( blue >> fmt -> Bloss ) << fmt -> Bshift );

	return value;
}

