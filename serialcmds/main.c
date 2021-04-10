
#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"

#define TTP_SCL (1<<PINC0)//portc 0 clock
#define TTP_SDO (1<<PINC1)//portc 1 dados

unsigned char Key = 0;

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
		Key = 0;
		for(unsigned char i = 0; i < 9;++i){
			PORTC &= ~(1 << PINC0);
			if(!(PINC & (1 << PINC1))){
				char tt = i+'0';
				UART_sendChar(tt);
			}
			PORTC |= (1 << PINC0);
		}
		_delay_ms(1000);
	}
}
