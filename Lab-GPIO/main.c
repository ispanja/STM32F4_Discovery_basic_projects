/* main.c */
#include <main.h>
int main(void)
{
int i;
gpio_init();
while(1)
{
for(i=0;i<1000000;i++);
gpio_led_state(LED3_ORANGE_ID, 1); // turn on
gpio_led_state(LED4_GREEN_ID, 1); // turn on
gpio_led_state(LED5_RED_ID, 0); // turn off
gpio_led_state(LED6_BLUE_ID, 0); // turn off
	
for(i=0;i<1000000;i++);
gpio_led_state(LED3_ORANGE_ID, 0); // turn off
gpio_led_state(LED4_GREEN_ID, 0); // turn off
gpio_led_state(LED5_RED_ID, 1); // turn on
gpio_led_state(LED6_BLUE_ID, 1); // turn on
}
}
