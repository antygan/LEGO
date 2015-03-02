#include "lego.h"
#include <fcntl.h>  //open, close
#include <cstring.h> // memcpy

LEGO_EV3_DEVICE lego_ev3;

LEGO_EV3_SYSTEM_RESULT lego_ev3_reset_device(void) {
	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;

	/* initialize lego motors */
	for(int i=0; i < LEGO_EV3_NUM_MOTOR_PORTS; i++) {
		lego_ev3.motor[i].motor_handle = LEGO_EV3_INVALID_FILE_HANDLE;
		lego_ev3.motor[i].command[MOTOR_TYPE] = opOUTPUT_RESET;
		lego_ev3.motor[i].command[MOTOR_PORT] = LEGO_EV3_MOTOR_PORT_UNKNOWN;
		lego_ev3.motor[i].command[MOTOR_SPEED] = 0; 	
	}

	return result;
}

LEGO_EV3_SYSTEM_RESULT lego_ev3_initialize_device(void) {
	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;

	/* initialize lego motors */
	for(int i=0; i < LEGO_EV3_NUM_MOTOR_PORTS; i++) {
		if( -1 == (lego_ev3.motor[i].motor_handle = open(PWM_DEVICE_NAME, O_WRONLY))) {
			result = LEGO_EV3_INVALID_FILE_HANDLE;
			goto exit;
		}
	}

exit:
	return error;
}

LEGO_EV3_SYSTEM_RESULT lego_ev3_finalize_device(void) {
	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;
	/* close lego motors file handler files */
	for(int i=0; i < LEGO_EV3_NUM_MOTOR_PORTS; i++) {
		if ( -1 != lego_ev3.motor[i].motor_handle) {
			close(lego_ev3.motor[i].motor_handle);
		}
	}

	return result;
}

LEGO_EV3_SYSTEM_RESULT lego_ev3_set_motor_config(const LEGO_EV3_MOTOR_CONFIG motor_config) {
	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;
	unsigned char port = motor_config.motor_command[MOTOR_PORT];

	/* check if motor port is valid */
	if ( (port >= LEGO_EV3_MOTOR_PORT_A) &&
		 (port < LEGO_EV3_NUM_MOTOR_PORTS) ) {
		lego_ev3.motor[port].motor_command[MOTOR_PORT] = 1 << port;
	} else {
		result = LEGO_EV3_UNKNOWN_PORT;
		goto exit;
	}

	/* check if the file handler is valid */
	if ( LEGO_EV3_INVALID_FILE_HANDLE != motor_config.motor_handle ) {
		lego_ev3.motor[port].motor_handle = motor_config.motor_handle;
	} else {
		result = LEGO_EV3_UNKNOWN_FILE_HANDLE;
		goto exit;
	}
	
	/* set the port type */
	lego_ev3.motor[port].motor_command[MOTOR_TYPE] =
			 motor_config.motor_command[MOTOR_TYPE];

	/* set the speed */
	lego_ev3.motor[port].motor_command[MOTOR_SPEED] =
		 motor_config.motor_command[MOTOR_SPEED] % LEGO_EV3_MAX_MOTOR_SPEED;
	
exit:
	return result;
         
}

LEGO_EV3_SYSTEM_RESULT lego_ev3_get_motor_config(const LEGO_EV3_MOTOR_PORT motor_port,
				LEGO_EV3_MOTOR_CONFIG* motor_config) {
	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;
	motor_config = NULL;

	if ((motor_port >= LEGO_EV3_MOTOR_PORT_A) &&
		(motor_port < LEGO_EV3_NUM_MOTOR_PORTS)) {
		motor_config = lego_ev3.motor[motor_port];
	} else {
		result = LEGO_EV3_UNKNOWN_PORT;
	}

	return result;
}

LEGO_EV3_SYSTEM_RESULT lego_ev3_set_motor_speed(const LEGO_EV3_MOTOR_PORT motor_port,				const char motor_speed) {

	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;

	if ((motor_port >= LEGO_EV3_MOTOR_PORT_A) &&
		(motor_port < LEGO_EV3_NUM_MOTOR_PORTS)) {
		lego_ev3.motor[motor_port].command[MOTOR_SPEED] =
					 motor_speed % LEGO_EV3_MAX_MOTOR_SPEED;
	} else {
		result = LEGO_EV3_UNKNOWN_PORT;
	}

	return result;
}

