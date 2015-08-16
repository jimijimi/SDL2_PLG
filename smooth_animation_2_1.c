/* 
   Listing 4-7 ( page 104 )
   converted to SDL2 by Jaime Ortiz. August 9, 2015
   See COPYING file for license information.
*/

#ifdef WINDOWS
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NUM_PENGUINS 100
#define MAX_SPEED 6

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct penguin{
	int x;
	int y;
	int dx;
	int dy;
};


void InitPenguins( struct penguin *, SDL_Surface * );
void MovePenguins( struct penguin *, SDL_Surface * );
void DrawPenguins( struct penguin *, SDL_Surface *, SDL_Surface * );


int main( int argc, char **argv )
{
	SDL_Window* window = NULL;
	SDL_Surface* background = NULL;

	SDL_Surface *temp = NULL;
	SDL_Surface *penguin = NULL;
	SDL_Surface *screen = NULL;

	SDL_Renderer* renderer = NULL;
	SDL_Texture* render_texture = NULL;
		
	SDL_Rect src;
	SDL_Rect dest;

	int frames = 0;

	struct penguin penguins[ NUM_PENGUINS ];
	
	
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "Unable to initialize SDL: %s\n",
			SDL_GetError( ) );
		return 1;
	}

	atexit( SDL_Quit );

	window = SDL_CreateWindow( "Smooth Animation 2",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   SCREEN_WIDTH, SCREEN_HEIGHT,
				   SDL_WINDOW_SHOWN );


	if ( !window ){
		printf( "Unable to create window, %s\n",
			SDL_GetError() );
		return 1;
	}

	renderer = SDL_CreateRenderer( window, -1, 0 );
	
	if ( !renderer ){
		printf( "Unable to set the screen, %s\n",
			SDL_GetError() );
		return 1;
	}


	screen = SDL_GetWindowSurface( window );

	if ( !screen ){
		printf( "Unable to set the screen, %s\n",
			SDL_GetError() );
		return 1;
	}

	render_texture = SDL_CreateTextureFromSurface( renderer, screen );
	
	if ( !render_texture ){
		printf( "Unable to set the screen texture, %s\n",
			SDL_GetError() );
		return 1;
	}
	
	//
	
	temp = SDL_LoadBMP( "media/background.bmp" );

	if ( !temp ){
		printf( "Unable to load bitmap, %s\n",
			SDL_GetError() );
		return 1;
	}

	
	background = SDL_ConvertSurface( temp, screen -> format, 0 );


	if ( !background ){
		printf( "Unable to load bitmap, %s\n",
			SDL_GetError() );
		return 1;
	}

	SDL_FreeSurface( temp );

	//

	temp = SDL_LoadBMP( "media/smallpenguin.bmp" );

	
	if ( !temp ){
		printf( "Unable to load bitmap, %s\n",
			SDL_GetError() );
		return 1;
	}

	SDL_SetColorKey( temp,
			 SDL_TRUE,
			 (Uint16) SDL_MapRGB( temp -> format,
					      0,
					      0,
					      255 ) );

	penguin = SDL_ConvertSurface( temp, screen -> format, 0 );

	if ( !penguin ){
	  	printf( "Unable to convert bitmap, %s\n",
			SDL_GetError() );
		return 1;
	}

	SDL_FreeSurface( temp );

		
	InitPenguins( penguins, screen );

	for ( frames = 0; frames < 300; frames ++ ){
		src.x = 0;
		src.y = 0;
		src.w = background -> w;
		src.h = background -> h;

		dest = src;

		SDL_BlitSurface( background, &src, screen, &dest );
		DrawPenguins( penguins, penguin, screen );
		SDL_UpdateTexture( render_texture, NULL, screen -> pixels, screen -> pitch );
		SDL_RenderClear( renderer );
		SDL_RenderCopy( renderer, render_texture, NULL, NULL );
		SDL_RenderPresent( renderer );

		MovePenguins( penguins, screen );
	}

	SDL_Delay( 4000 );
		
	SDL_FreeSurface( background );
	SDL_FreeSurface( penguin );

	SDL_DestroyWindow( window );
		
	return 0;
}



void InitPenguins( struct penguin *penguins, SDL_Surface *screen )
{
	int i = 0;

	srand( time( NULL ) );
		
	for ( i = 0; i < NUM_PENGUINS; i ++ ){
		penguins[ i ].x = rand() % screen -> w;
		penguins[ i ].y = rand() % screen -> h;
		penguins[ i ].dx = ( rand() % ( MAX_SPEED * 2 ) ) - MAX_SPEED;
		penguins[ i ].dy = ( rand() % ( MAX_SPEED * 2 ) ) - MAX_SPEED;
	}
}


void MovePenguins( struct penguin *penguins,
		   SDL_Surface *screen )
{
	int i = 0;

	for ( i = 0; i < NUM_PENGUINS; i ++ ){
		penguins[ i ].x += penguins[ i ].dx;
		penguins[ i ].y += penguins[ i ].dy;

		if ( penguins[ i ].x < 0 || penguins[ i ].x > screen -> w - 1 ){
			penguins[ i ].dx = -penguins[ i ].dx;
		}

		if ( penguins[ i ].y < 0 || penguins[ i ].y > screen -> h - 1 ){
			penguins[ i ].dy = -penguins[ i ].dy;
		}
	}
}


void DrawPenguins( struct penguin *penguins,
		   SDL_Surface *penguin,
		   SDL_Surface *screen )
{
	int i = 0;
	SDL_Rect src;
	SDL_Rect dest;

	for ( i = 0; i < NUM_PENGUINS; i ++ ){
		src.x = 0;
		src.y = 0;
		src.w = penguin -> w;
		src.h = penguin -> h;

		dest.x = penguins[ i ].x - penguin -> w / 2;
		dest.y = penguins[ i ].y - penguin -> h / 2;
		dest.w = penguin -> w;
		dest.h = penguin -> h;

		SDL_BlitSurface( penguin, &src, screen, &dest );
	}
}

