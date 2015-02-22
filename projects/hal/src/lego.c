#include "lego.h"
#include <cstring.h>

LEGO_DEVICE lego_ev3;

LEGO_SYSTEM_ERRORS initialize_lego_ev3() {
	LEGO_SYSTEM_ERRORS error = LEGO_UNKNOWN_ERROR;

	/* initialize lego motors */
	for(int i=0; i < LEGO_NUM_MOTOR_PORTS; i++) {
		lego_ev3.motor.motor_handle = LEGO_INVALID_FILE_HANDLE;
		lego_ev3.motor.command[MOTOR_TYPE] = opOUTPUT_RESET;
		lego_ev3.motor.command[MOTOR_PORT] = LEGO_MOTOR_PORT_UNKNOWN;
		lego_ev3.motor.command[MOTOR_SPEED] = 0; 	
	}
}
