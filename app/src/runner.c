#include <stdio.h>
#include <fcntl.h>  //open, close
#include "lego.h"
#include "lego_ev3_motor.h"
#include "lego_ev3_ir.h"
#include <sys/mman.h>
#include <sys/ioctl.h>



//Runtime constants
const int MAX_SAMPLES  = 100;
const char PORT = 0x0; //EV3 label minus 1
const char IR_REMOTE_MODE = 0;
const char IR_REMOTE_CONTROL_CHANNEL  = 0;
const char IR_SENSOR_TYPE = 33;

extern LEGO_EV3_DEVICE lego_ev3;
int main() {
	
	int ret_val = 0;
#if 0
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
#if 0
	int i2c_device_file;
	IIC *pIic;
	int i = 0;
	if (-1 == (i2c_device_file = open(IIC_DEVICE_NAME, O_RDWR | O_SYNC))) {
		printf("failed to open IIC device\n");
		ret_val = -1;
		goto exit;
	}
	if (MAP_FAILED == (pIic = (IIC*)mmap(0, sizeof(UART), PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, i2c_device_file, 0))) {
		printf("mapping IIC device failed\n");
		ret_val = -1;
		goto exit;
	}
	
	printf("IIC device ready\n");
	
	for (i =0; i < 100; i++)
	{	
		printf("status %d\n", (unsigned char)pIic->Status[1]);
		printf("changed %d\n", (unsigned char)pIic->Changed[1]);
		printf("actual %d\n", (UWORD)pIic->Actual[1]);
		printf("login %d\n", (UWORD)pIic->LogIn[1]);
		printf("value %d \n", (unsigned char)pIic->Raw[1][pIic->Actual[1]][0]);
		sleep(1);
	}
	
	printf("closing device\n");
	close(i2c_device_file);
#endif
//DEFINE VARIABLES
	int file;
	UART *pIrRemote; //IR remote user level handler
	DEVCON DevCon; // Configuration parameters
	int i;

	//Open the device file
	if((file = open(UART_DEVICE_NAME, O_RDWR | O_SYNC)) == -1)
	{
		printf("Failed to open IR device\n");
		return -1;
	}
	//Map kernel device to be used at the user space level
	pIrRemote = (UART*)mmap(0, sizeof(UART), PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, file, 0);
	if (pIrRemote == MAP_FAILED)
	{
		printf("Failed to map IR device\n");
		return -1;
	}

	//SPECIAL CONFIGURATION
	//Set IR as remote control
	DevCon.Mode[PORT] = IR_REMOTE_MODE;
	DevCon.Connection[PORT] = CONN_INPUT_UART;
	DevCon.Type[PORT] = IR_SENSOR_TYPE; //This instruction has no effect in the code
	ioctl(file, UART_SET_CONN, &DevCon);
	printf("UART Device is ready \n");

	//PROCESS SENSOR DATA
	//Print results
	for(i = 0; i<MAX_SAMPLES; i++)
	{
	printf("IR Remote Button: %d\n", (char)pIrRemote->Raw[PORT][pIrRemote->Actual[PORT]][IR_REMOTE_CONTROL_CHANNEL]);
	//printf("IR Remote Button: %d\n", (char)pIrRemote->Raw[PORT][pIrRemote->Actual[PORT]][IR_REMOTE_CONTROL_CHANNEL + 1]);
	//printf("IR Remote Button: %d\n", (char)pIrRemote->Raw[PORT][pIrRemote->Actual[PORT]][IR_REMOTE_CONTROL_CHANNEL + 2]);
	sleep(1);
	}

	//CLOSE DEVICE
	printf("Clossing device\n");
	close(file);
exit:
	return ret_val;
}

