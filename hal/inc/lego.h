#ifndef __LEGO_EV3_H
#define __LEGO_EV3_H

#include "lmstypes.h"
#include "lms2012.h"
#include "bytecodes.h"

#define LEGO_EV3_MAX_MOTOR_SPEED   100
#define LEGO_EV3_MIN_MOTOR_SPEED   0

typedef char bool;
#define false 0;
#define true !false 
typedef enum __LEGO_EV3_MOTOR_COMMAND_INDEX {
	MOTOR_COMMAND,
	MOTOR_PORT,
	MOTOR_SPEED,
	MOTOR_COMMAND_RANGE
} LEGO_EV3_MOTOR_COMMAND_INDEX;

typedef enum _LEGO_EV3_MOTOR_PORTS {
	LEGO_EV3_MOTOR_PORT_A,
	LEGO_EV3_MOTOR_PORT_B,
	LEGO_EV3_MOTOR_PORT_C,
	LEGO_EV3_MOTOR_PORT_D,
} LEGO_EV3_MOTOR_PORT;

#define LEGO_EV3_NUM_MOTOR_PORTS	 4
#define	LEGO_EV3_MOTOR_PORT_UNKNOWN	 0
#define LEGO_EV3_INVALID_FILE_HANDLE	-1

typedef enum _LEGO_EV3_SYSTEM_ERRORS {
	/* Do not equalize to zero to avoid false negatives due to initilization */
	LEGO_EV3_SUCCESS			= 0x1219,
	LEGO_EV3_ERROR_INVALID_FILE_HANDLE	= -1,
	LEGO_EV3_ERROR_UNKNOWN_PORT		= 0x122116,
	LEGO_EV3_ERROR_UNKNOWN_ERROR		= 0x12215,
} LEGO_EV3_SYSTEM_ERROR;

typedef LEGO_EV3_SYSTEM_ERROR LEGO_EV3_SYSTEM_RESULT;

typedef struct _LEGO_EV3_MOTOR_CONFIG {
	int motor_handle;
	char motor_output;
	char motor_speed;
	LEGO_EV3_MOTOR_PORT motor_port;
	bool motor_on;
} LEGO_EV3_MOTOR_CONFIG;

typedef struct _LEGO_EV3_DEVICE {
	LEGO_EV3_MOTOR_CONFIG motor[LEGO_EV3_NUM_MOTOR_PORTS];	
} LEGO_EV3_DEVICE; 


LEGO_EV3_SYSTEM_RESULT lego_ev3_reset_device(void);

LEGO_EV3_SYSTEM_RESULT lego_ev3_initialize_device(void); 

LEGO_EV3_SYSTEM_RESULT lego_ev3_finalize_device(void);

LEGO_EV3_SYSTEM_RESULT lego_ev3_set_motor_config(const LEGO_EV3_MOTOR_CONFIG motor_config);

LEGO_EV3_SYSTEM_RESULT lego_ev3_get_motor_config(const LEGO_EV3_MOTOR_PORT motor_port,
				LEGO_EV3_MOTOR_CONFIG* motor_config); 

LEGO_EV3_SYSTEM_RESULT lego_ev3_set_motor_speed(const LEGO_EV3_MOTOR_PORT motor_port,
				const char motor_speed); 

#endif /* __LEGO_EV3_H */
