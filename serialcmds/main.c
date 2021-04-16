
#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"
#include "TTP229.h"

int dutyCycle = 0;

int main()
{
	DDRB |= (1<<PINB0);
	unsigned int ubrr = MYUBRR;
	UBRR0H = (ubrr>>8);
	UBRR0L = (ubrr);
	
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	
	DDRC |= (1<<PINC0);

	DDRD |= (1<<PIND5);
	
	TCCR0A = (1<<COM0B1) | (1<<WGM00) | (1<<WGM01);
	TIMSK0 = (1<<TOIE0);

	OCR0B = 100;


	sei();

	TCCR0B = (1<<CS00) | (1<<CS01);

	while (1)
	{
		unsigned char play[64];
		UART_receiveString(play);
		if(play[0] != '\0'){
			dutyCycle = atoi((const char*)play);
			UART_sendString(play);
		}
		
	}
}
ISR(TIMER0_OVF_vect){
	OCR0B = (dutyCycle/100.0)*255;
}