#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>
#define base 50
long i=base;
long c=0;
int state=1;

ISR(TIMER0_OVF_vect)
{	PORTB = i;
	if (state==1){i++;if(i==base+30){state=2;c=0;}}
	else if (state==2){i=base+30;c++;if(c==30){state=3;}}
	else if (state==3){i=i-1;if(i==base){c=0;state=4;}}
	else if (state==4){i=base;c++;if(c==70){state=5;}}
	else if (state==5){i=i-3;if(i==base-15){state=6;}}
	else if (state==6){i=i+6;if(i==base+165){state=7;}}
	else if (state==7){i=i-6;if(i==base-27){state=8;}}
	else if (state==8){i=i+3;if(i==base){c=0;state=9;}}
	else if (state==9){i=base;c++;if(c==89){state=10;}}
	else if (state==10){i++;if(i==base+55){state=11;c=0;}}
	else if (state==11){i=base+55;c++;if(c==55){state=12;}}
	else if (state==12){i--;if(i==base){state=13;c=0;}}
	else if (state==13){i=base;c++;if(c==367){state=1;}}
		
}

int main(void)
{
	DDRB = 0xFF;
	TCCR0 = 0x02;  // N=8
	TIMSK = (1 << TOIE0);
	TCNT0 = 0;
	sei();
	while(1);
	return 1;
}

