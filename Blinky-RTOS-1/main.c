/* main.c */
#include <main.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

void vTask1(void *pvParameters)
{
while(1)
	{
	gpio_led_state(LED5_RED_ID, 1); // turn off
	gpio_led_state(LED6_BLUE_ID, 1); // turn off
	vTaskDelay(1000 / portTICK_RATE_MS); // delay 1s
	gpio_led_state(LED5_RED_ID, 0); // turn on
	gpio_led_state(LED6_BLUE_ID, 0); // turn on
	vTaskDelay(1000 / portTICK_RATE_MS); // delay 1s
	}
}


int main(void)
{
	gpio_init();
// create task	
	xTaskCreate(
					vTask1, 				// pointer to task function
					(const char*)"TASK1", 		// task name
					configMINIMAL_STACK_SIZE, 		// stack size
					NULL, 				// task input parameters - not used
					1, 						// task priority
					NULL); 				// task handle - not used
		// run task scheduler
		vTaskStartScheduler();
}
