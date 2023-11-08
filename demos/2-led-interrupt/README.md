## Description

This program confirms that at least one periodic interrupt occurs.

It (1) sets up P1 to control the LEDS, (2) enables periodic
interrupts, and then (3) the the periodic interrrupt (repeatedly turns
on the red LED.

## Suggested Activities

* Modify so that different combinations of LEDs are illuminated.

Setup a little switch state machine that count the interrumpt which changes
the state and also will reset into the first state and repeat

* Try to modify the interrupt handler so that an LED flashes on and off
  quickly (and thereby appears dimmer).

in this case we can modify the blink_count to be lower so that it can be
dimmer light.
