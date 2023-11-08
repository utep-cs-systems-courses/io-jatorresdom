//Alternate LEDs from Off, Green, and Red
#include <msp430.h>
#include "libTimer.h"
#include "led.h"

static unsigned int led_state = 0;

int main(void) {
  P1DIR |= LEDS;
  P1OUT &= ~LED_GREEN;
  P1OUT |= LED_RED;

  configureClocks();		/* setup master oscillator, CPU & peripheral clocks */
  enableWDTInterrupts();	/* enable periodic interrupt */
  
  or_sr(0x18);		/* CPU off, GIE on */
}


void
__interrupt_vec(WDT_VECTOR) WDT()	/* 250 interrupts/sec */
{
  static int blink_count = 0; // This will control the speed of blinking to make the LED appear dim



  // Toggle the LED state based on blink_count

  if (++blink_count == 500) { // Adjust this value for LED brightness (lower is brighter)

    blink_count = 0;          // Reset counter

    led_state++;              // Move to the next state



    if (led_state > 3) {

      led_state = 0; // Reset state if it exceeds the number of states we have

    }



    // Update LEDs based on the state

    switch (led_state) {

    case 0: // All LEDs off

      P1OUT &= ~LEDS;

      break;

    case 1: // Only Green LED on

      P1OUT = (P1OUT & ~LED_RED) | LED_GREEN;

      break;

    case 2: // Only Red LED on

      P1OUT = (P1OUT & ~LED_GREEN) | LED_RED;

      break;

    case 3: // All LEDs on

      P1OUT |= LEDS;

      break;

    }

  }
} 

