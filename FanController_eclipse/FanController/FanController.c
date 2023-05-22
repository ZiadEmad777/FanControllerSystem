/*************************************************************************************************
 * [Module]		  : Application Module.
 * [File Name]    : FanController.c
 * [Description]  : source file for controlling the fan speed with change of temperature.
 * [Author]       : Ziad Emad
 **************************************************************************************************/
#include <avr/io.h>
#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"
#include "adc.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 ===================================================================================================
 [enum name ]         : Fan_state
 [enum description]	  : this ( enum ) responsible for the fan state which will be printed
 	 	 	 	 	 	the screen.
 ===================================================================================================
 */
typedef enum{
	OFF,ON
}Fan_state;



/*******************************************************************************
 *                        Main Function                                        *
 *******************************************************************************/
int main()
{
	uint8 temp=0;
#ifdef ADC_INTERRUPT_ENABLE
	SREG |=(1<<7);
#endif
	Fan_state state;
	ADC_ConfigType parameters ={internal_2V,divisionFactor_8};

	/* initialize LCD driver */
	LCD_init();
	/* initialize ADC driver */
	ADC_init(&parameters);
	/* initialize dc_motor driver */
	DcMotor_Init();
	/* Display this string "Fan is " only once on LCD at the first row */
	LCD_displayStringRowColumn(0, 4, "FAN is ");
	/* Display this string "Fan is " only once on LCD at the first row */
	LCD_displayStringRowColumn(1, 4, "Temp =     C");

	while(1)
	{
		/*Get the temperature value from the temperature sensor*/
		temp=LM35_getTemperature();
		if ( temp <30 )
		{
			/*fan is off*/
			state=OFF;
			/*motor will not rotate*/
			DcMotor_Rotate(stop, 0);
		}
		else if ( (temp >= 30) && (temp <60) )
		{
			/*fan is on*/
			state=ON;
			/*motor will rotate with 25% of max speed*/
			DcMotor_Rotate(anticlockwise, 25);
		}
		else if ( (temp >=60) && (temp <90) )
		{
			/*fan is on*/
			state=ON;
			/*motor will rotate with 50% of max speed*/
			DcMotor_Rotate(clockwise,50);
		}
		else if ( (temp >=90) && (temp <120) )
		{
			/*fan is on*/
			state=ON;
			/*motor will rotate with 75% of max speed*/
			DcMotor_Rotate(clockwise, 75);
		}
		else if (  temp > 120 )
		{
			/*fan is on*/
			state=ON;
			/*motor will rotate with max speed*/
			DcMotor_Rotate(clockwise, 100);
		}

		/*Display the messages on the LCD*/
		LCD_moveCursor(1, 11);
		if (temp>=100) {
			LCD_intgerToString(temp);

		}
		else{
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		LCD_moveCursor(0, 11);
		if (state== OFF) {
			LCD_displayString("OFF");
		}
		else{
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
		}

	}
	return 0;
}

