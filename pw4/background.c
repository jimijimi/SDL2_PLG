#include <time.h>
#include "gamedefs.h"
#include "background.h"
#include "resources.h"

static int front_tiles[PARALLAX_GRID_WIDTH][PARALLAX_GRID_HEIGHT];
static int back_tiles[PARALLAX_GRID_WIDTH][PARALLAX_GRID_HEIGHT];

static Sint32 seed = 0;

static void InitRandom()
{
	seed = time( NULL );
}

static unsigned int GetRandom()
{
	Sint32 p1 = 1103515245;
	Sint32 p2 = 12345;
	seed = (seed * p1 + p2) % 2147483647;
	return (unsigned) seed / 3;
}

void InitBackground()
{
	int x, y;

	InitRandom();
	for ( x = 0; x < PARALLAX_GRID_WIDTH; x++ ) {
		for ( y = 0; y < PARALLAX_GRID_HEIGHT; y++ ) {
			front_tiles[ x ][ y ] = GetRandom() % num_star_tiles;
			back_tiles[ x ][ y ] = GetRandom() % num_star_tiles;
		}
	}
}

void DrawBackground(SDL_Surface * dest, int camera_x, int camera_y)
{
	int draw_x, draw_y;
	int start_draw_x, start_draw_y;

	int tile_x, tile_y;
	int start_tile_x, start_tile_y;

	start_tile_x = ((camera_x / PARALLAX_BACK_FACTOR) /
			TILE_WIDTH) % PARALLAX_GRID_WIDTH;
	start_tile_y = ((camera_y / PARALLAX_BACK_FACTOR) /
			TILE_HEIGHT) % PARALLAX_GRID_HEIGHT;

	start_draw_x = -((camera_x / PARALLAX_BACK_FACTOR) % TILE_WIDTH);
	start_draw_y = -((camera_y / PARALLAX_BACK_FACTOR) % TILE_HEIGHT);

	tile_y = start_tile_y;
	draw_y = start_draw_y;
	while (draw_y < SCREEN_HEIGHT) {
		tile_x = start_tile_x;
		draw_x = start_draw_x;
		while (draw_x < SCREEN_WIDTH) {
			SDL_Rect srcrect, destrect;

			srcrect.x = TILE_WIDTH * back_tiles[tile_x][tile_y];
			srcrect.y = 0;
			srcrect.w = TILE_WIDTH;
			srcrect.h = TILE_HEIGHT;
			destrect.x = draw_x;
			destrect.y = draw_y;
			destrect.w = TILE_WIDTH;
			destrect.h = TILE_HEIGHT;

			SDL_BlitSurface(back_star_tiles, &srcrect, dest, &destrect);

			tile_x++;
			tile_x %= PARALLAX_GRID_WIDTH;
			draw_x += TILE_WIDTH;
		}
		tile_y++;
		tile_y %= PARALLAX_GRID_HEIGHT;
		draw_y += TILE_HEIGHT;
	}
}

void DrawParallax(SDL_Surface * dest, int camera_x, int camera_y)
{
	int draw_x, draw_y;
	int start_draw_x, start_draw_y;

	int tile_x, tile_y;
	int start_tile_x, start_tile_y;


	start_tile_x = ((camera_x / PARALLAX_FRONT_FACTOR) /
			TILE_WIDTH) % PARALLAX_GRID_WIDTH;
	start_tile_y = ((camera_y / PARALLAX_FRONT_FACTOR) /
			TILE_HEIGHT) % PARALLAX_GRID_HEIGHT;

	start_draw_x = -((camera_x / PARALLAX_FRONT_FACTOR) % TILE_WIDTH);
	start_draw_y = -((camera_y / PARALLAX_FRONT_FACTOR) % TILE_HEIGHT);

	tile_y = start_tile_y;
	draw_y = start_draw_y;
	while (draw_y < SCREEN_HEIGHT) {
		tile_x = start_tile_x;
		draw_x = start_draw_x;
		while (draw_x < SCREEN_WIDTH) {
			SDL_Rect srcrect, destrect;

			srcrect.x = TILE_WIDTH * front_tiles[tile_x][tile_y];
			srcrect.y = 0;
			srcrect.w = TILE_WIDTH;
			srcrect.h = TILE_HEIGHT;
			destrect.x = draw_x;
			destrect.y = draw_y;
			destrect.w = TILE_WIDTH;
			destrect.h = TILE_HEIGHT;

			SDL_BlitSurface(front_star_tiles, &srcrect, dest, &destrect);

			tile_x++;
			tile_x %= PARALLAX_GRID_WIDTH;
			draw_x += TILE_WIDTH;
		}
		tile_y++;
		tile_y %= PARALLAX_GRID_HEIGHT;
		draw_y += TILE_HEIGHT;
	}
}
