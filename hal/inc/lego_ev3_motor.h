#ifndef __LEGO_EV3_MOTOR_H
#define __LEGO_EV3_MOTOR_H

#include "lego_ev3_system.h"

#define LEGO_EV3_MAX_MOTOR_SPEED   100
#define LEGO_EV3_MIN_MOTOR_SPEED   0

typedef enum __LEGO_EV3_MOTOR_COMMAND_INDEX {
	MOTOR_COMMAND,
	MOTOR_PORT,
	MOTOR_SPEED,
	MOTOR_COMMAND_RANGE
} LEGO_EV3_MOTOR_COMMAND_INDEX;

typedef struct _LEGO_EV3_MOTOR_CONFIG {
	int motor_handle;
	char motor_output;
	char motor_speed;
	LEGO_EV3_OUTPUT_PORT motor_port;
	bool motor_on;
} LEGO_EV3_MOTOR_CONFIG;

LEGO_EV3_SYSTEM_RESULT lego_ev3_set_motor_config(const LEGO_EV3_MOTOR_CONFIG motor_config);

LEGO_EV3_SYSTEM_RESULT lego_ev3_get_motor_config(const LEGO_EV3_OUTPUT_PORT motor_port,
				LEGO_EV3_MOTOR_CONFIG* motor_config); 

LEGO_EV3_SYSTEM_RESULT lego_ev3_set_motor_speed(const LEGO_EV3_MOTOR_PORT motor_port,
				const char motor_speed); 
#endif /* __LEGO_EV3_MOTOR_H */
