#include <stdio.h>
#include "lego.h"

extern LEGO_EV3_DEVICE lego_ev3;
int main() {
	
	int ret_val = 0;
#if 1
	LEGO_EV3_MOTOR_CONFIG motor_config_left, motor_config_right;

	/* reset the lego ev3 environment */
	if (LEGO_EV3_SUCCESS != lego_ev3_reset_device()) {
		ret_val = -1;
		goto exit;
	}
	/* initialize lego ev3 environment */
	if (LEGO_EV3_SUCCESS != lego_ev3_initialize_device()) {
		ret_val = -1;
		goto exit;
	}

	lego_ev3_get_motor_config(LEGO_EV3_MOTOR_PORT_A, &motor_config_left);
	lego_ev3_get_motor_config(LEGO_EV3_MOTOR_PORT_C, &motor_config_right);


	/* start the motors */
	lego_ev3_set_motor_speed(LEGO_EV3_MOTOR_PORT_A, 30);	
	lego_ev3_set_motor_speed(LEGO_EV3_MOTOR_PORT_D, 30);	
	sleep(2);

	lego_ev3_set_motor_speed(LEGO_EV3_MOTOR_PORT_A, 0);	
	lego_ev3_set_motor_speed(LEGO_EV3_MOTOR_PORT_D, 0);	

	lego_ev3_finalize_device();

#endif
#if 0
	char command[3];
	int handle;

	if ((handle = open(PWM_DEVICE_NAME, O_WRONLY)) == -1) {
		ret_val = -1;
		goto exit;
	}
	
	/* for left motor */
	command[0] = opOUTPUT_POWER;
	command[1] = 0x01;
	command[2] = -128;
	write(handle, command, 3);
	
	/* for right motor */
	command[0] = opOUTPUT_POWER;
	command[1] = 0x08;
	command[2] = -128;
	write(handle, command, 3);
	
	/* start the motors */
	command[0] = opOUTPUT_START;
	write(handle, command, 2);
	command[1] = 0x01;
	write(handle, command, 2);

	sleep(4);
	
	command[0] = opOUTPUT_STOP;
	write(handle, command, 2);	
	command[1] = 0x08;
	write(handle, command, 2);	

	close(handle);

#endif
#if 0
	char command[3];
	int handle;

	if ((handle = open(PWM_DEVICE_NAME, O_WRONLY)) == -1) {
		ret_val = -1;
		goto exit;
	}
	
	/* for left motor */
	command[0] = opOUTPUT_POWER;
	command[1] = 0x01;
	command[2] = -10;
	write(handle, command, 3);
	
	/* start the motors */
	command[0] = opOUTPUT_START;
	write(handle, command, 2);
	sleep(4);

	command[0] = opOUTPUT_POWER;
	command[1] = 0x01;
	command[2] = -50;
	write(handle, command, 3);
	command[0] = opOUTPUT_START;
	write(handle, command, 3);
	sleep(4);

	command[0] = opOUTPUT_POWER;
	command[1] = 0x01;
	command[2] = -0;
	write(handle, command, 3);
	command[0] = opOUTPUT_START;
	write(handle, command, 3);
	sleep(4);

	
	command[0] = opOUTPUT_STOP;
	write(handle, command, 2);	

	close(handle);
#endif 
exit:
	return ret_val;
}

