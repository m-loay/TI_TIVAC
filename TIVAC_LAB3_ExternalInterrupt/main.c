#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"

#define GPIO_PORTF_LOCK			*((uint32_t*)0x40025520)
#define GPIO_PORTF_CR			*((uint32_t*)0x40025524)
#define GPIO_PORTF_UNLOCK_VALUE	 0x4C4F434B

#define SW1		GPIO_PIN_4
#define SW2		GPIO_PIN_0
#define R_LED	GPIO_PIN_1
#define B_LED	GPIO_PIN_2
#define G_LED 	GPIO_PIN_3

volatile uint8_t counter=2;


int main(void)
{


	/*Enable Clock system using PLL with main Oscliator of 16MHZ
	 * System clock=200MHZ/SYSCTL_SYSDIV_5=40MHZ
	 * */
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	/*Enable preipheral Clock of PortF*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	/*Unlock PF0*/
	GPIO_PORTF_LOCK=GPIO_PORTF_UNLOCK_VALUE;
	GPIO_PORTF_CR=0x1F;

	/*Make SW1 as input with pull up*/
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, SW1|SW2);
	GPIOPadConfigSet(GPIO_PORTF_BASE, SW1|SW2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);


	/*Make R,G,B leds as output */
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, R_LED|B_LED| G_LED);

	/*Enable interrupts*/

	GPIOIntTypeSet(GPIO_PORTF_BASE, SW1|SW2 ,GPIO_FALLING_EDGE);
	IntEnable(INT_GPIOF);
	GPIOIntEnable(GPIO_PORTF_BASE, SW1|SW2);
	IntMasterEnable();


	while(1)
	{

	}
}



void GPIOF_SW1_Handler (void)
{
	GPIOIntClear(GPIO_PORTF_BASE, SW1|SW2);
	if (GPIOPinRead(GPIO_PORTF_BASE,SW2)==0)
		counter++;
	//else if (GPIOPinRead(GPIO_PORTF_BASE,SW1)==0)
	else
		counter--;

	GPIOPinWrite(GPIO_PORTF_BASE,R_LED|B_LED| G_LED,counter);

}
