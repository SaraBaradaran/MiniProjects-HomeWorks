#define RightSensor1 1
#define RightSensor2 0
#define Emitter 2
#define LeftSensor1 3
#define LeftSensor2 4

#define SensorPin PINB
#define DDRSensor DDRB
#define MotorPort PORTA
#define DDRMotor DDRA

#define MaxSpeed 200

#include <avr/io.h>

#include "util/delay.h"
#define F_CPU 8000000UL

void Initial()
{
	DDRSensor=0x00;
	DDRMotor=0xFF;
	SensorPin=0x00;
	MotorPort=0x06;
}

void Straight()
{
	//_delay_ms(40);
	MotorPort ^= 0b01010000;
}

void TurnLeft()
{
	//_delay_ms(50);
	MotorPort ^= 0b01010000;
	_delay_ms(0.15);
	MotorPort ^= 0b00010000;
}

void TurnRight()
{
	//_delay_ms(50);
	MotorPort ^= 0b01010000;
	_delay_ms(0.15);
	MotorPort ^= 0b01000000;
}

void stop()
{
	MotorPort = 0x00;
}

int main(void)
{
	Initial();
	
	while(1){

		if((PINB & (1 << 2)) == 0){
			Straight();
			MotorPort |= 0x06;
		}
		else if ((PINB & (1 << 3)) == 0){
			MotorPort |= 0x06;
			TurnRight();
		}
		else if ((PINB & (1 << 0)) == 0){
			MotorPort |= 0x06;
			TurnLeft();
		}
		else if ((PINB & (1 << 4)) == 0){
			MotorPort |= 0x06;
			TurnRight();
		}
		else if ((PINB & (1 << 1)) == 0){
			MotorPort |= 0x06;
			TurnLeft();
		}
		else{
			stop();
		}
	}
	
	return 0;
}


