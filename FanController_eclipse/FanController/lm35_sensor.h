/******************************************************************************
 * [Module]      : Temperature Sensor
 * [File Name]   : lm35.h
 * [Description] : Header file for the ATmega32 ADC driver
 * [Author]      : Ziad Emad
 *******************************************************************************/

#ifndef LM35_SENSOR_H_
#define LM35_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 *****************************************************************************************************
[Function Name]	: LM35_getTemperature
[Description]  	: Function responsible for calculate the temperature from the ADC digital value.
[Arguments]    	: This Function take no Arguments.
[Returns]      	: This Function return nothing

 ****************************************************************************************************/
uint8 LM35_getTemperature();

#endif /* LM35_SENSOR_H_ */
