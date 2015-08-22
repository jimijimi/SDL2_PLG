/* 
   This is the first prototype of PW as shown in PLG
   There are some small changes in the code so it can run using SDL2.
   However it can be noticed that there is repeaded code in the main file 
   and the provided libraries.
   I will make an attempt to remove the repeated code, 
   remove de global variables and make the 
   code a bit more compact
   This demo works fine in Debian 8 and Windows 10.
 */

#ifdef WINDOWS
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "gamedefs.h"
#include "particle.h"
#include "background.h"
#include "resources.h"

#define CAP_FRAME_RATE 30

const int TICKS_PER_FRAME = 1000 / CAP_FRAME_RATE;


typedef struct player_s {
	double angle;		
	double world_x,world_y;	
	int screen_x,screen_y;	
	double velocity;	
	double accel;		
	int shields;		
} player_t, *player_p;

enum { OPP_COMPUTER, OPP_NETWORK } opponent_type;
player_t player;		
player_t opponent;		


static int camera_x, camera_y;	

/* The window system */
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *screen = NULL;		
SDL_Texture *render_texture = NULL;


int fullscreen = 0;
int hwsurface = 0;
int doublebuf = 0;

double time_scale = 0;

/* ==========
   Prototypes
   ========== */

static unsigned int getrandom();
static void InitRandom();
static void DrawPlayer(player_p p);
static void InitPlayer();
static void UpdatePlayer(player_p p);
static void PlayGame();

static Sint32 seed = 0;

static void InitRandom()
{
	seed = time( NULL );
}

static unsigned int GetRandom( )
{
	Sint32 p1 = 1103515245;
	Sint32 p2 = 12345;
	seed = ( seed * p1 +p2 ) % 2147483647;
	return (unsigned) seed / 3;
}

/* =======
   Drawing
   ======= */


static void DrawPlayer(player_p p)
{
	SDL_Rect src, dest;
	int angle;
	

	p -> screen_x = ( int ) p -> world_x - camera_x;
	p -> screen_y = ( int ) p -> world_y - camera_y;


	if (p->screen_x < -PLAYER_WIDTH/2 ||
	    p->screen_x >= SCREEN_WIDTH+PLAYER_WIDTH/2)
		return;
	
	if (p->screen_y < -PLAYER_HEIGHT/2 ||
	    p->screen_y >= SCREEN_HEIGHT+PLAYER_HEIGHT/2)
		return;
	

	angle = p->angle;
	if (angle < 0) angle += 360;
	src.x = PLAYER_WIDTH * (angle / 4);
	src.y = 0;
	src.w = PLAYER_WIDTH;
	src.h = PLAYER_HEIGHT;
	dest.x = p->screen_x - PLAYER_WIDTH/2;
	dest.y = p->screen_y - PLAYER_HEIGHT/2;
	dest.w = PLAYER_WIDTH;
	dest.h = PLAYER_HEIGHT;
	

	SDL_BlitSurface( ship_strip, &src, screen, &dest );
}

/* =============
   Player Update
   ============= */

static void InitPlayer()
{
	printf ( "Initializing player\n" );
	player.world_x = GetRandom() % WORLD_WIDTH;
	player.world_y = GetRandom() % WORLD_HEIGHT;
	player.accel = 0;
	player.velocity = 0;
	player.angle = 0;
	UpdatePlayer(&player);
}


static void InitOpponent()
{
	if (opponent_type == OPP_COMPUTER) {
		opponent.world_x = GetRandom() % WORLD_WIDTH;
		opponent.world_y = GetRandom() % WORLD_HEIGHT;
		opponent.accel = 0;
		opponent.velocity = 0;
		opponent.angle = 0;
	}
	else {	
		/* Nothing yet. This code will be implemented later.*/
	}
}


