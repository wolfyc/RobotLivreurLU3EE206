//#include "LPC17xx.h"
#include "DTMF.h"

#define PCLK 25000000
#define DAC_freq 1000000
#define freq_init_1khz 1000 

#define AOUT_P0_26 20

unsigned int VALEUR[37] = {511,600,686,767,839,902,954,991,1014,1022,1014,991,954,902,839,767,686,600,511,422,336,256,183,120,68,31,8,0,8,31,68,120,183,256,336,422,511};
static unsigned int PN = 0;
void init_GPIO(){
	
	LPC_PINCON->PINSEL4 &= ~(3<<number_Poste_P2_7_B0_IN);
	LPC_PINCON->PINSEL4 &= ~(3<<number_Poste_P2_8_B1);
	LPC_PINCON->PINSEL4 &= ~(3<<number_Poste_P2_10_B2);
	LPC_PINCON->PINSEL4 &= ~(3<<number_Poste_P2_11_B3);
	LPC_PINCON->PINSEL4 &= ~(3<<number_Poste_P2_12_B4);
	LPC_GPIO2->FIODIR &= ~(3<<7);//input
	LPC_GPIO2->FIODIR &= ~(7<<10);

	LPC_PINCON->PINSEL0 &= ~(3<<Clavier_Row_1_P0_1_OUT);
	LPC_PINCON->PINSEL0 &= ~(3<<Clavier_Row_2_P0_2);
	LPC_PINCON->PINSEL0 &= ~(3<<Clavier_Row_3_P0_3);
	LPC_PINCON->PINSEL0 &= ~(3<<Clavier_Row_4_P0_4);
	LPC_PINCON->PINSEL0 &= ~(3<<Clavier_Colomn_1_P0_5_IN);
	LPC_PINCON->PINSEL0 &= ~(3<<Clavier_Colomn_2_P0_6);
	LPC_PINCON->PINSEL0 &= ~(3<<Clavier_Colomn_3_P0_9);
	LPC_PINCON->PINSEL0 &= ~(3<<Clavier_Colomn_4_P0_10);

	LPC_PINCON->PINSEL0 &= ~(3<<LED_Tram_Valid_P0_15_OUT);
	LPC_PINCON->PINSEL0 &= ~(3<<oscilloscope_P0_16_OUT);

	LPC_GPIO0->FIODIR |= (15<<1);//output
	LPC_GPIO0->FIODIR |= (3<<15);
	LPC_GPIO0->FIOCLR |= 15<<1 | 3<<15 ;
	LPC_GPIO0->FIODIR &= ~(3<<5);//input
	LPC_GPIO0->FIODIR &= ~(3<<9);


	LPC_PINCON->PINSEL2 &= ~(LED_Affichage_PassRobot_P1_20_jusq_P1_31_OUT << LED_Affichage_1st_bit);
	LPC_GPIO1->FIODIR |= (0xfff<<20);
	LPC_GPIO1->FIOCLR |= 0xfff<<20;

}

int Poste_Number(){
	PN = ((LPC_GPIO2->FIOPIN & (3<<7))>>7) + ((LPC_GPIO2->FIOPIN & (7<<10))>>8);
	return PN;
}

void init_Dac_DTMF(){
	LPC_SC->PCLKSEL0 &= ~(3<<22);//ASSURER QUE LHORLOGE EST A 25MHZ 
    LPC_PINCON->PINSEL1 |= (1<<AOUT_P0_26+1);//SET TO DAC ON
    LPC_PINCON->PINSEL1 &= ~(1<<AOUT_P0_26); //SET TO DAC ON
}

void init_T0(){ // timer pour controler la vitessse de lecture du tableau de valeur
	LPC_TIM0->IR = 1; // AQUITEMENT
	LPC_SC->PCLKSEL0 &= ~(3<<2); //PCLK 25MHZ
	LPC_TIM0->MR0 = DAC_freq / freq_init_1khz; // VALEUR DE COMPTEUR
	LPC_TIM0->MCR |= (3<<0) ;//INTERRUPTION & RESET DE TIMER
	LPC_TIM0->TCR |= 1; // TIMER0 ON
	NVIC_EnableIRQ(TIMER0_IRQn); // ACTIVE L'INERRUPTION
}

void TIMER0_IRQHandler(){
	LPC_TIM0->IR = 1; // AQUITEMENT
	static int index_val = 0;
	if (index_val < 37){
			LPC_DAC->DACR = (VALEUR[index_val]<<6);
			index_val++;
			if (index_val >= 37){
				index_val = 0;
			}
	}
	LPC_TIM0->TCR |= 1;
}


int main(){
    init_Dac_DTMF();
	init_T0();
	init_GPIO();
	
	unsigned int PN2 = 0;
    while(1){
			
			PN2 = Poste_Number() ;
			
			LPC_GPIO1->FIOPIN = PN2<<20;
			
			
		}
		
	}

