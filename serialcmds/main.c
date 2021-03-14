
#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UART.h"

unsigned long int microsecs = 0;
volatile unsigned long int millisecs = 0;
unsigned char times = 0;

unsigned long int last = 0;
unsigned char test = 0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 5;
	millisecs += 1;
}
int main()
{
	unsigned int ubrr = MYUBRR;
	UBRR0H = (ubrr>>8);
	UBRR0L = (ubrr);
	
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	
	DDRD = (1<<PIND6);
	PORTD &= ~(1<<PIND6);
	
	TCCR0B = (1<<CS01) | (1<<CS00);
	
	TIMSK0 = (1<<TOIE0);
	
	TCNT0 = 5;
	
	sei();

	while (1)
	{
		if(test){
		if((millisecs-last) >= 100){
			if(times == 12){
				times = 0;
			}
			if(times <4)PORTD ^= (1<<PIND6);
			times++;
			last = millisecs;
		}	
		}else{
			times = 0;
			PORTD &= ~(1<<PIND6);
		}
		
		unsigned char play[64];
		UART_receiveString(play);
		UART_sendString(play);
		if(!strcmp((const char*)play,"LED\n")){
			test = !test;
		}
	}
}
