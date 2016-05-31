

#include <stdint.h>

/*The define Section*/
#define GPIO_PORTF_CGC			*((uint32_t*)0x400FE608)
#define GPIO_PORTF_DIR			*((uint32_t*)0x40025400)
#define GPIO_PORTF_DATA			*((uint32_t*)0x400253FC)
#define GPIO_PORTF_DEN			*((uint32_t*)0x4002551C)
#define GPIO_PORTF_AFSEL		*((uint32_t*)0x40025420)
#define GPIO_PORTF_PUR			*((uint32_t*)0x40025510)
#define GPIO_PORTF_LOCK			*((uint32_t*)0x40025520)
#define GPIO_PORTF_CR			*((uint32_t*)0x40025524)
#define GPIO_PORTF_UNLOCK_VALUE	 0x4C4F434B
#define GPIO_PORTF_RLED			*((uint32_t*)0x40025008)
#define GPIO_PORTF_SW1	    	*((uint32_t*)0x40025040)
#define GPIO_PORTF_SW2	    	*((uint32_t*)0x40025004)

/*The Declaration section*/


/*The Function prototype Section*/
void init_system (void);
void flash_led (void);
void delay (uint16_t half_sec);
int main(void)
{

	init_system();
	while(1)
	{

		do
		{

		} while ( GPIO_PORTF_SW1!=0);

		do
		{
			flash_led();
		} while ( GPIO_PORTF_SW2!=0);


	}



}


/*The Function Definition Section*/
void init_system (void)
{
	/*Activate Clocking system for port F*/
	GPIO_PORTF_CGC=0x20;

	/*choose the direction for PF1 as an output and PF4,PF0 is input*/
	GPIO_PORTF_DIR=0x2;

	/*choose the function for PF4,PF1 as a GPIO*/
	GPIO_PORTF_AFSEL=0;

	/*Unlock PF0*/
	GPIO_PORTF_LOCK=GPIO_PORTF_UNLOCK_VALUE;
	GPIO_PORTF_CR=0x1F;

	/*Enable PF4,PF1 ,PF0as a DIO*/
	GPIO_PORTF_DEN=0x13;

	/*Enable Pull up for PF4,PF0*/
	GPIO_PORTF_PUR=0x10;

	/*Activate PF1*/
	GPIO_PORTF_RLED=0x2;

	/*deactivate PF1*/
	GPIO_PORTF_RLED=0;

}


void flash_led (void)
{
	/*Activate PF1*/
	GPIO_PORTF_RLED=0x2;
	delay(1);
	/*deactivate PF1*/
	GPIO_PORTF_RLED=0;
	delay(1);

}


void delay (uint16_t half_sec)
{
	uint32_t counter=1538460;

	while(half_sec>0)
	{
		while(counter>0)
		{
			counter--;
		}

		half_sec--;

	}
}