static void UpdatePlayer(player_p p)
{
	float angle;
	
	angle = ( float ) p -> angle;
	
	p -> velocity += p -> accel * time_scale;
	if ( p -> velocity > PLAYER_MAX_VELOCITY ) p -> velocity = PLAYER_MAX_VELOCITY;
	if ( p -> velocity < PLAYER_MIN_VELOCITY ) p -> velocity = PLAYER_MIN_VELOCITY;
	
	p -> world_x += p -> velocity *  cos( angle * PI / 180.0 ) * time_scale;
	p -> world_y += p -> velocity * -sin( angle * PI / 180.0 ) * time_scale;
				
	if ( p -> world_x < 0 ) p -> world_x = 0;
	if ( p -> world_x >= WORLD_WIDTH ) p -> world_x = WORLD_WIDTH - 1;
	if ( p -> world_y < 0) p -> world_y = 0;
	if ( p -> world_y >= WORLD_HEIGHT) p -> world_y = WORLD_HEIGHT - 1;
}

/* ==============
   Main Game Loop
   ============== */

static void PlayGame()
{
	const Uint8 *keystate;
	int quit = 0;
	int turn;
	int prev_ticks = 0, cur_ticks = 0;

	int start_time, end_time;
	int frames_drawn = 0;
	
	prev_ticks = SDL_GetTicks();
	
	start_time = time(NULL);

	while (quit == 0) {
		
		prev_ticks = cur_ticks;
		cur_ticks = SDL_GetTicks();
		time_scale = ( double )( cur_ticks - prev_ticks ) / 30.0;
				
		SDL_PumpEvents();
		
		keystate = SDL_GetKeyboardState( NULL );
		
		if ( keystate[ SDL_SCANCODE_Q ] || keystate[ SDL_SCANCODE_ESCAPE ] ) quit = 1;
		
		
		turn = 0;
		if ( keystate[ SDL_SCANCODE_LEFT ] ) turn += 15;
		if ( keystate[ SDL_SCANCODE_RIGHT ] ) turn -= 15;
		
		
		player.accel = 0;
		if ( keystate[ SDL_SCANCODE_UP]) player.accel = PLAYER_FORWARD_THRUST;
		if ( keystate[ SDL_SCANCODE_DOWN]) player.accel = PLAYER_REVERSE_THRUST;
		
		
		if ( keystate[ SDL_SCANCODE_SPACE ] ) {
			player.velocity *= 0.8;
		}
		
		
		if ( keystate[ SDL_SCANCODE_E ] ) {
			CreateParticleExplosion( player.world_x,
						 player.world_y,
						 255, 255, 255,
						 10, 300);
			CreateParticleExplosion( player.world_x,
						 player.world_y,
						 255, 0, 0,
						 5, 100);
			CreateParticleExplosion( player.world_x,
						 player.world_y,
						 255, 255, 0,
						 2, 50);
		}
		
		player.angle += turn * time_scale;
		if ( player.angle < 0 ) player.angle += 360;
		if ( player.angle >= 360 ) player.angle -= 360;
		
		UpdatePlayer( &player );
		UpdatePlayer( &opponent );

		camera_x = player.world_x - SCREEN_WIDTH / 2;
		camera_y = player.world_y - SCREEN_HEIGHT / 2;
		
		if (camera_x < 0) camera_x = 0;
		if (camera_x >= WORLD_WIDTH-SCREEN_WIDTH)
			camera_x = WORLD_WIDTH-SCREEN_WIDTH-1;
		if (camera_y < 0) camera_y = 0;
		if (camera_y >= WORLD_HEIGHT-SCREEN_HEIGHT)
			camera_y = WORLD_HEIGHT-SCREEN_HEIGHT-1;
		
		
		UpdateParticles();
				
		
		DrawBackground(screen, camera_x, camera_y);
		DrawParallax(screen, camera_x, camera_y);
		DrawParticles(screen, camera_x, camera_y);
		DrawPlayer(&player);
		DrawPlayer(&opponent);
	
		/* Flip the page. */
		SDL_UpdateTexture( render_texture, NULL, screen -> pixels, screen -> pitch );
		SDL_RenderClear( renderer );
		SDL_RenderCopy( renderer, render_texture, NULL, NULL );
		SDL_RenderPresent( renderer );

		frames_drawn++;

		int frame_ticks = SDL_GetTicks( ) - prev_ticks;
		if ( frame_ticks < TICKS_PER_FRAME ){
			SDL_Delay( TICKS_PER_FRAME - frame_ticks );
		}
	}

	end_time = time(NULL);
	
	if (start_time == end_time) end_time++;

	printf("Drew %i frames in %i seconds, for a framerate of %.2f fps.\n",
	       frames_drawn,
	       end_time-start_time,
	       (float)frames_drawn/(float)(end_time-start_time));
}



