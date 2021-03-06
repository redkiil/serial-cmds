
#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char buffer[64];

int main()
{
	DDRB |= (1<<PINB0);
	unsigned int ubrr = MYUBRR;
	UBRR0H = (ubrr>>8);
	UBRR0L = (ubrr);
	
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	
	while (1)
	{
		UART_receiveString(buffer);
		if(!strcmp(buffer,"LED\n")){
			PORTB |= (1<<PINB0);
		}else if(!strcmp(buffer,"LEDOFF\n")){
			PORTB &= ~(1<<PINB0);
		}
		
		UART_sendString(buffer);
	}
}