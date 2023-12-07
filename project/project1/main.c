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
int secondCount = 0;
int case_int = 0;


void __interrupt_vec(WDT_VECTOR) WDT(){    /* 250 interrupts/sec */

  states = get_switches_states();

  if(states[0]){
    secondCount++;
    if(secondCount >= 125){
      toggle_red();
      toggle_green();
      secondCount = 0;
    }
  }

  if (temp) {
    secondCount++;
    if(secondCount >= 125) {
      secondCount = 0;
      case_int++;
    }
    switch(case_int){
    case 0:
      toggle_red();
      toggle_green();
      break;
    case 1:
      toggle_green();
      toggle_red();
      break;
    case 2:
      toggle_green();
      toggle_red();
      break;
    case 3:
      toggle_red();
      toggle_green();
      break;
    case 4:
      toggle_red();
      toggle_green();
      break;
    case 5:
      toggle_red();
      case_int = 0;
      break;
    default:
      led_init();
      break;
    }   
   }
}
