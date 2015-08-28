#ifndef GAMEDEFS_H
#define GAMEDEFS_H

#define SCREEN_WIDTH	640
#define SCREEN_HEIGHT	480

#define MAX_PARTICLES	10000

#define PLAYER_WIDTH	96
#define PLAYER_HEIGHT	96

#define TILE_WIDTH	64
#define TILE_HEIGHT	64

#define WORLD_WIDTH	2000
#define WORLD_HEIGHT	2000

#define PLAYER_MAX_VELOCITY	(15.0)
#define PLAYER_MIN_VELOCITY	(-5.0)

#define PLAYER_FORWARD_THRUST	(3)
#define PLAYER_REVERSE_THRUST	(-2)

#define PARALLAX_BACK_FACTOR	4
#define PARALLAX_FRONT_FACTOR	2

#define PARALLAX_GRID_WIDTH     100
#define PARALLAX_GRID_HEIGHT    100

#define PI (3.141592654F)

extern double time_scale;

typedef struct player_s {
	double angle;
	double world_x, world_y;
	int screen_x, screen_y;
	double velocity;
	double accel;
	int shields;
} player_t, *player_p;

#endif
