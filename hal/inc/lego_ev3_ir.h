#ifndef __LEGO_EV3_IR_H
#define __LEGO_EV3_IR_H

typedef enum __LEGO_EV3_IR_MODE {
	LEGO_EV3_IR_MODE_PROXIMITY,
	LEGO_EV3_IR_MODE_BEACON,
	LEGO_EV3_IR_MODE_REMOTE
} LEGO_EV3_IR_MODE;

typedef struct _LEGO_EV3_IR_CONFIG {
	int ir_handle;
	LEGO_EV3_INPUT_PORT ir_port;
	LEGO_EV3_IR_MODE ir_mode;
} LEGO_EV3_IR_CONFIG;

typedef struct __LEGO_EV3_IR_DATA {
	char distance;
	char angle;
} LEGO_EV3_IR_DATA;

LEGO_EV3_SYSTEM_RESULT lego_ev3_set_ir_config(const LEGO_EV3_IR_CONFIG ir_config);

LEGO_EV3_SYSTEM_RESULT lego_ev3_get_ir_config(const LEGO_EV3_IR_PORT ir_port,
				LEGO_EV3_IR_CONFIG* ir_config);

LEGO_EV3_SYSTEM_RESULT lego_ev3_get_ir_data(const LEGO_EV3_MOTOR_PORT ir_port,
				LEGO_EV3_IR_DATA *ir_speed);
#endif
