#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

//temp variable (testing purposes)
int temp = 0;

//Holds the switches states 1 or 0
int* states;


//Notes for Megalovania and note length
int mMelody[] = {

  586,
  0,   
  586, 
  0,   
  1174, 
  0,   
  830, 
  0,   
  880, 
  0,   
  920, 
  0,   
  950,
  0,
  586,
  0,
  950,
  0,
  950,
  0,
  920,
  0,
 
};
float mDuration[] = {

  .14,
  .14,
  .122,
  .122,
  .248,
  .248,
  .368,
  .368,
  .256,
  .256,
  .242,
  .242,
  .251,
  .251,
  .121,
  .121,
  .128,
  .128,
  .121,
  .1,
  .242,
  .242
  
};


//Notes for shooting stars

int sMelody[] = {

  586,
  0,   
  586, 
  0,   
  1174, 
  0,   
  830, 
  0,   
  880, 
  0,   
  920, 
  0,   
  950,
  0,
  586,
  0,
  950,
  0,
  950,
  0,
  920,
  0,
 
};
float sDuration[] = {

  .14,
  .14,
  .122,
  .122,
  .248,
  .248,
  .368,
  .368,
  .256,
  .256,
  .242,
  .242,
  .251,
  .251,
  .121,
  .121,
  .128,
  .128,
  .121,
  .1,
  .242,
  .242
};

//Check if -1 for no song 0 for megalovania 1 for shootings stars
int play = -1;


void play_method(int melody[], float duration[],int play_m){

  if (play_m == 0) {
    play_note(melody[temp],duration[temp]);
    temp++;
    if(temp > 19) {
      temp = 0;
      toggle_green();
      play_method(melody,duration,-1);
      return;
    }else{
      play_method(melody,duration,0);
    }
  }
}


int main() {

  configureClocks();
  led_init();
  // toggle_red();
  //  toggle_green();  //testing led that they are on respectively
  switch_init();
  buzzer_init();
  // buzzer_set_period(1000); //test purpose just checking that the buzzer code works correctly
  
  enableWDTInterrupts();
  
  or_sr(0x18); // CPU off, GIE on

}

// global state var to count time
int reset_switches = 0;
int secondCount = 0;
int case_int = 0;



void __interrupt_vec(WDT_VECTOR) WDT(){    /* 250 interrupts/sec */

  states = get_switches_states();

  //Blinks both lights 10 times every half second with the switch in the red board

  if(states[0]){
    secondCount++;
    if(secondCount >= 60){
      reset_switches++;
      toggle_red();
      toggle_green();
      secondCount = 0;
      if(reset_switches >= 20){
	play_note(1000,3);
	reset_switches = 0;
	set_switches_states();
      }
    }
  }

    if(states[1]){
      if(secondCount >= 125){
	case_int++;
	secondCount = 0;
      }
      switch(case_int){
      case 0:
	if(!secondCount){
	  toggle_red();
	}
      break;
      case 1:
	if(!secondCount){
	  toggle_green();
	}
      break;
      case 2:
	if(!secondCount){
	  toggle_red();
	  toggle_green();
	}
      break;
      case 3:
	if(!secondCount){
	  toggle_red();
	  toggle_green();
	}
      break;
      case 4:
	if(!secondCount){
	  toggle_red();
	  toggle_green();
	}
      break;
      case 5:
	if(!secondCount){
	  set_switches_states();
	  case_int = 0;
	}
	break;
      }
      secondCount++;
    }
  

  if(states[2]){
    secondCount++;
    if(secondCount >= 125){
      reset_switches++;
      toggle_green();
      secondCount = 0;
      if(reset_switches >= 20){
  	reset_switches = 0;
  	set_switches_states();
      }
    }
  }
  

  
  if(states[3]){
    toggle_green();
    play_method(mMelody,mDuration,0);
    play_method(mMelody,mDuration,0);
    set_switches_states();
    //secondCount++;
   }
}
