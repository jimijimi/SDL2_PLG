#ifdef WINDOWS
#include<SDL.h>
#include<SDL_opengl.h>
#else
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>
#endif

#include<GL/glu.h>
#include<stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int main( int argc, char **argv )
{
	
	SDL_Window* window = NULL;

	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		printf( "Unable to initialize SDL: %s\n",
			SDL_GetError() );
		return 1;
	}

	atexit( SDL_Quit );

	window = SDL_CreateWindow( "OpenGL with SDL2",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   SCREEN_WIDTH, SCREEN_HEIGHT,
				   SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );

	if ( !window ){
		printf( "Unable to create window, %s\n",
			SDL_GetError() );
		return 1;
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext( window );

	if ( !glcontext ){

		printf( "Unable to create context, %s\n",
			SDL_GetError() );
		return 1;
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 6 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );

	glViewport( 80, 0, 480, 480 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -1.0, 1.0, -1.0, 1.0, 1.0, 100.0 );
	glClearColor( 0, 0, 0, 0 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT );

	glBegin( GL_TRIANGLES );
	glColor3f( 1.0, 0.0, 0.0 );
	glVertex3f( 0.0, 1.0, -2.0 );
	glColor3f( 0.0, 1.0, 0.0 );
	glVertex3f( 1.0, -1.0, -2.0 );
	glColor3f( 0.0, 0.0, 1.0 );
	glVertex3f( -1.0, -1.0, -2.0 );
	glEnd();

	glFlush();
	SDL_GL_SwapWindow( window );
	SDL_Delay( 5000 );
	
	SDL_GL_DeleteContext( glcontext );
	
	return 0;
}
