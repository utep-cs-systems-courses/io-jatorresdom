#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"



int main() {

  configureClocks();
  led_init();
  switch_init();
  buzzer_init();
  // buzzer_set_period(1000); //test purpose just checking that the buzzer code works correctly
  state_machine_init();
  enableWDTInterrupts();
  
  or_sr(0x18); // CPU off, GIE on


  //  while (1) {
  //   state_machine_update();
  //  }
}

// global state var to count time

int secondCount = 0;
int top_switch = 0;


void __interrupt_vec(WDT_VECTOR) WDT(){    /* 250 interrupts/sec */
  top_switch = get_top_switches_int();

  if (top_switch) {
    secondCount++;
    if (secondCount >= 125) { /* once each sec... */
      secondCount = 0;/* reset count */
      P1OUT ^= LED_GREEN;/* toggle green LED */
      P1OUT ^= LED_RED;
    }
  }
}
