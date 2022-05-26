#include "LPC17xx.h"

void Pin_Init()
{
	// Scope Display
	LPC_PINCON->PINSEL0&=~(3<<0);
	LPC_GPIO0->FIODIR|=(1<<0);
	
	//  Number of posts
	LPC_PINCON->PINSEL4&=~(0x3FF<<18);
	LPC_GPIO2->FIODIR&=~(0x1F<<9);
	
	// Number of Robots
	LPC_PINCON->PINSEL3&=~(0xFF<<16);
	LPC_GPIO1->FIODIR&=~(0x1F<<9);
	
	//Series Communication with Supervision
	
	// Transmition
	
	LPC_PINCON->PINSEL4|=1<<1;
	LPC_PINCON->PINSEL4&=~(1<<0);

	// Reception
	
	LPC_PINCON->PINSEL4|=1<<3;
	LPC_PINCON->PINSEL4&=~(1<<2);
	
		//Series Communication with Poste
	
	// Transmition
	
	LPC_PINCON->PINSEL4|=1<<17;
	LPC_PINCON->PINSEL4&=~(1<<16);

	// Reception
	
	LPC_PINCON->PINSEL4|=1<<19;
	LPC_PINCON->PINSEL4&=~(1<<18);
	
	// PWM Signal to the Wire
	
	LPC_PINCON->PINSEL4|=1<<10;
	LPC_PINCON->PINSEL4&=~(1<<11);
	
}









int main ()
{
	
	while (1); 
	
	return 0;
}