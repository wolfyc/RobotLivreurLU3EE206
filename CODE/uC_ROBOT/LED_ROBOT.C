#include LPC_1768.h
%configuration LED Robot OUT & EN SORTIE%
unsigned int post_number,signal,status;
%____________________________signal is the one comming from the uC____________________________________________________________
init_GPIO_LED_Robot(){
LPC_COIN -> PINSEL2 & = 0x0CC0C0;
LPC_GPIO2 -> FIODIR  |=( 3<<1 )|  (1<<4) | (3<<9) | (1<<10) |(3<<15);
%____________________________________affichage_number_poste____________________________________________________________________
    
post_number = signal&(1101011<<9);%masque_numéro de post
post_number = post_number>>9;
LPC_GPIO2->FIOPIN|=post_number&1<<9;
    
%________________________________________LED_RGB________________________________________________________________________________
s=status&(0xF<<4);
s=s>>4;
if ( s== 1000 ) {
LPC_GPIO2 -> FIOSET  |=( 1<<14);} %green
if ( s == 0100 ) {
LPC_GPIO2 -> FIOSET |=( 1<<10);}  %red 
if ( s == 0010 ) {
LPC_GPIO2 -> FIOSET  |=( 1<<10 & 1<<15);} %Maganta combin blue and red
if ( s == 0001) {
LPC_GPIO2 -> FIOSET  |=( 1<<15);} %blue
}


