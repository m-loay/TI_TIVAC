/*
 * motor_drive.h
 *
 *  Created on: May 28, 2016
 *      Author: modys
 */

#ifndef MOTOR_DRIVE_H_
#define MOTOR_DRIVE_H_

#include "common.h"

//! \brief     Initialize the motor Driver
extern void MotorDrive_init (void);


//! \brief     update the pwm 3 arms according to position of BLDC
//! \param[in] state   the reading of hall sensor
//! \param[in] dutycycle the required duty cycle
extern void MotorDrive_update(uint8_t state,  uint16_t dutycycle);

#endif /* MOTOR_DRIVE_H_ */
