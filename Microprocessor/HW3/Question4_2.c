#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>
#define base 50
float i=base;
long c=0;
int state=1;
float bounds[13]={30,30,30,70,5,30,32,9,89,55,55,55,367};

int binaryToDecimal(int n)
{
	int num = n;
	int dec_value = 0;
	int b = 1;
	
	int temp = num;
	while (temp) {
		int last_digit = temp % 10;
		temp = temp / 10;
		
		dec_value += last_digit * b;
		
		b = b * 2;
	}
	
	return dec_value;
}

ISR(TIMER0_OVF_vect)
{	PORTB = i;
	if(PINC!=0x00)
	{
		int x=binaryToDecimal(PINC);
		for(int j=0;j<13;j++)
		{
			if(PIND & 0x01)
			bounds[j]+=(x/13);
			else
			bounds[j]-=(x/13);
		}
	}
	
	if (state==1){i=i+(float)30/bounds[state-1];if(i==base+30){state=2;c=0;}}
	else if (state==2){c++;if(c==bounds[state-1]){state=3;}}
	else if (state==3){i=i-(float)30/bounds[state-1];if(i==base){c=0;state=4;}}
	else if (state==4){c++;if(c==bounds[state-1]){state=5;}}
	else if (state==5){i=i-(float)15/bounds[state-1];if(i==base-15){state=6;}}
	else if (state==6){i=i+(float)180/bounds[state-1];if(i==base+165){state=7;}}
	else if (state==7){i=i-(float)192/bounds[state-1];if(i==base-27){state=8;}}
	else if (state==8){i=i+(float)27/bounds[state-1];if(i==base){c=0;state=9;}}
	else if (state==9){c++;if(c==bounds[state-1]){state=10;}}
	else if (state==10){i=i+(float)55/bounds[state-1];if(i==base+55){state=11;c=0;}}
	else if (state==11){c++;if(c==bounds[state-1]){state=12;}}
	else if (state==12){i=i-(float)55/bounds[state-1];if(i==base){state=13;c=0;}}
	else if (state==13){c++;if(c==bounds[state-1]){state=1;}}
	
}

int main(void)
{
	DDRB = 0xFF;
	TCCR0 = 0x02;  // N=8
	DDRC=0x00;
	DDRD=0x00;
	TIMSK = (1 << TOIE0);
	TCNT0 = 0;
	sei();
	while(1){};
	return 1;
}

