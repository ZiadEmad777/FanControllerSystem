/*************************************************************************************************
 * [File Name]    : dc_motor.h
 * [Description]  : Header file for controlling the motor of the Fan.
 * [Author]       : Ziad Emad
 **************************************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_E_PORT_ID              PORTB_ID
#define DC_MOTOR_E_PIN_ID               PIN3_ID

#define DC_MOTOR_INPUT1_PORT_ID		    PORTB_ID
#define DC_MOTOR_INPUT1_PIN_ID		    PIN0_ID

#define DC_MOTOR_INPUT2_PORT_ID		    PORTB_ID
#define DC_MOTOR_INPUT2_PIN_ID		    PIN1_ID

#define DC_MOTOR_ENABLE_PORT_ID         PORTB_ID /*this is for the PWM oc0*/
#define DC_MOTOR_ENABLE_PIN_ID			PIN3_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
/*
 ==================================================================================================
 [enum name ]         : DcMotor_State
 [enum description]	  : this ( enum ) responsible for  configuration of motor's rotation direction .
 ====================================================================================================
 */
typedef enum{
	stop,clockwise,anticlockwise
}Dc_Motor_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
*****************************************************************************************************
[Function Name]	: DcMotor_Init
[Description]  	: The Function responsible for setup the direction for the two
                  motor pins through the GPIO driver.
[Arguments]    	: This Function take no arguments.
[Returns]      	: This Function return nothing
****************************************************************************************************/
void DcMotor_Init();

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
void DcMotor_Rotate(Dc_Motor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
