#ifndef __LEGO_H
#define __LEGO_H

#include "lmstypes.h"
#include "lms2012.h"
#include "bytecodes.h"

#define LEGO_NUM_MOTOR_PORTS        4

typedef enum __LEGO_MOTOR_COMMAND_INDEX {
	MOTOR_TYPE,
	MOTOR_PORT,
	MOTOR_SPEED,
	MOTOR_INDEX
};

typedef struct _LEGO_MOTOR_PORTS {
	LEGO_MOTOR_PORT_UNKNOWN = 0,
	LEGO_MOTOR_PORT_A = 0x1,
	LEGO_MOTOR_PORT_B = 0x2,
	LEGO_MOTOR_PORT_C = 0x4,
	LEGO_MOTOR_PORT_D = 0x8,
} LEGO_MOTOR_PORT;

typedef struct _LEGO_SYSTEM_ERRORS {
	LEGO_INVALID_FILE_HANDLE = -1,
	LEGO_UNKNOWN_ERROR = 0x12215,
} LEGO_SYSTEM_ERRORS;

typedef struct _LEGO_MOTOR {
	int motor_handle;
	char motor_command[MOTOR_INDEX];
} LEGO_MOTOR;

typedef struct _LEGO_DEVICE {
	LEGO_MOTOR motor[LEGO_NUM_MOTOR_PORTS];	
} LEGO_DEVICE; 

#endif /* __LEGO_H */
