#include "common.h"

uint8_t read=0;
uint32_t dataBuffer[8];
int32_t data[2000];
uint8_t flag=0;
int32_t ia=0;
uint32_t counter=0;

int main(void)
{
	HAL_init();
	HallSensor_init();
	MotorDrive_init();
	HAL_TimerInt_enable(TIMER0_BASE,INT_TIMER0A,TIMER_TIMA_TIMEOUT );
	HAL_MasterInt_enable();
	HAL_Timer_enable(TIMER0_BASE, TIMER_A);


	while(1)
	{

	}
}


void Timer0IntHandler(void)
{
	// Clear the timer interrupt
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	HallSensor_read(&read);
	MotorDrive_update(read, HAL_MAX_DUTY);
	HAL_readAdcData(ADC0_BASE, HAL_SS0, dataBuffer);
	if (counter<2000)
	{
			data[counter]=dataBuffer[0];
			counter++;
	}


}
