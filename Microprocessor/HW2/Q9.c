#include <avr/io.h>
#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>


void func(void)
{
	asm ("in r16,0x13");
	asm ("rol r16");
	asm ("ror r20");
	asm ("out 0x12,r20");
}


int main(void)
{
	DDRB=0xFF;
	DDRC=0x00;
	DDRA=0x00;
	DDRD=0xFF;
	PORTB=0x00;
	PINC=0x00;
	char i=0;

	while (1)
	{
		_delay_ms(300);
		if(PINC==0x80)
		{
			PORTB=PORTB | (1<<i);
		}
		if(i<0x08)
		{
			func();
			i++;
		}
		PORTA=i;
	}
	return 0;
}

