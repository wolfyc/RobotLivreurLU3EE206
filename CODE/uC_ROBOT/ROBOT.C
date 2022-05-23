#include "LPC17xx.h"

int T0clk =25000000;
int i =0 ;
int T_mes=10;
int mes=0 ;
int f ;
unsigned int VALEUR[36] = {511,611,707,795,872,936,983,1012,1022,\
	1012,983,936,872,795,707,611,511,411,315,227,150,86,39,10,0,10,39,86,150,227,315,411,511,611,707,795};

void init_Telemetre ()
	{
// Initialisation of the pins 
		
//Initialisation of the output 		
		LPC_PINCON->PINSEL0&=~(3);
		LPC_GPIO0-> FIODIR|=1;
		LPC_GPIO0-> FIOPIN|=1;
		
//Initialisation of the switches 	(Meas frequency )	
		
		LPC_PINCON->PINSEL0&=~((3<<2)|(3<<4));
		LPC_GPIO0-> FIODIR&=~(3<<1);
		mes=(LPC_GPIO0-> FIOPIN)&(3<<1);
		mes=(mes>>1);
		mes=mes^3;
		
switch(mes)
{
  case 0:
  T_mes=10;
  break;
  case 1:
  T_mes=15;
  break;
  case 2:
  T_mes=20;
  break;
  case 3:
  T_mes=25;
  break;
	
  default:
	T_mes=10;
}
		

		
		
// Initialisation of the timer 0 for Ultrasound emition !

	// Falling edge to start emission 	
		
		LPC_TIM0->MR0=0;
		LPC_TIM0->MCR|=1;
		LPC_TIM0->MCR&=~(3<<1);
		
	// Rising edge to end the pulse 	
	
		LPC_TIM0->MR1=200;
		LPC_TIM0->MCR|=(1<<3);
		LPC_TIM0->MCR&=~(3<<4);

	// Reset	
		LPC_TIM0->MR2=((1/((float)T_mes)))*T0clk;
		LPC_TIM0->MCR|=(1<<7);
		
	
		
		NVIC_EnableIRQ(TIMER0_IRQn);
		LPC_TIM0->TCR|=1;
		
		
		//RECEPTION 
		LPC_PINCON->PINSEL3|=(3<<20);
		LPC_TIM0->CCR=1;
		
	}

void TIMER0_IRQHandler()
	{
		LPC_TIM0->IR|=(1<<i);
		i^=1;
		LPC_GPIO0-> FIOPIN^=1;
	}

	void Obstacle_Warning()
	{
		LPC_TIM1->MR0=0.25*T0clk;
		LPC_TIM1->MCR|=(1<<0);
		LPC_TIM1->MCR&=~(3<<1);
		
		LPC_TIM1->MR1=1000*T0clk;
		LPC_TIM1->MCR|=(3<<3);
		LPC_TIM1->MCR&=~(1<<5);
		
		NVIC_EnableIRQ(TIMER1_IRQn);
				
	
	};
	void TIMER1_IRQHandler()
	{
		LPC_TIM1->IR|=(1<<i);
		i^=1;
				
	}
	
	
int main(void)

float dist ;

	{
		init_Telemetre();
		while(1)
		{
		dist = (349*(LPC_TIM0->CR0)/T0clk)/2;
			
			if (dist>100)
			{
				// don't emmit the sound
				LPC_TIM1->TCR=2;
				LPC_DAC->DACR=0;
			}
			else
				if (dist>20)
			{
				LPC_TIM1->TCR=1;
				f=(10-(d/0.1))*0.25+0.5;
				sound_emmit();
			}
			  LPC_TIM1->MR1=(1/(float)f)*T0clk;
			
		}; 		// Waiting mode 
		
		return 0;
	}
	


	void  sound_emmit()	
	{
	  LPC_PINCON->PINSEL1&=~(1<<20);
		LPC_PINCON->PINSEL1|=	(1<<21);
		LPC_DAC->DACR=Value[n];
		n++;
		
		if (n>35)
		{
			n=0;
		}
				
	}