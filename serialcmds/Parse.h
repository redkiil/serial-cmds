/*
 * Parse.h
 *
 * Created: 06/03/2021 03:43:04
 *  Author: Augusto
 */ 


void PARSE_Comma(unsigned char *toparse,unsigned char **str){
	unsigned char *token;
	unsigned char idx = 0;
	token = strtok((char *)toparse, ",");
	str[idx] = token;
	idx++;
	while(token != 0){
		token = strtok(0, ",");
		str[idx] = token;
		idx++;
	}
}