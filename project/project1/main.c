#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

int* states;

int main() {

  configureClocks();
  led_init();
  // toggle_red();
  //  toggle_green();  //testing led that they are on respectively
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

int temp = 0;
int reset_switches = 0;
int secondCount = 0;
int case_int = 0;


void __interrupt_vec(WDT_VECTOR) WDT(){    /* 250 interrupts/sec */

  states = get_switches_states();

  //Blinks both lights 10 times every half second with the switch in the red board

  if(states[0]){
    secondCount++;
    if(secondCount >= 125){
      reset_switches++;
      toggle_red();
      toggle_green();
      secondCount = 0;
      if(reset_switches >= 20){
	reset_switches = 0;
	set_switches_states();
      }
    }
  }
}
