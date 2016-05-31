#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"

#include "inc/hw_gpio.h"


#define SS1     1
#define ENABLE  1
#define DISABLE 0

uint32_t read=0;
uint32_t result=0;

int main(void)
{


	/*Enable Clock system using PLL with main Oscliator of 16MHZ
	 * System clock=200MHZ/SYSCTL_SYSDIV_5=40MHZ
	 * */
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	/*Enable preipheral Clock of PortD*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);



	/*Make SW1 as input with pull up*/
	GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1);

	/*Configure ADC */
	ADCSequenceDisable(ADC0_BASE,DISABLE);
	ADCSequenceConfigure(ADC0_BASE, SS1, ADC_TRIGGER_PROCESSOR,0);
	ADCSequenceStepConfigure(ADC0_BASE, SS1, 0, ADC_CTL_IE| ADC_CTL_END| ADC_CTL_CH6);
	ADCSequenceEnable(ADC0_BASE, SS1);


	while(1)
	{
		ADCIntClear(ADC0_BASE, SS1);
		ADCProcessorTrigger(ADC0_BASE, SS1);

		while(! ADCIntStatus(ADC0_BASE, SS1,false));

		ADCSequenceDataGet(ADC0_BASE, SS1,&read);
	//	result=((read*9)+160)/5;

	}

}



