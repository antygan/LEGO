#include "lego.h"

int main() {
	
	int ret_val = 0;
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
	motor_config_left.motor_command[MOTOR_COMMAND] = opOUTPUT_SPEED;
	motor_config_left.motor_command[MOTOR_PORT] = LEGO_EV3_MOTOR_PORT_A;
	motor_config_left.motor_command[MOTOR_SPEED] = 30;
	motor_config_right.motor_command[MOTOR_COMMAND] = opOUTPUT_SPEED;
	motor_config_right.motor_command[MOTOR_PORT] = LEGO_EV3_MOTOR_PORT_B;
	motor_config_right.motor_command[MOTOR_SPEED] = 30;
	lego_ev3_set_motor_config(motor_config_left);
	lego_ev3_set_motor_config(motor_config_right);

	lego_ev3_set_motor_speed(LEGO_EV3_MOTOR_PORT_A, 30);	
	lego_ev3_set_motor_speed(LEGO_EV3_MOTOR_PORT_B, 30);	
	
	sleep(2);

	lego_ev3_set_motor_speed(LEGO_EV3_MOTOR_PORT_A, 0);	
	lego_ev3_set_motor_speed(LEGO_EV3_MOTOR_PORT_B, 0);	

	lego_ev3_finalize_device();

exit:
	return ret_val;
}

