#ifndef PARTICLE_H
#define PARTICLE_H

#ifdef WINDOWS
#include<SDL.h>
#else
#include<SDL/SDL.h>
#endif

typedef struct particle_s {
	double x,y;
	double energy;
	double angle;
	int r, g, b;
} particle_t, *particle_p;

void DrawParticles(SDL_Surface *dest, int camera_x, int camera_y);


void UpdateParticles(void);


void CreateParticleExplosion(int x, int y, int r, int g, int b, int energy, int density);

#endif
