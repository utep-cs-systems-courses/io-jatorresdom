#include <msp430.h>
#include "switches.h"
#include "led.h"
#define NUM_SWITCHES 5  // Total number of switches


// Array to hold the state of each switch
int switch_states[NUM_SWITCHES] = {0};



void switch_init() {
  P1REN |= SW1;
  P1IE |= SW1;
  P1OUT |= SW1;
  P1DIR &= ~SW1;
  P2REN |= TOP_SWITCH;
  P2IE |= TOP_SWITCH;
  P2OUT |= TOP_SWITCH;
  P2DIR &= ~TOP_SWITCH;
}



void switch_interrupt_handler() {

  char p1val = P1IN;
  P1IES |= (p1val & SW1);
  P1IES &= (p1val | ~SW1);

  // S2 RED BOARD

  if (p1val & SW1) {

    if(switch_states[0]){
      switch_states[0] = 0;
    }
    else{
      switch_states[0] = 1;
    }
  }
  
  char p2val = P2IN;
  P2IES |= (p2val & TOP_SWITCH);
  P2IES &= (p2val | ~TOP_SWITCH);

  // Check if any top switch is pressed

  //S1 GREEN BOARD

  if (p2val & SW2) {

    if (switch_states[1]){
      switch_states[1] = 0;
    }
    else{
      switch_states[1] = 1;
    }
    
  }

  // S2 GREEN BOARD

  if (p2val & SW3) {

    if (switch_states[2]){
      switch_states[2] = 0;
    }
    else{
      switch_states[2] = 1;
    }
 
  }
  
  // S3 GREEN BOARD

  if (p2val & SW4) {

    if (switch_states[3]){
      switch_states[3] = 0;
    }
    else{
      switch_states[3] = 1;
    }

  }

  //S4 GREEN BOARD

  /* up=red, down=green */

  if (p2val & SW5) {
    if (switch_states[0]){
      switch_states[0] = 0;
    }
    else{
      switch_states[0] = 1;
    }
  }

}

int* get_switches_states(){

  return switch_states; 

}

//void set_switches_states(){
//  for(int i = 0; i > (NUM_SWITCHES - 1); i++){
//    switch_states[i] = 0;
//  }
//}

void __interrupt_vec(PORT1_VECTOR) Port_1(){
  
  if (P1IFG & SW1) {      /* did a button cause this interrupt? */
    P1IFG &= ~SW1;/* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */

  }

}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  
  if(P2IFG & SW2){
    P2IFG &= ~SW2;
    switch_interrupt_handler();
  }
  else if(P2IFG & SW3){
    P2IFG &= ~SW3;
    switch_interrupt_handler();
  }
  else if(P2IFG & SW4){
    P2IFG &= ~SW4;
    switch_interrupt_handler();
  }
  else if(P2IFG & SW5){
    P2IFG &= ~SW5;
    switch_interrupt_handler();
  }

}
