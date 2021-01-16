/* main.c */
#include <main.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <stm32f4_discovery.h>

xTaskHandle xTaskHandle1, xTaskHandle2, xTaskHandle3, xTaskHandle4;

// forward declarations of task functions
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);
void vTask4(void *pvParameters);

void vTask1(void *pvParameters)
{
		uint32_t value, tasksCount, led_state;
		tasksCount = 1; // we have only one task at this point
		led_state = 1;
		while(1)
		{
				vTaskDelay(500 / portTICK_RATE_MS); // LED blinking frequency
				gpio_led_state(LED4_GREEN_ID, led_state); // green LED
				led_state = (led_state == 1) ? 0 : 1;
				value = STM_EVAL_PBGetState(BUTTON_USER);
				if (value == 1)
				{
						// add new task
						tasksCount++;
						// keypressed - add new task
						if (tasksCount == 5)
						{
								// kill all tasks except this
								vTaskDelete(xTaskHandle2);
								vTaskDelete(xTaskHandle3);
								vTaskDelete(xTaskHandle4);
								// turn off all leds
								gpio_led_state(LED3_ORANGE_ID, 0);
								gpio_led_state(LED5_RED_ID, 0);
								gpio_led_state(LED6_BLUE_ID, 0);
								tasksCount = 1;
						}
				else
						{
								switch(tasksCount)
								{
									case 2:
											xTaskCreate(vTask2,"TASK2",
											configMINIMAL_STACK_SIZE,
											NULL, 1, &xTaskHandle2);
											break;
									case 3:
											xTaskCreate(vTask3,"TASK3",
											configMINIMAL_STACK_SIZE,
											NULL, 1, &xTaskHandle3);
											break;
									case 4:
											xTaskCreate(vTask4,"TASK4",
											configMINIMAL_STACK_SIZE,
											NULL, 1, &xTaskHandle4);
											break;
								}
						}
			}
	}
}

void vTask2(void *pvParameters)
{
	uint32_t led_state;
	led_state = 1;
	while(1)
	{
		vTaskDelay(500 / portTICK_RATE_MS); // LED blinking frequency
		gpio_led_state(LED3_ORANGE_ID, led_state); // orange LED
		led_state = (led_state == 1) ? 0 : 1;
	}
}

void vTask3(void *pvParameters)
{
	uint32_t led_state;
	led_state = 1;
	while(1)
	{
			vTaskDelay(500 / portTICK_RATE_MS); // LED blinking frequency
			gpio_led_state(LED5_RED_ID, led_state); // red LED
			led_state = (led_state == 1) ? 0 : 1;
	}
}

void vTask4(void *pvParameters)
{
	uint32_t led_state;
	led_state = 1;
	while(1)
	{
		vTaskDelay(500 / portTICK_RATE_MS); // LED blinking frequency
		gpio_led_state(LED6_BLUE_ID, led_state); // orange LED
		led_state = (led_state == 1) ? 0 : 1;
	}
}


int main(void)
{
 gpio_init();
 STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
 xTaskCreate(vTask1, "TASK1", configMINIMAL_STACK_SIZE, NULL, 1, &xTaskHandle1);
 vTaskStartScheduler();
}
