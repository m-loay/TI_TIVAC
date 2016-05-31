/*
 * hallSensor.h
 *
 *  Created on: May 28, 2016
 *      Author: modys
 */

#ifndef HALLSENSOR_H_
#define HALLSENSOR_H_

#include "common.h"


//! \brief     Initialize the hall sensor
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins					    The pins required to configure ored together
extern void HallSensor_init (void);


//! \brief     Initialize the hall sensor
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins
extern void  HallSensor_read(uint8_t *HallSensor_data);

#endif /* HALLSENSOR_H_ */
