/*************************************************************************************************
 * [File Name]    : dc_motor.c
 * [Description]  : source file for controlling motor of the Fan.
 * [Author]       : Ziad Emad
 **************************************************************************************************/
#include "dc_motor.h"
#include "gpio.h"
#include "PWM.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 *****************************************************************************************************
[Function Name]	: DcMotor_Init
[Description]  	: The Function responsible for setup the direction for the two
                  motor pins through the GPIO driver.
[Arguments]    	: This Function take no arguments.
[Returns]      	: This Function return nothing
 ****************************************************************************************************/
void DcMotor_Init(){

	/*configuring the direction of the pins as outputs*/
	GPIO_setupPinDirection(DC_MOTOR_INPUT1_PORT_ID, DC_MOTOR_INPUT1_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_INPUT2_PORT_ID, DC_MOTOR_INPUT2_PIN_ID,PIN_OUTPUT);

	/*Motor is stop at the beginning*/
	GPIO_writePin(DC_MOTOR_INPUT1_PORT_ID, DC_MOTOR_INPUT1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_INPUT2_PORT_ID, DC_MOTOR_INPUT2_PIN_ID, LOGIC_LOW);
}

/*
 *****************************************************************************************************
[Function Name]	: DcMotor_Rotate
[Description]  	: The function responsible for rotate the DC Motor CW/ or A-CW or
				  stop the motor based on the state input state value
[Arguments]    	: state: The required DC Motor state, it should be CW or A-CW or stop.
				  DcMotor_State data type should be declared as enum or uint8.
				  speed: decimal value for the required motor speed, it should be from
				  0 → 100. For example, if the input is 50, The motor should rotate with
				  50% of its maximum speed.
[Returns]      	: This Function return nothing.
 ****************************************************************************************************/
void DcMotor_Rotate(Dc_Motor_State state,uint8 speed){
	/*adjust speed of the motor by adjusting the duty cycle of the PWM signal*/
	PWM_Timer0_Start(speed);

	if (state == stop)
	{
		GPIO_writePin(DC_MOTOR_INPUT1_PORT_ID, DC_MOTOR_INPUT1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_INPUT2_PORT_ID, DC_MOTOR_INPUT2_PIN_ID, LOGIC_LOW);
	}
	else if(state == clockwise)
	{
		GPIO_writePin(DC_MOTOR_INPUT1_PORT_ID, DC_MOTOR_INPUT1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_INPUT2_PORT_ID, DC_MOTOR_INPUT2_PIN_ID, LOGIC_HIGH);
	}
	else if (state==anticlockwise)
	{
		GPIO_writePin(DC_MOTOR_INPUT1_PORT_ID, DC_MOTOR_INPUT1_PIN_ID,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_INPUT2_PORT_ID, DC_MOTOR_INPUT2_PIN_ID, LOGIC_LOW);
	}

}
