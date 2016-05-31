#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

#define R_LED		GPIO_PIN_1
#define B_LED		GPIO_PIN_2
#define G_LED 		GPIO_PIN_3

volatile uint8_t choice=0;
int main(void)
{


	/*Enable Clock system using PLL with main Oscliator of 16MHZ
	 * System clock=200MHZ/SYSCTL_SYSDIV_5=40MHZ
	 * */
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	/*Enable preipheral Clock of PortF*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	/*Enable preipheral Clock of TIMER0*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

	/*Make PF1,PF2,PF3 Pins as o/p*/
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, R_LED| B_LED| G_LED);

	/*Configure TIMER0*/
	TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, 40000000);


	TimerEnable(TIMER0_BASE, TIMER_A);


	while(1)
	{

		while(!TimerIntStatus(TIMER0_BASE,false));
		// Clear the timer interrupt
		TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
		choice+=2;

		// Turn on the LED
		GPIOPinWrite(GPIO_PORTF_BASE, R_LED| B_LED| G_LED, choice);

		if(choice==14) choice=2;


	}

}


