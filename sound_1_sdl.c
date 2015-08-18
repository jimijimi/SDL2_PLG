#ifdef WINDOWS
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#else
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#endif

#include<stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void Init();
void LoadMedia();
void Close();

SDL_Window* window = NULL;

SDL_Renderer* renderer = NULL;

Mix_Chunk *explosion = NULL;
Mix_Chunk *cannon = NULL;

void Init()
{

	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ){
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		exit( 1 );
	}

	window = SDL_CreateWindow( "SDL Sound", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( !window ){
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		exit( 1 );
	}
	
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( !renderer ){
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		exit( 1 );
		}
	
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	
		
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		exit( 1 );
	}
	
	printf( "Init OK\n" );
}




void LoadMedia( void )
{
	explosion = Mix_LoadWAV( "media/explosion.wav" );
	if( !explosion ){
		printf( "Failed to load explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		exit( 1 );
	}
	
	cannon = Mix_LoadWAV( "media/cannon.wav" );
	if( !cannon )
	{
		printf( "Failed to load cannon effect! SDL_mixer Error: %s\n", Mix_GetError() );
		exit( 1 );
	}

	printf( "Load media OK\n" );
}

void close()
{
	printf( "Shutting down SDL\n" );
	Mix_FreeChunk( cannon );
	Mix_FreeChunk( explosion );

	cannon = NULL;
	explosion = NULL;
	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
}

int main( int argc, char** argv )
{
	Init();

	atexit( SDL_Quit );
	atexit( SDL_CloseAudio );
	atexit( Mix_Quit );

	
	LoadMedia( );

	int quit = 0;
	
	SDL_Event e;
	
	while( SDL_WaitEvent( &e ) != 0 && !quit ){
		SDL_Keysym keysym;
		if( e.type == SDL_QUIT ){
			quit = 1;
		}
		else if( e.type == SDL_KEYDOWN ){
			switch( e.key.keysym.sym ){
			case SDLK_q:
				printf( "'Q' pressed, exiting.\n"  );
				quit = 1;
				break;
			case SDLK_c:
				Mix_PlayChannel( -1, cannon, 0 );
				break;
			case SDLK_e:
				Mix_PlayChannel( -1, explosion, 0 );
				break;
			}
		}
	}
	
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
	SDL_RenderPresent( renderer );
	close();
	
	return 0;
}

