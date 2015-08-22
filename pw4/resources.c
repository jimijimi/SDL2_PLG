#include <stdio.h>
#include <stdlib.h>
#include "gamedefs.h"
#include "resources.h"

SDL_Surface *ship_strip;	/* rotating ship in 2-degree increments */
SDL_Surface *front_star_tiles;	/* for the parallaxing star layer */
SDL_Surface *back_star_tiles;	/* for the star background */
int num_star_tiles;		/* derived from the width of the loaded strips */

void LoadGameData( SDL_Surface ** screen )
{
	printf( "Loading assets.\n" );
	SDL_Surface *tmp;
	Uint32 colorkey;


	/*STARFIGHTER*/

	printf( "starfighter.\n" );
	
	tmp = SDL_LoadBMP( "fighter.bmp" );

	if ( !tmp ) {
		fprintf( stderr, "Unable to load ship image: %s\n", SDL_GetError() );
		exit( 1 );
	}
	
	SDL_SetColorKey( tmp, SDL_TRUE, SDL_MapRGB( tmp -> format, 0, 0, 0 ) );
	
	ship_strip = SDL_ConvertSurface( tmp, ( *screen ) -> format, 0 );
	
	if ( !ship_strip ) {
		ship_strip = tmp;
	}
	else {
		SDL_FreeSurface( tmp );
	}

	/*BACKSTARTS*/

	printf( "backstars\n" );
	
	tmp = SDL_LoadBMP("back-stars.bmp");
	
	if ( !tmp ) {
		fprintf( stderr, "Unable to load background tiles: %s\n", SDL_GetError( ) );
		exit( 1 );
	}
	
	num_star_tiles = tmp -> w / 64;
	num_star_tiles = 4;
	

	back_star_tiles = SDL_ConvertSurface( tmp, ( *screen ) -> format, 0 );
	if ( !back_star_tiles){
		back_star_tiles = tmp;
	}
	else{
		SDL_FreeSurface(tmp);
	}

	/*PARALAXING*/

	printf( "paralax stars.\n" );

	tmp = SDL_LoadBMP( "front-stars.bmp" );
	if ( !tmp ) {
		printf( "Unable to load parallax tiles: %s\n", SDL_GetError( ) );
		exit( 1 );
	}
	
	SDL_SetColorKey( tmp, SDL_TRUE, SDL_MapRGB( tmp -> format, 0, 0, 0 ) );
	

	front_star_tiles = SDL_ConvertSurface( tmp, ( *screen ) -> format, 0 );
	if ( !front_star_tiles ){
		front_star_tiles = tmp;
	}
	else{
		SDL_FreeSurface(tmp);
	}

	printf( "Succesfully loaaded assets.\n" );
}

void UnloadGameData( void )
{
    if ( ship_strip ) {
	SDL_FreeSurface( ship_strip );
	ship_strip = NULL;
    }
    if ( front_star_tiles ) {
	SDL_FreeSurface( front_star_tiles );
	front_star_tiles = NULL;
    }
    if ( back_star_tiles != NULL ) {
      SDL_FreeSurface(back_star_tiles);
      back_star_tiles = NULL;
    }
}
