#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/adc.h"
#include "driverlib/debug.h"

#define SW1			GPIO_PIN_4
#define R_LED		GPIO_PIN_1
#define B_LED		GPIO_PIN_2
#define G_LED 		GPIO_PIN_3
#define STATE_RED	0
#define STATE_YEL	1
#define STATE_GER	2

struct Obj_State
{
	uint8_t out;
	uint32_t wait;
	uint8_t next[3];
};

typedef struct Obj_State  FSM_obj;

FSM_obj  Traffic_light[3]=
{
		{2, 20000000,{STATE_RED,STATE_YEL,STATE_YEL}},
		{10, 20000000,{STATE_YEL,STATE_GER,STATE_GER}},
		{8, 40000000,{STATE_GER,STATE_RED,STATE_RED}}
};


int main(void)
{
	uint8_t counter=0;
	uint8_t state=0;
	/*Enable Clock system using PLL with main Oscliator of 16MHZ
	 * System clock=200MHZ/SYSCTL_SYSDIV_5=40MHZ
	 * */
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	/*Enable preipheral Clock of PortF*/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	/*Make SW1 as input with pull up*/
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, SW1);
	GPIOPadConfigSet(GPIO_PORTF_BASE, SW1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	/*Make R,G,B leds as output */
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, R_LED|B_LED| G_LED);



	while(1)
	{
		//if(GPIOPinRead(GPIO_PORTF_BASE,SW1)==0)
		{
			GPIOPinWrite(GPIO_PORTF_BASE,R_LED|B_LED| G_LED,Traffic_light[state].out);
			SysCtlDelay(Traffic_light[state].wait);
			counter++;
			if(counter>2)counter=0;
			state=Traffic_light[state].next[counter];
		}

	}
}


