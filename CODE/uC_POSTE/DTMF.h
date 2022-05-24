#ifndef DTMF_H_INCLUDED
#define DTMF_H_INCLUDED
//fichier header
#include "LPC17xx.h"
//valeur global 
#define PCLK 25000000
#define DAC_freq 1000000
#define freq_init_1khz 1000 
// pinID
#define AOUT_P0_26 20

#define number_Poste_P2_7_B0_IN 14
#define number_Poste_P2_8_B1 16
#define number_Poste_P2_10_B2 20
#define number_Poste_P2_11_B3 22
#define number_Poste_P2_12_B4 24

#define Clavier_Row_1_P0_1_OUT 2
#define Clavier_Row_2_P0_2 4
#define Clavier_Row_3_P0_3 6
#define Clavier_Row_4_P0_4 8

#define Clavier_Colomn_1_P0_5_IN 10
#define Clavier_Colomn_1_P0_6 12
#define Clavier_Colomn_1_P0_9 18
#define Clavier_Colomn_1_P0_10 20

#define LED_Affichage_PassRobot_P1_20_jusq_P1_31_OUT 0xffffff
#define LED_Affichage_1st_bit 8

#define LS_baseRX_P2_1_IN 0
#define LS_posteTX_P2_0_OUT 2

#define IR_Rec_P0_23_IN 14
#define LED_Tram_Valid_P0_15_OUT 30
#define oscilloscope_P0_16_OUT 32


void init_dac();
void init_T0();
void TIMER0_IRQHandler();


#endif // DTMF_H_INCLUDED
