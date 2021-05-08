
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
#define RS eS_PORTB0
#define EN eS_PORTB1


#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

char check_pin(char col){
	
	PORTC = 0x0E;// check if the key is in the first row
	if ((PIND & (1 << (col - '0'))) == 0){
		if(col == '0')
			return '7';
		else if(col == '1')
			return '8';
		else if (col == '2')
			return '9';
		else 
			return '/';
	}
	else{

		PORTC = 0x0D;// check if the key is in the second row
		if ((PIND & (1 << (col - '0'))) == 0){
			if(col == '0')
				return '4';
			else if(col == '1')
				return '5';
			else if (col == '2')
				return '6';
			else
				return '*';
		}
		else{

			PORTC = 0x0B;// check if the key is in the third row
			if ((PIND & (1 << (col - '0'))) == 0){
				if(col == '0')
					return '1';
				else if(col == '1')
					return '2';
				else if (col == '2')
					return '3';
				else
					return '-';
			}
			
			else{// check if the key is in the 4th row
				if(col == '0')
					return 'C';
				else if(col == '1')
					return '0';
				else if (col == '2')
					return '=';
				else
					return '+';
			}
		}
	}
}


char a[8];
char i = 0;

char make_operation(){
	Lcd8_Set_Cursor(1,i+1);
	char tmp;
	if(a[1] == '+')
		tmp = (a[0] - '0') + (a[2] - '0');

	else if(a[1] == '-')
		tmp = (a[0] - '0') - (a[2] - '0');

	else if(a[1] == '*')
		tmp = (a[0] - '0') * (a[2] - '0');

	else if(a[1] == '/')
		tmp = (a[0] - '0') / (a[2] - '0');

	if(tmp <= 0xFF && tmp >= 0xF7){
		Lcd8_Write_Char('-');
		Lcd8_Set_Cursor(1,i+2);
		Lcd8_Write_Char(-tmp + '0');
	}
	else{
		Lcd8_Write_Char(tmp/10 + '0');
		Lcd8_Set_Cursor(1,i+2);
		Lcd8_Write_Char(tmp%10 + '0');
	}
}


int main(void)
{
	//DDRC for rows of the keypad 
	DDRC = 0XFF;
	PORTC = 0X00;
	//DDRD for columns of the keypad
	DDRD = 0XF0;
	PORTD = 0XFF;
	DDRA = 0XFF;
	DDRB = 0XFF;
	Lcd8_Init();
	while(1){

		if(PIND != 0XFF){// check if one column is 0
				
			if((PIND & (1 << 0)) == 0){// check if the first column is 0
				a[i] = check_pin('0');
			}
			else if((PIND & (1 << 1)) == 0){// check if the second column is 0
				a[i] = check_pin('1');
			}
			else if((PIND & (1 << 2)) == 0){// check if the third column is 0
				a[i] = check_pin('2');				
			}
			else{// check if the 4th column is 0
				a[i] = check_pin('3');
			}
			PORTC = 0x00;

			if(a[i] == 'C'){
				Lcd8_Clear();
				i = 0;
				_delay_ms(3);
				continue;
			}	
			Lcd8_Set_Cursor(1,i);
			Lcd8_Write_Char(a[i]);

			if(a[i] == '='){
				make_operation();
				continue;
			}
			i += 1;
			_delay_ms(3);
		}
	}
	return 0;
}
