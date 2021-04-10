
#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "TTP229.h"

int main()
{
	unsigned int ubrr = MYUBRR;
	UBRR0H = (ubrr>>8);
	UBRR0L = (ubrr);
	
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	
	DDRC |= (1<<PINC0);
	

	while (1)
	{
		UART_sendChar(TTP229_readKeypad());
		_delay_ms(50);
	}
}
