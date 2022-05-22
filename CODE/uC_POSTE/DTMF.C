//#include "LPC17xx.h"
#include "DTMF.h"

#define PCLK 25000000
#define freq_init_1khz 1000 

unsigned int VALEUR[36] = {511,611,707,795,872,936,983,1012,1022,\
	1012,983,936,872,795,707,611,511,411,315,227,150,86,39,10,0,10,39,86,150,227,315,411,511,611,707,795};

void init_dac(){
	LPC_SC->PCLKSEL0 &= ~(3<<22);//ASSURER QUE LHORLOGE EST A 25MHZ 
    LPC_PINCON->PINSEL1 |= 1<<21;//SET TO DAC ON
    LPC_PINCON->PINSEL1 &= ~(1<<20); //SET TO DAC ON
}

void init_T0(){ // timer pour controler la vitessse de lecture du tableau de valeur
	LPC_TIM0->IR = 1; // AQUITEMENT
	LPC_SC->PCLKSEL0 &= ~(3<<2); //PCLK 25MHZ
	LPC_TIM0->MR0 = PCLK / freq_init_1khz; // VALEUR DE COMPTEUR
	LPC_TIM0->MCR |= (3<<0) ;//INTERRUPTION & RESET DE TIMER
	LPC_TIM0->TCR |= 1; // TIMER0 ON
	NVIC_EnableIRQ(TIMER0_IRQn); // ACTIVE L'INERRUPTION
}

void TIMER0_IRQHandler(){
	LPC_TIM0->IR = 1; // AQUITEMENT
	static int index_val = 0;
	if (index_val < 36){
			LPC_DAC->DACR = (VALEUR[index_val]<<6);
			index_val++;
			if (index_val >= 36){
				index_val = 0;
			}
	}
	LPC_TIM0->TCR |= 1;
}


int main(){
    init_dac();
	init_T0();
    while(1){
		
		}
		
	}

