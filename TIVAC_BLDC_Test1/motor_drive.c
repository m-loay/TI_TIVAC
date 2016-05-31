/*
 * motor_drive.c
 *
 *  Created on: May 28, 2016
 *      Author: modys
 */

#include "motor_drive.h"
extern int32_t ia;

//! \brief     Initialize the motor Driver
extern void MotorDrive_init (void)
{
	HAL_GPIO_setPinOutput(GPIO_PORTF_BASE,GPIO_PIN_4);
	HAL_GPIO_PinWrite(GPIO_PORTF_BASE,GPIO_PIN_4,10);

	HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);
	HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);

	HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);
	HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);

	HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);
	HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);
	return;
}// end of MotorDrive_init() function


//! \brief     update the pwm 3 arms according to position of BLDC
//! \param[in] state   the reading of hall sensor
//! \param[in] dutycycle the required duty cycle
extern void MotorDrive_update(uint8_t state,  uint16_t dutycycle)
{
	switch (state)
	{
 	case 1:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, dutycycle);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, dutycycle);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);//CL
		ia=-1;
		break;

	case 2:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, dutycycle);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, dutycycle);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);//CL
		ia=1;
		break;

	case 3:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, dutycycle);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, dutycycle);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);//CL
		ia=0;
		break;

	case 4:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, dutycycle);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, dutycycle);//CL
		ia=0;
		break;

	case 5:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, dutycycle);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, dutycycle);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);//CL
		ia=-1;
		break;

	case 6:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, dutycycle);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, dutycycle);//CL
		ia=1;
		break;
	default:
		break;
	}
}// end of MotorDrive_update() function



/*
  	case 1:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, dutycycle);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, dutycycle);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);//CL
		break;

	case 2:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, dutycycle);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, dutycycle);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);//CL
		break;

	case 3:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, dutycycle);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, dutycycle);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);//CL
		break;

	case 4:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, dutycycle);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, dutycycle);//CL
		break;

	case 5:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, dutycycle);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, dutycycle);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);//CL
		break;

	case 6:
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_0, dutycycle);//AH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);//AL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);//BH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);//BL

		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);//CH
		HAL_Pwm_setDuty(PWM0_BASE, PWM_OUT_5, dutycycle);//CL
		break;
 *
 *
 * */
