#ifndef __LEGO_EV3_H
#define __LEGO_EV3_H

#include "lmstypes.h"
#include "lms2012.h"
#include "bytecodes.h"
#include "lego_ev3_system.h"

/* lego ev3 device headers */
#include "lego_ev3_motor.h"
#include "lego_ev3_ir.h"


typedef struct _LEGO_EV3_DEVICE {
	LEGO_EV3_MOTOR_CONFIG motor[LEGO_EV3_NUM_MOTOR_PORTS];	
} LEGO_EV3_DEVICE; 


LEGO_EV3_SYSTEM_RESULT lego_ev3_reset_device(void);

LEGO_EV3_SYSTEM_RESULT lego_ev3_initialize_device(void); 

LEGO_EV3_SYSTEM_RESULT lego_ev3_finalize_device(void);


#endif /* __LEGO_EV3_H */
