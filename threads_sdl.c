/* SLD threads 
   Ported to SDL2 by Jaime Ortiz
   See COPYING file for license information
*/


#ifdef WINDOWS
#include <SDL.h>
#include <SDL_thread.h>
#else
#define <SDL/SDL.h>
#define <SDL/SDL_thread.h>
#endif
#include <stdio.h>
#include <stdlib.h>


static int counter = 0;
SDL_mutex *counter_mutex;

static int exit_flag = 0;

int ThreadEntryPoint( void * );

int main ( int argc, char **argv )
{
	SDL_Thread *thread_1;
	SDL_Thread *thread_2;
	SDL_Thread *thread_3;

	counter_mutex = SDL_CreateMutex();

	printf( "Press Ctrl-C to exit the program.\n" );

	thread_1 = SDL_CreateThread( ThreadEntryPoint, "Thread 1", "Thread 1" );
	thread_2 = SDL_CreateThread( ThreadEntryPoint, "Thread 2", "Thread 2" );
	thread_3 = SDL_CreateThread( ThreadEntryPoint, "Thread 3", "Thread 3" );

	while ( counter < 20 ){
		SDL_Delay( 1000 );
	}

	exit_flag = 1;

	printf( "exit_flag has been set by main().\n" );

	SDL_Delay( 3500 );

	SDL_DestroyMutex( counter_mutex );
			
	return 0;
}

int ThreadEntryPoint( void *data )
{
	char *thread_name;
	thread_name = ( char* ) data;

	while ( !exit_flag ){
		printf( "This is %s\n", thread_name );

		SDL_mutexP( counter_mutex );

		printf( "The counter is currently %i\n", counter );

		counter ++;

		SDL_mutexV( counter_mutex );

		SDL_Delay( rand() % 3000 );
	}

	printf( "%s is now exiting. \n", thread_name );

	return;
}
