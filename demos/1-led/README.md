## Description
This program turns on the red led

Be sure to understand the manipulation of P1OUT and P1DIR.

## Suggested Activities

* Modify so that different combinations of LEDs are illuminated.

Okay 

LED_GREEN ON:
P1OUT |= LED_GREEN;
P1OUT &= ~LED_RED;

LED_GREEN AND LED_RED ON:
P1OUT |= LED_GREEN;
P1OUT |= LED_RED;

LED_GREEN AND LED_RED OFF:
P1OUT &= LED_GREEN;
P1OUT &= LED_RED;

LED_RED ON:
P1OUT &= ~LED_GREEN;
P1OUT |= LED_RED;

* Determine the impact of not setting one of the LED bits in P1DIR (and why). 

If you dont set the LED in P1DIR it would not do anything when you try to
change them in P1OUT. P1DIR can provide a path for you to control or interact
with the LEDS.
