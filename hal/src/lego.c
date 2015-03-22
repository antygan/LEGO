#include "lego.h"
#include <fcntl.h>  //open, close

LEGO_EV3_DEVICE lego_ev3;

LEGO_EV3_SYSTEM_RESULT lego_ev3_reset_device(void) {
	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;
	int i = 0;
	/* initialize lego motors */
	for(i=0; i < LEGO_EV3_NUM_MOTOR_PORTS; i++) {
		lego_ev3.motor[i].motor_handle = LEGO_EV3_ERROR_INVALID_FILE_HANDLE;
		lego_ev3.motor[i].motor_output = opOUTPUT_RESET;
		lego_ev3.motor[i].motor_port =  LEGO_EV3_MOTOR_PORT_UNKNOWN;
		lego_ev3.motor[i].motor_speed = 0;
		lego_ev3.motor[i].motor_on = false;
	}

	return result;
}

LEGO_EV3_SYSTEM_RESULT lego_ev3_initialize_device(void) {
	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;
	int i = 0;  
	/* initialize lego motors */
	for(i=0; i < LEGO_EV3_NUM_MOTOR_PORTS; i++) {
		if( -1 == (lego_ev3.motor[i].motor_handle = open(PWM_DEVICE_NAME, O_WRONLY))) {
			result = LEGO_EV3_ERROR_INVALID_FILE_HANDLE;
			goto exit;
		}
		lego_ev3.motor[i].motor_output = opOUTPUT_SPEED;
		lego_ev3.motor[i].motor_port =  i;
	}

exit:
	return result;
}

LEGO_EV3_SYSTEM_RESULT lego_ev3_finalize_device(void) {
	int i = 0;
	LEGO_EV3_SYSTEM_RESULT result = LEGO_EV3_SUCCESS;
	/* close lego motors file handler files */
	for(i=0; i < LEGO_EV3_NUM_MOTOR_PORTS; i++) {
		if ( -1 != lego_ev3.motor[i].motor_handle) {
			close(lego_ev3.motor[i].motor_handle);
		}
	}

	result = lego_ev3_reset_device();

	return result;
}

