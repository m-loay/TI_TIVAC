/*
 * hal.c
 *
 *  Created on: May 25, 2016
 *      Author: modys
 */
#include "hal.h"

/*******************Init Function************************/

//! \brief      Initializes the hardware abstraction layer (HAL) object
//! \details    Initializes all handles to the microcontroller peripherals.
extern void HAL_init (void)
{
	ROM_FPULazyStackingEnable();
	ROM_FPUEnable();
	HAL_SystemClk_setup();
	HAL_Timer_setup(TIMER0_BASE, TIMER_CFG_A_PERIODIC,TIMER_A, 3000);
	HAL_Pwm_setup(PWM0_BASE, HAL_PWM_CLK_MHZ, HAL_PWM_FREQ_KHZ);
	HAL_Adc_setup(ADC0_BASE, HAL_SS0 ,ADC_TRIGGER_TIMER);
	return;
}// end of HAL_init() function


//! \brief      Initializes the hardware abstraction layer (HAL) object
//! \details    Initializes allmodules to the microcontroller peripherals.
//!             Returns nothing
extern void HAL_SystemClk_setup (void)
{
	/*Enable Clock system using PLL with main Oscliator of 16MHZ
	 * System clock=200MHZ/SYSCTL_SYSDIV_5=40MHZ
	 * PWM clock=System clock / SYSCTL_PWMDIV_2=20
	 * */
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPWMClockSet(SYSCTL_PWMDIV_2);

	/*Enable preipheral Clock of PortA,B,D,E,F*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	/*Enable preipheral Clock of TIMER0*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	/*Enable preipheral Clock of ADC0*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

	/*Enable preipheral Clock of PWM*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	return;

}// end of HAL_SystemClk_setup() function


//! \brief     Enable Peripheral clock
//! \param[in]  ui32 preipheral
extern void HAL_SystemPeripheralEnable(uint32_t peripheral)
{
	SysCtlPeripheralEnable(peripheral);
	return;
}// end of HAL_SystemPeripheralEnable() function


/*******************Enable/Disable GIE Functions************************/

//! \brief    enable a global interrupt
extern void HAL_MasterInt_enable(void)
{

	IntMasterEnable();
	return;
}  // end of HAL_MasterInt_enable() function


//! \brief    disable a global interrupt
extern void HAL_MasterInt_disable(void )
{

	IntMasterDisable();
	return;

}  // end of HAL_MasterInt_disable() function


/*******************Timers Functions************************/

//! \brief     Setup Timer0 Interrupt
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in]  ui32 config is the configuration of timer
//! \param[in]  ui32 timerNumber to select the required timer
//! \param[in]  ui32 timerValue timer periode=desiredtime/Cpu clk
//! \All of the ranges can be found in timer.h
extern void HAL_Timer_setup(uint32_t base, uint32_t config,uint32_t timerNumber ,uint32_t timerValue)
{

	/*Configure the timer*/
	TimerConfigure(base, config);

	/*Load the timer with proper value*/
	TimerLoadSet(base, timerNumber, timerValue);

	/*Trigger the adc */
	TimerControlTrigger(base,timerNumber, true );
	return;
}// end of HAL_Timer_setup() function


//! \brief    enable a timerinterrupt
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in]  ui32 interrupts to select the required timer
//! \param[in]  ui32 interruptflags to select the required mode
//! \All of the ranges can be found in timer.h and tm4c123gh6pm.h
extern void HAL_TimerInt_enable(uint32_t base, uint32_t interrupts,uint32_t interruptflags )
{

	// start the specified timer
	IntEnable(interrupts);
	TimerIntEnable(base, interruptflags);
	return;
}  // end of HAL_Timerinr_enable() function


//! \brief    enable a timerinterrupt
//! \param[in]  ui32 base is the base address value of required timer
//! \param[in]  ui32 interrupts to select the required timer
//! \param[in]  ui32 interruptflags to select the required mode
//! \All of the ranges can be found in timer.h and tm4c123gh6pm.h
extern void HAL_TimerInt_disable(uint32_t base, uint32_t interrupts,uint32_t interruptflags )
{

	// stop the specified timer
	IntDisable(interrupts);
	TimerIntDisable(base, interruptflags);
	return;

}  // end of HAL_Timerint_disable() function



/*******************PWM Functions************************/

