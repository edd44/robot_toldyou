/*
 * usart.c
 *
 *  Created on: 22-06-2013
 *      Author: edd
 */

#include "usart.h"
#include <avr/io.h>
#include <stdio.h>

static FILE stdio_usart = FDEV_SETUP_STREAM(USART_putchar, NULL, _FDEV_SETUP_WRITE);

int USART_init(unsigned int baudrate, unsigned char  rx_enable, unsigned char tx_enable, unsigned char rx_int_enable, unsigned char tx_int_enable)
{
	if (tx_enable == 1) UCSRB |= (1<<TXEN);
		else UCSRB &= ~(1<<TXEN);

	if (rx_enable == 1) UCSRB |= (1<<RXEN);
		else UCSRB &= ~(1<<RXEN);

	int temp = (((F_CPU / (baudrate * 16UL))) - 1);

	UBRRL = temp;
	UBRRH = (temp>>8);

	if (rx_int_enable == 1) UCSRB |= (1<<RXCIE);
		else UCSRB &= ~(1<<RXCIE);

	if (tx_int_enable == 1) UCSRB |= (1<<TXCIE);
		else UCSRB &= ~(1<<TXCIE);

	return 0;
}

int USART_putchar(char c, FILE *stream)
{
	while (!(UCSRA & (1<<UDRE)));
    if (c == '\n') USART_putchar('\r', stream);
	while (!(UCSRA & (1<<UDRE)));
	UDR = c;
    return 0;
}

int USART_stdout_redirect()
{
	stdout = &stdio_usart;
	return 0;
}

char USART_getchar()
{
	char temp;
	UCSRB &= ~(1<<RXCIE);
	while (!(UCSRA & (1<<RXC)));
	UCSRB |= (1<<RXCIE);
	temp = UDR;
	return temp;
}