int main(int argc, char *argv[])
{
	enum { GAME_COMPUTER, GAME_NETWORK, GAME_UNKNOWN } game_type = GAME_UNKNOWN;
	char *remote_address;
	int i;
	
	if ( argc < 2 ) {
		printf( "Penguin Warrior\n" );
		printf( "Usage: pw [ mode ] [ option ... ]\n" );
		printf( "  Game modes (choose one):\n" );
		printf( "    --computer\n" );
		printf( "    --net <remote ip address>\n" );
		printf( "  Display options, for tweaking and experimenting:\n" );
		printf( "    --fullscreen\n" );
		printf( "    --hwsurface  (use an SDL hardware surface if possible)\n" );
		printf( "    --doublebuf  (use SDL double buffering if possible)\n" );
		printf( "  The display options default to a windowed, software buffer.\n" );
		return 1;
	}

    
	for ( i = 0; i < argc; i++ ) {
		if ( !strcmp(argv[ i ], "--computer" ) ) {
			game_type = GAME_COMPUTER;
			continue;
		}
		else if ( !strcmp( argv[ i ], "--net" ) ) {
			game_type = GAME_NETWORK;
			if ( ++i >= argc) {
				printf("You must supply an IP address for --net.\n");
				return 1;
			}
			remote_address = argv[ i ];
			continue;
			
		}
		else if ( !strcmp( argv[ i ], "--hwsurface" ) ) {
			hwsurface = 1;
		}
		else if ( !strcmp( argv[ i ], "--doublebuf" ) ) {
			doublebuf = 1;
		}
		else if ( !strcmp(argv[ i ], "--fullscreen" ) ) {
			fullscreen = 1;
		}
	}

	switch ( game_type ) {
	case GAME_COMPUTER: 
		opponent_type = OPP_COMPUTER;
		printf( "Playing against the computer.\n" );
		break;  
		
	case GAME_NETWORK:
		printf( "Sorry, network play is not implemented... yet!\n" );
		return 1;
		
	default:
		printf( "You must select a game type.\n" );
		return 1;
	}
	
	InitRandom();
	

	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	atexit(SDL_Quit);
	

	window = SDL_CreateWindow( "Penguin Warrior",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   SCREEN_WIDTH, SCREEN_HEIGHT,
				   SDL_WINDOW_SHOWN );

	if ( !window ) {
		printf( "Unable to create window, %s\n", SDL_GetError() );
		return 1;
	}
		

	renderer = SDL_CreateRenderer( window, -1, 0 );

	if ( !renderer ){
		printf( "Unable to set the renderer, %s\n", SDL_GetError() );
		return 1;
	}
	
	screen = SDL_GetWindowSurface( window );

	if ( !screen ){
		printf( "Unable to set the screen, %s\n", SDL_GetError() );
		return 1;
	}

	render_texture = SDL_CreateTextureFromSurface( renderer, screen );
	
	if ( !render_texture ){
		printf( "Unable to set the screen texture, %s\n", SDL_GetError() );
		return 1;
	}
	
	LoadGameData( &screen );

	InitBackground();
	
	InitPlayer();
	InitOpponent();
	PlayGame();

	
	UnloadGameData();
	
	return 0;
}
