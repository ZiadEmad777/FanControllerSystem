/******************************************************************************
 * [Module]      : ADC module
 * [File Name]   : adc.c
 * [Description] : Source file for the ATmega32 ADC driver
 * [Author]      : Ziad Emad
 *******************************************************************************/

#include "adc.h"
#include "avr/io.h" /* To use the ADC Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#ifdef ADC_INTERRUPT_ENABLE
#include <avr/interrupt.h>
#endif

/* if the module is working with interrupts
 * g_adc_result is to save the converted digital value
 * value is read from the ISR */
#ifdef ADC_INTERRUPT_ENABLE

volatile uint16 g_adcResult = 0;


ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC;
}
#endif
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 *****************************************************************************************************
[Function Name]	: ADC_init
[Description]  	: This function is responsible for initializing the ADC registers with the requirements
[Arguments]    	: it take a pointer to structure to ease the configuration user can edit
[Returns]      	: This Function return nothing

 ****************************************************************************************************/

void ADC_init(const ADC_ConfigType * ConfigType)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = (ConfigType ->ref_volt << REFS0);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz --> ADC must operate in range 50-200Khz
	 */
	SET_BIT(ADCSRA,ADEN);
#ifdef ADC_INTERRUPT_ENABLE
	SET_BIT(ADCSRA,ADIE);
#else
	CLEAR_BIT(ADCSRA,ADIE);
#endif
	ADCSRA &= 0xF8;
	ADCSRA |= ConfigType->prescaler;
}

/*
 *****************************************************************************************************
[Function Name]	: ADC_readChannel
[Description]  	: This function is responsible to give us the digital o/p of the ADC.
[Arguments]    	: it take the channel number at which the sensor is connected to.
[Returns]      	: This Function return the ADC value in case of polling and return 0 in case of using
				  interrupts.

 ****************************************************************************************************/
uint16 ADC_readChannel(uint8 channel_num)
{
	/* Input channel number must be from 0 --> 7 */
	channel_num &= 0x07;
	/* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX &= 0xE0;
	/* Choose the correct channel by setting the channel number in MUX4:0 bits */
	ADMUX |=  channel_num;
	 /* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA,ADSC);
#ifndef ADC_INTERUPPT_ENABLE
	/* Wait for conversion to complete, ADIF becomes '1' */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	/* Clear ADIF by write '1' to it :) */
	SET_BIT(ADCSRA,ADIF);
	/* Read the digital value from the data register */
	return ADC;
#else
	return 0;
#endif

}
