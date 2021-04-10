/*
 * TTP229.h
 *
 * Created: 10/04/2021 05:00:07
 *  Author: Augusto
 */ 

unsigned char Key = 0;
unsigned char KeyH = 0;
char tes = 0;

char TTP229_readKeypad(){
	Key = 0;
	tes = 0;
	PORTC |= (1 << PINC0);
	_delay_us(10);
	PORTC &= ~(1 << PINC0);
	for(unsigned char i = 0; i < 8;++i){
		PORTC |= (1 << PINC0);
		if(!(PINC & (1 << PINC1))){
			Key = i+1;
		}
		PORTC &= ~(1 << PINC0);
	}
	if(Key==0)KeyH = 0;
	if(Key>0 && KeyH ==0){
		KeyH = 1;
		tes = Key+'0';
	}
	return tes;
}