#ifdef WINDOWS
#include<SDL.h>
#else
#include<SDL/SDL.h>
#endif

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


#define MAX_PLAYING_SOUNDS 10
#define VOLUME_PER_SOUND SDL_MIX_MAXVOLUME * 0.7
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256


struct sound{
	Uint8 *samples;
	Uint32 length;
};


struct playing{
	int active;
	struct sound* sound;
	Uint32 position;
};


struct playing playing[ MAX_PLAYING_SOUNDS ];


void AudioCallBack( void *, Uint8 *, int );

int LoadAndConvertSound( char*, SDL_AudioSpec *, struct sound * );

void ClearPlayingSounds( void );

int PlaySound( struct sound * );

int main( int argc, char **argv )
{
	SDL_Window *window = NULL;
	SDL_Surface *screen = NULL;

	SDL_Event event;

	int quit_flag = 0;

	SDL_AudioSpec desired;
	SDL_AudioSpec obtained;

	struct sound cannon;
	struct sound explosion;

	if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ){
		printf( "Unable to initialize SDL: %s\n", SDL_GetError() );
	}

	atexit( SDL_Quit );

	atexit( SDL_CloseAudio );

	window = SDL_CreateWindow( "SDL Sound demo.",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   SCREEN_WIDTH, SCREEN_HEIGHT,
				   SDL_WINDOW_SHOWN );

	if ( !window ){
		printf( "Unable to set the Main Window. %s\n",
			SDL_GetError() );
		return 1;
	}
		
	screen = SDL_GetWindowSurface( window );

	if ( !screen ){
		printf( "Unable to set the screen. %s\n",
		       SDL_GetError() );
	}
	
	SDL_zero( desired );
	desired.freq = 44100;
	desired.format = AUDIO_S16;
	desired.samples = 4096;
	desired.channels = 2;
	desired.callback = AudioCallBack;
	desired.userdata = NULL;
	SDL_zero( obtained );
	
	if ( !SDL_OpenAudioDevice( NULL, 0, &desired, &obtained, SDL_AUDIO_ALLOW_FORMAT_CHANGE ) ){
		printf( "Unable to open audio device: %s\n", SDL_GetError()  );
		return 1;
	}
	
	if ( LoadAndConvertSound( "media/cannon.wav", &obtained, &cannon ) != 0 ){
		printf( "Unable to load sound.\n" );
		return 1;
	}

	if ( LoadAndConvertSound( "media/explosion.wav", &obtained, &explosion ) != 0 ){
		printf( "Unable to load sound.\n" );
		return 1;
	}

	ClearPlayingSounds();
	SDL_PauseAudio( 0 );
	
	printf( "Press 'Q' to quit. C an E play sounds.\n" );

	
	while( SDL_WaitEvent( &event ) != 0 && quit_flag == 0 ){
		SDL_Keysym keysym;
		switch ( event.type ){
			
		case SDL_KEYDOWN:
			keysym = event.key.keysym;
			if ( keysym.sym == SDLK_q ){
				printf( "'Q' pressed, exiting.\n" );
				quit_flag = 1 ;
			}

			if ( keysym.sym == SDLK_c ){
				printf( "Firing cannon!\n" );
				PlaySound( &cannon );
			}

			if ( keysym.sym == SDLK_e ){
				printf( "Kaboom!\n" );
				PlaySound( &explosion );
			}
			
			break;
		case SDL_QUIT:
			printf( "Quit event. Bye.\n" );
			quit_flag = 1;
		}
	}
       
	
	SDL_PauseAudio( 1 );
	SDL_LockAudio( );

	free( cannon.samples );
	free( explosion.samples );

	SDL_UnlockAudio();
	SDL_DestroyWindow( window );
	
	return 0;
}

void AudioCallBack( void *user_data, Uint8 *audio, int length )
{
	int i = 0;

	memset( audio, 0, length );

	for ( i = 0; i < MAX_PLAYING_SOUNDS; i ){
		/*Locate this sound's current buffer position*/
		if ( playing[ i ].active ){
			Uint8 *sound_buf;
			Uint32 sound_len;

			sound_buf = playing[ i ].sound -> samples;
			sound_buf += playing[ i ].position;
		
			/*Determine the number of samples to mix*/
			if ( ( playing[ i ].position + length ) > playing[ i ].sound -> length ){
				sound_len = playing[ i ].sound -> length - playing[ i ].position;
			}
			else{
				sound_len = length;
			}
		
	
			SDL_MixAudio( audio, sound_buf, sound_len, VOLUME_PER_SOUND );
		
			playing[ i ].position += length;

			if ( playing[ i ].position >= playing[ i ].sound -> length ){
				playing[ i ].active = 0;
			}
		}
	}
}

     
int LoadAndConvertSound( char* filename, SDL_AudioSpec *spec, struct sound * sound )
{
	SDL_AudioCVT cvt;
	SDL_AudioSpec loaded;

	Uint8 *new_buf;

	if ( SDL_LoadWAV( filename, &loaded, &sound -> samples, &sound -> length ) == NULL ){
		printf ( "Unable to load sound: %s\n", SDL_GetError() );
		return 1;
	}

	if ( SDL_BuildAudioCVT( &cvt,
				loaded.format,
				loaded.channels,
				loaded.freq,
				spec -> format,
				spec -> channels,
				spec -> freq ) < 0 ){
		printf( "Unable to convert sound: %s\n", SDL_GetError( ) );
		return 1;
	}

	cvt.len = sound -> length;
	new_buf = ( Uint8 * ) malloc( cvt.len * cvt.len_mult );

	if ( new_buf == NULL ){
		printf( "Memory allocation failed.\n" );
		SDL_FreeWAV( sound -> samples );
		return 1;
	}

	memcpy( new_buf, sound -> samples, sound -> length );

	cvt.buf = new_buf;

	if ( SDL_ConvertAudio( &cvt ) < 0 ){
		printf( "Audio conversion error: %s\n", SDL_GetError() );
		free( new_buf );
		SDL_FreeWAV( sound -> samples );
		return 1;
	}

	SDL_FreeWAV( sound -> samples );
	sound -> samples = new_buf;
	sound -> length = sound -> length * cvt.len_mult;

	printf( "'%s' was loaded and converted successfully.\n", filename );

	return 0;
}

void ClearPlayingSounds( void )
{
	int i;
	for ( i = 0; i < MAX_PLAYING_SOUNDS; i ++ ){
		playing[ i ].active = 0;
	}
}


int PlaySound( struct sound * sound )
{
	int i = 0;

	for ( i = 0; i < MAX_PLAYING_SOUNDS; i ++ ){
		if ( playing[ i ].active == 0 ) {
			break;
		}
	}

	if ( i == MAX_PLAYING_SOUNDS ){
		return 1;
	}

	SDL_LockAudio();
	playing[ i ].active = 1;
	playing[ i ].sound = sound;
	playing[ i ].position = 0;

	SDL_UnlockAudio();

	return 0;
}

