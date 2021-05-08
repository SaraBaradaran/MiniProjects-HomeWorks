
#ifndef F_CPU
#define F_CPU 800000000UL
#endif

#define D0 eS_PORTA0
#define D1 eS_PORTA1
#define D2 eS_PORTA2
#define D3 eS_PORTA3
#define D4 eS_PORTA4
#define D5 eS_PORTA5
#define D6 eS_PORTA6
#define D7 eS_PORTA7
#define RS eS_PORTD0
#define EN eS_PORTD1


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <string.h>
#include "lcd.h"


char check_pin(char col){
	
	PORTC = 0x0E;// check if the key is in the first row
	if ((PIND & (1 << (col - '0'))) == 0){
		if(col == '4')
		return '1';
		else if(col == '5')
		return '2';
		else if (col == '6')
		return '3';
	}
	else{

		PORTC = 0x0D;// check if the key is in the second row
		if ((PIND & (1 << (col - '0'))) == 0){
			if(col == '4')
			return '4';
			else if(col == '5')
			return '5';
			else if (col == '6')
			return '6';
		}
		else{

			PORTC = 0x0B;// check if the key is in the third row
			if ((PIND & (1 << (col - '0'))) == 0){
				if(col == '4')
				return '7';
				else if(col == '5')
				return '8';
				else if (col == '6')
				return '9';
			}
			
			else{// check if the key is in the 4th row
				if(col == '4')
				return '*';
				else if(col == '5')
				return '0';
				else if (col == '6')
				return '#';
			}
		}
	}
}


char a[9];
char i = 0;
bool Floor = 0;
bool compare_pass(char* correct_pass){

	int pass = 0;
	for(int i=1; i<9; i++){
		if(a[i] == '#' && i -1 == strlen(correct_pass)){
			a[i] = ' ';
			break;
		}
		if(correct_pass[i-1] != a[i])
			return 0;
		a[i] = ' ';
	}
	return 1;
}

char passwords[9][4] = {"", "111", "222", "333", "444", "555", "666", "777", "888"};

char check_password(){

	Lcd8_Clear();
	char str[4];
	strcpy(str, passwords[a[0] - '0']);
	if( compare_pass(str) ){
		
		Lcd8_Write_String("welcome !");
		PORTB |= (1 << (a[0] - '0' - 1));

	}
	else{

		Lcd8_Write_String("wrong !");
	}
	i = 0;
	_delay_ms(5);
	Lcd8_Clear();
}

void exit_floor(){

	Lcd8_Clear();
	Lcd8_Write_String("Good Bye !");
	PORTB &= ~(1 << (a[0] - '0' - 1));
	i = 0;
	_delay_ms(5);
	Lcd8_Clear();

}

ISR(INT0_vect){

	if((PIND & (1 << 4)) == 0){// check if the first column is 0
		a[i] = check_pin('4');
	}
	else if((PIND & (1 << 5)) == 0){// check if the second column is 0
		a[i] = check_pin('5');
	}
	else if((PIND & (1 << 6)) == 0){// check if the third column is 0
		a[i] = check_pin('6');
	}
	PORTC = 0x00;
	if(Floor == 0){

		Lcd8_Set_Cursor(1,1);
		Lcd8_Write_Char(a[0]);
		Floor = 1;
		i += 1;

	}
	else{

		Lcd8_Set_Cursor(2,i);
		Lcd8_Write_Char(a[i]);
			
		if(a[i] == '#'){
			if(PORTB & (1 << (a[0] - '0' - 1)))
				exit_floor();
			else
				check_password();
			Floor = 0;
		}
		else
			i += 1;
	}

	_delay_ms(3);
}
int main(void)
{
	DDRC = 0XFF;
	PORTC = 0X00;
	DDRD = 0X03;
	PORTD = 0XFF;
	DDRA = 0XFF;
	DDRB = 0XFF;
	Lcd8_Init();
	MCUCR = 0x02;
	GICR = (1 << INT0);
	sei();
	while(1){}
	return 0;
}
