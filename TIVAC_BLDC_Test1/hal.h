/*
 * hal.h
 *
 *  Created on: May 25, 2016
 *      Author: modys
 */

#ifndef HAL_H_
#define HAL_H_

#include "common.h"

#define HAL_MIN_DUTY		0
#define HAL_MAX_DUTY		994
#define HAL_PWM_CLK_MHZ		20
#define HAL_PWM_FREQ_KHZ	20
#define HAL_SS0				0


/*******************Init Function************************/

//! \brief      Initializes the hardware abstraction layer (HAL) object
//! \details    Initializes all handles to the microcontroller peripherals.
extern void HAL_init (void);

//! \brief      Initializes the hardware abstraction layer (HAL) object
//! \details    Initializes allmodules to the microcontroller peripherals.
//!             Returns nothing
extern void HAL_SystemClk_setup (void);

//! \brief     Enable Peripheral clock
//! \param[in]  ui32 preipheral
extern void HAL_SystemPeripheralEnable(uint32_t peripheral);

/*******************Enable/Disable GIE Functions************************/

//! \brief    enable a global interrupt
extern void HAL_MasterInt_enable(void);


//! \brief    disable a global interrupt
extern void HAL_MasterInt_disable(void );


/*******************Timers Functions************************/

//! \brief     Setup Timer0 Interrupt
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in]  ui32 config is the configuration of timer
//! \param[in]  ui32 timerNumber to select the required timer
//! \param[in]  ui32 timerValue timer periode=desiredtime/Cpu clk
//! \All of the ranges can be found in timer.h
extern void HAL_Timer_setup(uint32_t base, uint32_t config,uint32_t timerNumber ,uint32_t timerValue);

//! \brief    enable a timerinterrupt
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in]  ui32 interrupts to select the required timer
//! \param[in]  ui32 interruptflags to select the required mode
//! \All of the ranges can be found in timer.h and tm4c123gh6pm.h
extern void HAL_TimerInt_enable(uint32_t base, uint32_t interrupts,uint32_t interruptflags );


//! \brief    enable a timerinterrupt
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in]  ui32 interrupts to select the required timer
//! \param[in]  ui32 interruptflags to select the required mode
//! \All of the ranges can be found in timer.h and tm4c123gh6pm.h
extern void HAL_TimerInt_disable(uint32_t base, uint32_t interrupts,uint32_t interruptflags );


//! \brief    reload timer
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in]  ui32 timerNumber to select the required timer
//! \param[in]  ui32 timerNumber timer periode=desiredtime/Cpu clk
//! \All of the ranges can be found in timer.h
static inline void HAL_Timer_reload(uint32_t base,uint32_t timerNumber ,uint32_t timerValue)
{

	// reload the specified timer
	TimerLoadSet(base, timerNumber, timerValue);
	return;
}  // end of HAL_Timer_reload() function


//! \brief    enable a timer
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in]  ui32 timerNumber to select the required timer
//! \All of the ranges can be found in timer.h
static inline void HAL_Timer_enable(uint32_t base, uint32_t timerNumber)
{

	// start the specified timer
	TimerEnable(base, timerNumber);
	return;
}  // end of HAL_Timer_enable() function


//! \brief    disable a timer
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in]  ui32 timerNumber to select the required timer
//! \All of the ranges can be found in timer.h
static inline void HAL_Timer_disable(uint32_t base, uint32_t timerNumber)
{

	// stop the specified timer
	TimerDisable(base, timerNumber);
	return;
}  // end of HAL_Timer_disable() function


//! \brief     Sets the timer period
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in] timerNumber  The timer number, 0,1 or 2
//! \param[in] period       The timer period
static inline void HAL_setTimerPeriod(uint32_t base,uint32_t timerNumber ,uint32_t timerValue)
{

	// set the period
	TimerLoadSet(base, timerNumber, timerValue);

	return;
}  // end of HAL_setTimerPeriod() function


/*******************PWM Functions************************/

//! \brief     Sets up the PWMs (Pulse Width Modulators)
//! \param[in] uint32_t base   base is the base address value of required timer
//! \param[in] PwmFreq_MHz The Pwm frequency in MHZ
//! \param[in] desiredFreq_KHz The PWM desired frqquency in KHz
extern void HAL_Pwm_setup(uint32_t base,
		const uint32_t PwmFreq_MHz,
		const uint32_t desiredFreq_KHz);

//! \brief     enable the required pins and disable the rest pins
//! \param[in]  ui32 base is the base address value of required pwm
//! \param[in] timerNumber  PWM_OUT_n_BIT ,n=0 --> 5
//! \param[in] dutyCycle       The pwm dutyCycle
static inline void HAL_Pwm_setDuty(uint32_t base , uint32_t PwmOutPin, uint32_t dutyCycle)
{
	PWMPulseWidthSet(base, PwmOutPin, dutyCycle);
} // end of HAL_setTimerPeriod() function


/*******************ADC Functions************************/

//! \brief     Sets up the ADCs (Analogue to Digital Converter)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] SampleSequncer_number    The sample sequencer number
//! \param[in] AdcTrigger  				The trigger source
extern void HAL_Adc_setup(uint32_t base, uint32_t SampleSequncer_number, uint32_t AdcTrigger);

//! \brief     Sets up the ADCs (Analogue to Digital Converter)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] SampleSequncer_number    The sample sequencer number
//! \param[in] *pAdcData  				A pointer to the ADC data buffer
static inline void HAL_readAdcData(uint32_t base, uint32_t SampleSequncer_number, uint32_t *pAdcData)
{
	/*Check if the ADc finished conversion*/
	while(! ADCIntStatus(base, SampleSequncer_number,false));

	/*get the data of adc in buffer*/
	ADCSequenceDataGet(base, SampleSequncer_number, pAdcData);

	/*Clear the interrupt flag*/
	ADCIntClear(base, SampleSequncer_number);
	return;
} // end of HnAL_readAdcData() function


/*******************GPIO Functions************************/

//! \brief     Sets up the GPIOs as input (General purpose input /output)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins					    The pins required to configure ored together
extern void HAL_GPIO_setPinInput (uint32_t base, uint8_t pins);

//! \brief     Sets up the GPIOs as output (General purpose input /output)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins					    The pins required to configure ored together
extern void HAL_GPIO_setPinOutput (uint32_t base, uint8_t pins);

//! \brief     write the GPIOs as output (General purpose input /output)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins					    The pins required to configure ored together
//! \param[in] pinsValue				the value to write on the pins
static inline void HAL_GPIO_PinWrite (uint32_t base, uint8_t pins, uint8_t pinsValue)
{
	GPIOPinWrite(base, pins, pinsValue);
	return;
}


//! \brief     read the GPIOs as output (General purpose input /output)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins					    The pins required to configure ored together
//! \return  value to read on the pins
static inline  uint8_t HAL_GPIO_PinRead(uint32_t base, uint8_t pins)
{
	return(GPIOPinRead(base, pins));
}

#endif /* HAL_H_ */
