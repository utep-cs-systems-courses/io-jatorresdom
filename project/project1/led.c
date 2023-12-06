#include <msp430.h>
#include "led.h"

void led_init() {
  P1DIR |= (LED_GREEN | LED_RED);
  P1OUT &= ~(LED_GREEN | LED_RED);
}

void toggle_green() {
  P1OUT ^= LED_GREEN;
}

void toggle_red() {
  P1OUT ^= LED_RED;
}

