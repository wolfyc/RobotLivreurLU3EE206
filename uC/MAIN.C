#include "LPC17xx.h"

unsigned char test = 0;
void init_proc(void){
	LPC_GPIO2->FIODIR = 0xFF;
}
	int main(void){
		init_proc();
		while(1){
			test++;
			LPC_GPIO2->FIOPIN = test;
		}
	}