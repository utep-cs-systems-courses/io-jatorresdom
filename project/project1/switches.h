#ifndef SWITCH_INCLUDED
#define SWITCH_INCLUDED

#define SW1 BIT4
#define SW2 BIT0
#define SW3 BIT1
#define SW4 BIT2
#define SW5 BIT3
#define TOP_SWITCH (SW2 | SW3 | SW4 | SW5)

void switch_init();
void switch_interrupt_handler();
int get_top_switches_int();

#endif // SWITCH_INCLUDED

