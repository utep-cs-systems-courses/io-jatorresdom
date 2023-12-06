#include <msp430.h>
#include "switches.h"
#include "led.h"

int top_switches_int = 0;

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
  char p2val = P2IN;
  P2IES |= (p2val & TOP_SWITCH);
  P2IES &= (p2val | ~TOP_SWITCH);

  // Check if SW1 is pressed
  // Check if any top switch is pressed

  if (p2val & TOP_SWITCH) {
    if(top_switches_int){
      top_switches_int = 0;
    }
    else {
      top_switches_int = 1;
    }
  }
}

int get_top_switches_int(){

  return top_switches_int;
  

}

void __interrupt_vec(PORT1_VECTOR) Port_1(){
  
  if (P1IFG & SW1) {      /* did a button cause this interrupt? */

    P1IFG &= ~SW1;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */

  }

}

void __interrupt_vec(PORT2_VECTOR) Port_2(){
  
  if (P2IFG & TOP_SWITCH) {

    P2IFG &= ~TOP_SWITCH;
    switch_interrupt_handler();
  }

}
