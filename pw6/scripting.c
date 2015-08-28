#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tcl.h>
#include "scripting.h"


static Tcl_Interp *interp = NULL;


static int HandleFireWeaponCmd( ClientData client_data,
			        Tcl_Interp * interp,
			        int objc,
			        Tcl_Obj * CONST objv[] );



extern player_t player;
extern player_t opponent;


void InitScripting(void)
{
	interp = Tcl_CreateInterp();
	if ( interp == NULL ) {
		fprintf( stderr, "Unable to initialize Tcl.\n" );
		exit( 1 );
	}
	
	
	if ( Tcl_CreateObjCommand( interp, "fireWeapon",
				   HandleFireWeaponCmd, ( ClientData ) 0,
				   NULL ) == NULL) {
		fprintf( stderr, "Error creating Tcl command.\n" );
		exit(1);
	}

	
	Tcl_LinkVar( interp, "player_x", ( char * ) &player.world_x,
		     TCL_LINK_DOUBLE );
	Tcl_LinkVar( interp, "player_y", ( char * ) &player.world_y,
		     TCL_LINK_DOUBLE );
	Tcl_LinkVar( interp, "player_angle", ( char * ) &player.angle,
		     TCL_LINK_DOUBLE );
	Tcl_LinkVar( interp, "player_accel", ( char * ) &player.accel,
		     TCL_LINK_DOUBLE );
	Tcl_LinkVar( interp, "computer_x", ( char * ) &opponent.world_x,
		     TCL_LINK_DOUBLE );
	Tcl_LinkVar( interp, "computer_y", ( char * ) &opponent.world_y,
		     TCL_LINK_DOUBLE );
	Tcl_LinkVar( interp, "computer_angle", ( char * ) &opponent.angle,
		     TCL_LINK_DOUBLE );
	Tcl_LinkVar( interp, "computer_accel", ( char * ) &opponent.accel,
		     TCL_LINK_DOUBLE );

	
	Tcl_SetVar2Ex( interp, "world_width", NULL, Tcl_NewIntObj( WORLD_WIDTH ), 0);

	Tcl_SetVar2Ex( interp, "world_height", NULL,
		       Tcl_NewIntObj( WORLD_HEIGHT ), 0);
	Tcl_SetVar2Ex( interp, "player_forward_thrust", NULL,
		       Tcl_NewIntObj( PLAYER_FORWARD_THRUST ), 0);
	Tcl_SetVar2Ex( interp, "player_reverse_thrust", NULL,
		       Tcl_NewIntObj( PLAYER_REVERSE_THRUST ), 0);
}


void CleanupScripting(void)
{
	if ( interp != NULL ) {
		Tcl_DeleteInterp( interp );
	}
}



int LoadGameScript( char *filename )
{
	int status;
	
	status = Tcl_EvalFile( interp, filename );
	if ( status != TCL_OK ) {
		fprintf( stderr, "Error executing %s: %s\n",
			 filename,
			 Tcl_GetStringResult( interp ) );
		return -1;
	}
	
	return 0;
}


static int HandleFireWeaponCmd(ClientData client_data,
			       Tcl_Interp *interp,
			       int objc,
			       Tcl_Obj * CONST objv[ ] )
{
	objc += 0;
	objv += 0;
	//client_data += 0;
	

	fprintf(stderr, "Computer is firing weapon. This doesn't work yet.\n");
	

	Tcl_ResetResult( interp );
	

	return TCL_OK;
}


int RunGameScript( )
{
	int status;
	

	status = Tcl_Eval( interp, "playComputer" );
	if (status != TCL_OK) {
		fprintf( stderr, "Error in script: %s\n",
			 Tcl_GetStringResult(interp));
		return -1;
	}
	

	if ( opponent.accel > PLAYER_FORWARD_THRUST ){
		opponent.accel = PLAYER_FORWARD_THRUST;
	}
	
	if ( opponent.accel < PLAYER_REVERSE_THRUST ){
		opponent.accel = PLAYER_REVERSE_THRUST;
	}
	
	while ( opponent.angle >= 360) {
		opponent.angle -= 360;
	}
	while ( opponent.angle < 0) {
		opponent.angle += 360;
	}
	
	return 0;
}

