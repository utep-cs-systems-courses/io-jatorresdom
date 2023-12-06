#ifndef LED_INCLUDED
#define LED_INCLUDED
#define LED_GREEN BIT0
#define LED_RED BIT6

void led_init();
void toggle_green();
void toggle_red();

#endif // LED_INCLUDED

