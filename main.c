/*
 * main.c
 *
 *  Created on: 08-08-2013
 *      Author: edd
 */
#include "usart.h"
#include <util/delay.h>
#define F_CPU 8000000 UL

#define up 1
#define down 2
#define left 4
#define right 8
#define button_B 0x10
#define button_C 0x20

void go_forward()
{
	//printf("do przodu!!!\n");
	PORTD = 0x80;
	PORTB = 0x80;
}

void go_backward()
{
	//printf("do ty³u!!!\n");

	PORTD = 0x40;
	PORTB = 0x40;
}

void stop()
{
	//printf("STOP!");

	PORTD = 0x00;
	PORTB = 0x00;
}

void turn_left()
{
	//printf("w lewo!");
	PORTD = 0x00;
	PORTB = 0x80;
}

void turn_left_corner()
{
	printf("w lewo! korner");
	PORTD = 0x40;
	PORTB = 0x80;
}

void turn_right()
{
	//printf("w prawo!");
	PORTD = 0x80;
	PORTB = 0x00;
}

void turn_right_corner()
{
	//printf("w prawo!");
	PORTD = 0x80;
	PORTB = 0x40;
}

void button_B_pressed()
{
	//printf("B\n!");
}

void button_C_pressed()
{
	//printf("C\n!");
}

int main()
{
	int buttons[8];
	USART_init(9600,1,1,0,0);
	USART_stdout_redirect();
	DDRC = 0x00;


	DDRD = 0xC0;
	DDRB = 0xC0;
	PORTD = 0x0;
	PORTB = 0x0;

 for(;;)
 {
	 /*_delay_ms(100);
	 portc_high = PINC & 0x3F;
	 printf("%c",portc_high);*/
	 _delay_ms(100);
	 /*
	 if ((PINC | ~up) == ~up) go_forward();
	 else
	 {
		 if ((PINC | ~down) == ~down) go_backward();
		 else
		 {
			 if ((PINC | ~left) == ~left) turn_left();
			 else
			 {
				 if ((PINC | ~right) == ~right) turn_right();
				 else
				 			 {
				 				 if ((PINC | ~(button_B & left)) == ~(button_B & left)) turn_left_corner;
				 				 else
				 								 			 {
				 								 				 if ((PINC | ~button_C) == ~button_C) button_C_pressed();
				 								 				 else stop();
				 								 			 }
				 			 }


			 }
		 }
		 */
	 if ((PINC | ~up) == ~up) buttons[0]=1;
	 else buttons[0]=0;

	 if ((PINC | ~down) == ~down) buttons[1]=1;
	 else buttons[1]=0;

	 if ((PINC | ~left) == ~left) buttons[2]=1;
	 else buttons[2]=0;

	 if ((PINC | ~right) == ~right) buttons[3]=1;
	 else buttons[3]=0;

	 if ((PINC | ~button_B) == ~button_B) buttons[4]=1;
	 else buttons[4]=0;

	 if (buttons[0]==1) go_forward();
	 //else stop();
	 if (buttons[1]==1) go_backward();
	// else stop();
	 if (buttons[2]==1)
		 {
		 if (buttons[4]==1) turn_left_corner();
		 else turn_left();
		 }
	 //else stop();
	 if (buttons[3]==1)
	 {
	 	if (buttons[4]==1) turn_right_corner();
	 	else turn_right();
	 }
	 //else stop();

	 if (buttons[0]==0 & buttons[1]==0 & buttons[2]==0 & buttons[3]==0) stop();





 }
 return 0;
}
