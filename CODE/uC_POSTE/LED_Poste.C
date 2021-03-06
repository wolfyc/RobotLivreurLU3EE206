#include LPC_1768.h
unsigned int status;
unsigned int robot_number;
unsigned int vitesse;
unsigned int s;

%signal qui arrive de uC
init_GPIO_LED(){
%______________________________________affichege_robot_number___________________________________________________________________
LPC_GPIO1-> FIOCLR |=0xFFF00000;
robot_number= status&(0xF<<12);
robot_number=number_robot >> 12;
LPC_GPIO1->FIOPIN|=number_robot&1<<20;

%_______________________________________affichage_vitesse_robot__________________________________________________________________

vitesse = status &(0xF<<8);
vitesse = vitesse>>8;
LPC_GPIO1->FIOPIN|=vitesse&1<<24;

%__________________________________________affichage_status_robot_________________________________________________________________
s=status&(0xF<<4);
s=s>>4;
LPC_GPIO1->FIOPIN|=(s&1<<27);

%__________________________________________affichage_LED_IR________________________________________________________________________
unsigned int tram;
tram= robot_number +vitesse + s ;

%______________________________________________2_s_complement_______________________________________________________________________
tram=~tram;
tram=tram+1;
T= status&(0xF);
if  (tram == T ) {
    LPC_GPIO0->FIOSET |= (1<<15);
}
}
