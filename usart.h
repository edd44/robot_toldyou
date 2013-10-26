/*
 * usart.h
 *
 *  Created on: 22-06-2013
 *      Author: edd
 */

#include <avr/io.h>
#include <stdio.h>



int USART_init(unsigned int baudrate, unsigned char  rx_enable, unsigned char tx_enable, unsigned char rx_int_enable, unsigned char tx_int_enable);
int USART_putchar(char c, FILE *stream);
int USART_stdout_redirect();
char USART_getchar();
