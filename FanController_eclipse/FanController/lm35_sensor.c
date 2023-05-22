/******************************************************************************
 * [Module]      : Temperature Sensor
 * [File Name]   : lm35.c
 * [Description] : Source file for the ATmega32 ADC driver
 * [Author]      : Ziad Emad
 *******************************************************************************/

#include "lm35_sensor.h"
#include "adc.h"
#include <avr/delay.h>

/*
 *****************************************************************************************************
[Function Name]	: LM35_getTemperature
[Description]  	: Function responsible for calculate the temperature from the ADC digital value.
[Arguments]    	: This Function take no Arguments.
[Returns]      	: This Function return nothing

 ****************************************************************************************************/
uint8 LM35_getTemperature()
{
	uint8 temp_value = 0;

	uint16 adc_value = 0;
#ifndef ADC_INTERRUPT_ENABLE
	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);
#else
	ADC_readChannel(SENSOR_CHANNEL_ID);
	adc_value= g_adcResult;
#endif
	_delay_ms(5);
	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8) ( ( (uint32) adc_value *SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE) / (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE) );

	return temp_value;
}