//! \brief     Sets up the PWMs (Pulse Width Modulators)
//! \param[in] uint32_t base   base is the base address value of required timer
//! \param[in] PwmFreq_MHz The Pwm frequency in MHZ
//! \param[in] desiredFreq_KHz The PWM desired frqquency in KHz
extern void HAL_Pwm_setup(uint32_t base,
		const uint32_t PwmFreq_MHz,
		const uint32_t desiredFreq_KHz)
{
	uint32_t halfPeriod_cycles=((PwmFreq_MHz*1000)/desiredFreq_KHz)-1;

	/*Make PB4,5,6,7, PE4,5 Pins as PWM*/

	GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
	GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);

	GPIOPinConfigure(GPIO_PB6_M0PWM0);
	GPIOPinConfigure(GPIO_PB7_M0PWM1);
	GPIOPinConfigure(GPIO_PB4_M0PWM2);
	GPIOPinConfigure(GPIO_PB5_M0PWM3);
	GPIOPinConfigure(GPIO_PE4_M0PWM4);
	GPIOPinConfigure(GPIO_PE5_M0PWM5);

	/*Configure PWM
	 * 1)configure Gen 0,1,2
	 * 2) Sync Comparators, load regsiters , DB registers*/
	PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_DB_NO_SYNC );
	PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_DB_NO_SYNC );
	PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_DB_NO_SYNC );

	//Set the Period (expressed in clock ticks)
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, halfPeriod_cycles);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, halfPeriod_cycles);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, halfPeriod_cycles);

	//Set PWM duty
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, HAL_MIN_DUTY);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, HAL_MIN_DUTY);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, HAL_MIN_DUTY);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, HAL_MIN_DUTY);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, HAL_MIN_DUTY);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, HAL_MIN_DUTY);

	/*Sysnc PWM time base clock */
	PWMSyncUpdate(PWM0_BASE, PWM_GEN_0_BIT | PWM_GEN_1_BIT | PWM_GEN_2_BIT);

	// Turn on the Output pins
	PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT | PWM_OUT_2_BIT |
			PWM_OUT_3_BIT | PWM_OUT_4_BIT | PWM_OUT_5_BIT , true);

	// Enable the PWM generator
	PWMGenEnable(PWM0_BASE, PWM_GEN_0);
	PWMGenEnable(PWM0_BASE, PWM_GEN_1);
	PWMGenEnable(PWM0_BASE, PWM_GEN_2);

	/*Sysnc PWM time base clock */
	PWMSyncUpdate(PWM0_BASE, PWM_GEN_0_BIT | PWM_GEN_1_BIT | PWM_GEN_2_BIT);
	return;

} // end of HAL_Pwm_setup() function


/*******************ADC Functions************************/

//! \brief     Sets up the ADCs (Analogue to Digital Converter)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] SampleSequncer_number    The sample sequencer number
//! \param[in] AdcTrigger  				The trigger source
extern void HAL_Adc_setup(uint32_t base, uint32_t SampleSequncer_number, uint32_t AdcTrigger)
{

	/*Make Pins PE0,1,2,3 and PD0,1,2,3 as ADC pins*/
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_0);
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1);
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0);
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1);
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2);
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_3);

	/*Disable the adc module before any configuration*/
	ADCSequenceDisable(base,SampleSequncer_number);

	/*Configure sample sequencer number and trigger source */
	ADCSequenceConfigure(base, SampleSequncer_number, ADC_TRIGGER_TIMER, 0);

	/*Define the steps for the sequencer*/
	ADCSequenceStepConfigure(base, SampleSequncer_number, 0, ADC_CTL_CH0);
	ADCSequenceStepConfigure(base, SampleSequncer_number, 1, ADC_CTL_CH1);
	ADCSequenceStepConfigure(base, SampleSequncer_number, 2, ADC_CTL_CH2);
	ADCSequenceStepConfigure(base, SampleSequncer_number, 3, ADC_CTL_CH4);
	ADCSequenceStepConfigure(base, SampleSequncer_number, 4, ADC_CTL_CH5);
	ADCSequenceStepConfigure(base, SampleSequncer_number, 5, ADC_CTL_CH6);
	ADCSequenceStepConfigure(base, SampleSequncer_number, 6, ADC_CTL_CH7);
	ADCSequenceStepConfigure(base, SampleSequncer_number, 7, ADC_CTL_CH3|ADC_CTL_IE|ADC_CTL_END);

	/*Enable Sample sequencer*/
	ADCSequenceEnable(base, SampleSequncer_number);

	/*Clear the interrupt flag*/
	ADCIntClear(base, SampleSequncer_number);
	return;
}// end of HAL_Adc_setup() function


/*******************GPIO Functions************************/

//! \brief     Sets up the GPIOs as input (General purpose input /output)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins					    The pins required to configure ored together
extern void HAL_GPIO_setPinInput (uint32_t base, uint8_t pins)
{
	GPIOPinTypeGPIOInput(base, pins);
	return;
}


//! \brief     Sets up the GPIOs as output (General purpose input /output)
//! \param[in] base    					base is the base address value of required timer
//! \param[in] pins					    The pins required to configure ored together
extern void HAL_GPIO_setPinOutput (uint32_t base, uint8_t pins)
{
	GPIOPinTypeGPIOOutput(base, pins);
	return;
}
