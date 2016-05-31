/*
 * hallSensor.c
 *
 *  Created on: May 28, 2016
 *      Author: modys
 */

#include "hallSensor.h"


//! \brief     Initialize the hall sensor
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins					    The pins required to configure ored together
extern void HallSensor_init (void)
{

	HAL_GPIO_setPinInput(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1 ,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_2 ,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_3 ,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	return;
}// end of HallSensor_init() function

//! \brief     read the GPIOs as output (General purpose input /output)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins					    The pins required to configure ored together
//! \return  value to read on the pins
extern void  HallSensor_read(uint8_t *HallSensor_data)
{

	*HallSensor_data=(HAL_GPIO_PinRead(GPIO_PORTF_BASE, GPIO_PIN_1| GPIO_PIN_2 | GPIO_PIN_3))>>1;
	return;
}// end of HallSensor_read() function
