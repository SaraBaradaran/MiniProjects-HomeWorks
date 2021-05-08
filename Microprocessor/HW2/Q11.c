#include <avr/io.h>
#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#include <avr/pgmspace.h>
const unsigned char PROGMEM lookup[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int main(){
	
	DDRD = 0XFF;
	DDRC &= 0b11111100;
	char counter = 0;
	PORTD = pgm_read_byte(&(lookup[counter]));

	while(1){ //PINC0 FOR UP COUNTING AND PINC1 FOR DOWN COUNTING
		
		if((PINC & 0b00000010) != 0){
			_delay_ms(400);
			counter -= 1;
			PORTD = pgm_read_byte(&(lookup[counter]));
		}
		if((PINC & 0b00000001) != 0){
			_delay_ms(400);
			counter += 1;
			PORTD = pgm_read_byte(&(lookup[counter]));

		}
	}
}