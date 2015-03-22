#include "lego.h"
#include "lego_ev3_motor.h"
#include <string.h>

extern LEGO_EV3_DEVICE lego_ev3;

LEGO_EV3_SYSTEM_RESULT lego_ev3_set_motor_config(const LEGO_EV3_MOTOR_CONFIG motor_config) {

	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;
	char command[MOTOR_COMMAND_RANGE] = {0};
	unsigned char port = motor_config.motor_port;

	/* check if motor port is valid */
	if ( (port >= LEGO_EV3_MOTOR_PORT_A) &&
		 (port < LEGO_EV3_NUM_MOTOR_PORTS) ) {
		command[MOTOR_PORT] = port;
	} else {
		result = LEGO_EV3_ERROR_UNKNOWN_PORT;
		goto exit;
	}

	if (lego_ev3.motor[port].motor_handle != LEGO_EV3_INVALID_FILE_HANDLE) {

		/* set the port type */
		lego_ev3.motor[port].motor_output =
				 motor_config.motor_output;

		/* set the speed */
		lego_ev3.motor[port].motor_speed =
			 motor_config.motor_speed % LEGO_EV3_MAX_MOTOR_SPEED;
	
		command[MOTOR_COMMAND] = motor_config.motor_output;
		command[MOTOR_SPEED] = lego_ev3.motor[port].motor_output;

		/* write the configuration */
		write(lego_ev3.motor[port].motor_handle,
			 command, 3);
	} else {
		result = LEGO_EV3_ERROR_INVALID_FILE_HANDLE;
		goto exit;
	}

	
exit:
	return result;
         
}

LEGO_EV3_SYSTEM_RESULT lego_ev3_get_motor_config(const LEGO_EV3_MOTOR_PORT motor_port,
				LEGO_EV3_MOTOR_CONFIG* motor_config) {
	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;

	if ((motor_port >= LEGO_EV3_MOTOR_PORT_A) &&
		(motor_port < LEGO_EV3_NUM_MOTOR_PORTS)) {
		memcpy(motor_config, &lego_ev3.motor[motor_port],
				 sizeof(LEGO_EV3_MOTOR_CONFIG));
	} else {
		result = LEGO_EV3_ERROR_UNKNOWN_PORT;
	}

	return result;
}

LEGO_EV3_SYSTEM_RESULT lego_ev3_set_motor_speed(const LEGO_EV3_MOTOR_PORT motor_port,				const char motor_speed) {

	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;
	char command[MOTOR_COMMAND_RANGE] = {0};

	if ((motor_port >= LEGO_EV3_MOTOR_PORT_A) &&
		(motor_port < LEGO_EV3_NUM_MOTOR_PORTS)) {
		lego_ev3.motor[motor_port].motor_speed =
					 motor_speed % LEGO_EV3_MAX_MOTOR_SPEED;
		command[MOTOR_PORT] = 1 << motor_port;
		command[MOTOR_COMMAND] = lego_ev3.motor[motor_port].motor_output;
		command[MOTOR_SPEED] = lego_ev3.motor[motor_port].motor_speed;

		write(lego_ev3.motor[motor_port].motor_handle,
			 command, 3);

		if (motor_speed != 0) {
			command[MOTOR_COMMAND] = opOUTPUT_START;
			lego_ev3.motor[motor_port].motor_on = true;
		} else {
			command[MOTOR_COMMAND] = opOUTPUT_STOP;
			lego_ev3.motor[motor_port].motor_on = false;
		}

		write(lego_ev3.motor[motor_port].motor_handle,
			 command, 2);
	} else {
		result = LEGO_EV3_ERROR_UNKNOWN_PORT;
	}

	return result;
}


