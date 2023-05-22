/******************************************************************************
 * [Module]      : ADC module
 * [File Name]   : adc.h
 * [Description] : Header file for the ATmega32 ADC driver
 * [Author]      : Ziad Emad
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 ===================================================================================================
 [enum name ]         : ADC_Prescaler
 [enum description]	  : this ( enum ) responsible for prescaling configuration for the ADC frequency
 ===================================================================================================
 */
typedef enum
{
	divisionFactor_2,divisionFactor_22,divisionFactor_4,divisionFactor_8,divisionFactor_16,divisionFactor_32,divisionFactor_64,divisionFactor_128
}ADC_Prescaler;
/*
 ===================================================================================================
 [enum name ]         : ADC_ReferenceVolatge
 [enum description]	  : this ( enum ) responsible for configuration the voltage used in ADC
 ===================================================================================================
 */
typedef enum{
	aREF,aVCC,reserverd,internal_2V
}ADC_ReferenceVolatge;
/*
 ===================================================================================================
 [structure name ]           : ADC_ConfigType
 [structure description]	 : this structure responsible for configuration of ADC Initializations
 ===================================================================================================
 */
typedef struct{
	ADC_ReferenceVolatge ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 *****************************************************************************************************
[Function Name]	: ADC_init
[Description]  	: This function is responsible for initializing the ADC registers with the requirements
[Arguments]    	: it take a pointer to structure to ease the configuration user can edit
[Returns]      	: This Function return nothing

 ****************************************************************************************************/
void ADC_init(const ADC_ConfigType * ConfigType);

/*
 *****************************************************************************************************
[Function Name]	: ADC_readChannel
[Description]  	: This function is responsible to give us the digital o/p of the ADC.
[Arguments]    	: it take the channel number at which the sensor is connected to.
[Returns]      	: This Function return the ADC value in case of polling and return 0 in case of using
				  interrupts.

 ****************************************************************************************************/
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
