#include <avr/io.h>
#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

char OUTPUT = 0b00000001;
void SHIFT_RIGHT_TO_LEFT(){

	while((PINC & (1<<1)) == 0){

		OUTPUT = OUTPUT << 1;

		if(OUTPUT == 0){
			OUTPUT = 1;
		}
		
		PORTB = OUTPUT;
		_delay_ms(100);

	}

}
void SHIFT_LEFT_TO_RIGHT(){

	while((PINC & (1<<1)) == 0){

		OUTPUT = OUTPUT >> 1;

		if(OUTPUT == 0){
			OUTPUT = 0X80;
		}

		PORTB = OUTPUT;
		_delay_ms(100);
	}

}
int main(void)
{
	DDRC &= ~(1 << 1);
	DDRB = 0XFF;
	while((PINC & (1 << 1)) == 0){}
	
	while(1){

		SHIFT_RIGHT_TO_LEFT();
		_delay_ms(10);
		SHIFT_LEFT_TO_RIGHT();
		_delay_ms(10);
	}
	
}
