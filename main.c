/*
 * main.c
 *
 *  Created on: 08-08-2013
 *      Author: edd
 */
#include "usart.h"
#include <util/delay.h>
#include <avr/interrupt.h>
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
	//printf("w lewo! korner");
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


int i = 0;
int rx_complete = 0;
char buffer[16];

ISR(USART_RXC_vect)
{
	//char temp = UDR;
	//printf("%d", i);
	buffer[i] = UDR;
	i++;

	if (i == 16)
	{
		//printf("all\n");
		rx_complete = 1;
		i = 0;
	}
	//printf("%c-", temp);

}

unsigned char ConvertTwoCharsToByte(char Hchar, char Lchar)
{
	char temp_Hchar, temp_Lchar, result;
	if (Hchar >= 'A' && Hchar <= 'F') temp_Hchar=Hchar-'A'+0xA;
	if (Hchar >= 'a' && Hchar <= 'f') temp_Hchar=Hchar-'a'+0xA;
	if (Hchar >= '0' && Hchar <= '9') temp_Hchar=Hchar-'0';

	if (Lchar >= 'A' && Lchar <= 'F') temp_Lchar=Lchar-'A'+0xA;
	if (Lchar >= 'a' && Lchar <= 'f') temp_Lchar=Lchar-'a'+0xA;
	if (Lchar >= '0' && Lchar <= '9') temp_Lchar=Lchar-'0';

	result = temp_Hchar * 16 + temp_Lchar;

	return result;
}

int main()
{
	int buttons[15];
	USART_init(19200,1,1,1,0);
	USART_stdout_redirect();
	DDRC = 0x00;


	DDRD = 0xC0;
	DDRB = 0xC0;
	PORTD = 0x0;
	PORTB = 0x0;
	sei();

 for(;;)
 {
	 int x;
	 if (rx_complete != 0)
	 {
		 rx_complete = 0;
		 //printf("gotit\n");
		 /*for(x=0;x<16;x++)
		 {
			 printf("%c", buffer[x]);
		 }*/
		 /*for (x=0;x<16;x+=2)
		 {
			 printf("%x", ConvertTwoCharsToByte(buffer[x], buffer[x+1]));
		 }*/
		 /*for(x=0;x<7;x++)
		 {
			buttons[x] = ConvertTwoCharsToByte(buffer[2*x], buffer[2*x+1]);
			printf("%d ", buttons[x]);
		 }*/
	 }
	 //printf("-");

	 //SEGA pad button check-----------------------------------------------------------
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
	 //--------------------------------------------------------------------------------

	 if (buttons[0]!=0) go_forward();
	 //else stop();
	 if (buttons[1]!=0) go_backward();
	// else stop();
	 if (buttons[2]!=0)
		 {
		 if (buttons[4]!=0) turn_left_corner();
		 else turn_left();
		 }
	 //else stop();
	 if (buttons[3]!=0)
	 {
	 	if (buttons[4]!=0) turn_right_corner();
	 	else turn_right();
	 }
	 //else stop();

	 if (buttons[0]==0 && buttons[1]==0 && buttons[2]==0 && buttons[3]==0) stop();





 }
 return 0;
}
