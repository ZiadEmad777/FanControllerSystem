/*************************************************************************************************
 * [Module]		  : Timer0
 * [File Name]    : PWM.c
 * [Description]  : source file for controlling the duty cycle timer0.
 * [Author]       : Ziad Emad
 **************************************************************************************************/
#include "PWM.h"
#include "gpio.h"
#include <avr/io.h>
#include <util/delay.h>


/*******************************************************************************
 *                      Functions Definitions                                  *
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
void PWM_Timer0_Start(uint8 duty_cycle){

	/*Setup the direction for OC0 as output pin through the GPIO driver.*/
	GPIO_setupPinDirection(PWM_pin_PORT_ID, PWM_pin_PIN_ID, PIN_OUTPUT);

	/*Set Timer Initial value*/
	TCNT0=0;

	switch(duty_cycle)
	{
	case 25:
		duty_cycle = 64;
		break;
	case 50:
		duty_cycle= 128;
		break;
	case 75:
		duty_cycle = 192;
		break;
	case 100:
		duty_cycle= 255;
		break;
	}

	/*Set Compare Value 0-->100*/
	OCR0= duty_cycle;

	/*Setup the PWM mode with Non-Inverting.
	 Setup the prescaler with F_CPU/8.
	 Setup the compare value based on the required input duty cycle
	 The generated PWM signal frequency will be 500Hz to control the DC
	 Motor speed.*/
	TCCR0 |= (1<<WGM00) | (1<<COM01) | (1<<WGM01) | (1<<CS01);
}
