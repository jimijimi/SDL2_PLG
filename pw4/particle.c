#include <math.h>
#include <stdlib.h>
#include "gamedefs.h"
#include "particle.h"

particle_t particles[MAX_PARTICLES];
int active_particles = 0;

static void AddParticle(particle_p particle);
static void DeleteParticle(int index);
static Uint16 CreateHicolorPixel(SDL_PixelFormat * fmt, Uint8 red,
				 Uint8 green, Uint8 blue);

static void AddParticle(particle_p particle)
{
	if (active_particles >= MAX_PARTICLES)
		return;

	particles[active_particles] = *particle;
	active_particles++;
}


static void DeleteParticle(int index)
{
	particles[index] = particles[active_particles - 1];
	active_particles--;
}


void DrawParticles(SDL_Surface * dest, int camera_x, int camera_y)
{
	int i;
	Uint16 *pixels;


	if (SDL_LockSurface(dest) != 0)
		return;
	pixels = (Uint16 *) dest->pixels;

	for (i = 0; i < active_particles; i++) {
		int x, y;
		Uint16 color;


		x = particles[i].x - camera_x;
		y = particles[i].y - camera_y;
		if ((x < 0) || (x >= SCREEN_WIDTH))
			continue;
		if ((y < 0) || (y >= SCREEN_HEIGHT))
			continue;


		color = CreateHicolorPixel(dest->format,
					   particles[i].r,
					   particles[i].g, particles[i].b);


		pixels[(dest->pitch / 2) * y + x] = color;
	}


	SDL_UnlockSurface(dest);
}


void UpdateParticles(void)
{
	int i;

	for (i = 0; i < active_particles; i++) {
		particles[i].x += particles[i].energy *
			cos(particles[i].angle * PI / 180.0) * time_scale;
		particles[i].y += particles[i].energy *
			-sin(particles[i].angle * PI / 180.0) * time_scale;


		particles[i].r--;
		particles[i].g--;
		particles[i].b--;
		if (particles[i].r < 0)
			particles[i].r = 0;
		if (particles[i].g < 0)
			particles[i].g = 0;
		if (particles[i].b < 0)
			particles[i].b = 0;


		if ((particles[i].r + particles[i].g + particles[i].b) == 0) {
			DeleteParticle(i);


			i--;
		}
	}
}


void CreateParticleExplosion(int x, int y, int r, int g, int b, int energy,
			     int density)
{
	int i;
	particle_t particle;


	for ( i = 0; i < density; i++ ) {

		particle.x = x;
		particle.y = y;
		particle.angle = rand() % 360;
		particle.energy = (double) (rand() % (energy * 1000)) / 1000.0;


		particle.r = r;
		particle.g = g;
		particle.b = b;


		AddParticle(&particle);
	}
}


static Uint16 CreateHicolorPixel(SDL_PixelFormat * fmt, Uint8 red,
				 Uint8 green, Uint8 blue)
{
	Uint16 value;

	value = ( ( ( red >> fmt -> Rloss ) << fmt -> Rshift ) +
		  ( ( green >> fmt -> Gloss) << fmt -> Gshift ) +
		  ( ( blue >> fmt -> Bloss ) << fmt -> Bshift ));

	return value;
}
