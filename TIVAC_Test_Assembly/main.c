

#include <stdint.h>

void f1 (void);
void f2 (void);

int main(void)
{
	volatile int a=0;
	volatile int b=0;

	a++;
	f1();
	b++;
	return(0);


}

void f1 (void)
{
	volatile int c=5;
	f2();
}

void  f2 (void)
{
	volatile int d=0;
	d++;
}

