/*************************************************************************************************
 * [File Name]    : PWM.h
 * [Description]  : Header file for controlling the duty cycle timer0.
 * [Author]       : Ziad Emad
 **************************************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PWM_pin_PORT_ID					PORTB_ID
#define PWM_pin_PIN_ID					PIN3_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 ==================================================================================================
 [enum name ]         : fastPWM_mode
 [enum description]	  : this ( enum ) responsible for configuration Compare Output Mode, Fast PWM Mode .
 ====================================================================================================
 */
typedef enum{
	oc0_OFF,reserved,non_inverting,inverting
}fastPWM_mode;

/*
 ==================================================================================================
 [enum name ]         : clock_select
 [enum description]	  : this ( enum ) responsible for configuration Clock Select Bit Description.
 ====================================================================================================
 */
typedef enum {
	no_clk,clk1,clk8,clk64,clk256,clk1024,extclk_falling,extclk_rising
}clock_select;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
*****************************************************************************************************
[Function Name]	: PWM_Timer0_Start
[Description]  	: The function responsible for trigger the Timer0 with the PWM Mode.
				  	  ➢ Setup the PWM mode with Non-Inverting.
					  ➢ Setup the prescaler with F_CPU/8.
					  ➢ Setup the compare value based on the required input duty cycle
					  ➢ Setup the direction for OC0 as output pin through the GPIO driver.
					  ➢ The generated PWM signal frequency will be 500Hz to control the DC
						Motor speed.
[Arguments]    	: Tduty_cycle: The required duty cycle percentage of the generated
				  PWM signal. Its value should be from 0 → 100
[Returns]      	: This Function return nothing

****************************************************************************************************/
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
