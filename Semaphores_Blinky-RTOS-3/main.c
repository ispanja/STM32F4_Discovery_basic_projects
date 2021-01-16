/* main.c */
#include <main.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <stm32f4_discovery.h>

void vTaskHigh(void *pvParameters);
void vTaskLow(void *pvParameters);
xSemaphoreHandle xBinarySemaphore;

void vTaskHigh(void *pvParameters)
{
portTickType t1, t2;
 gpio_led_state(LED5_RED_ID, 0); // red LED off
 while(1)
 {
 xSemaphoreTake(xBinarySemaphore, portMAX_DELAY);
 gpio_led_state(LED5_RED_ID, 1); // red LED on
 t1 = xTaskGetTickCount();
 while(1)
 {
 t2 = xTaskGetTickCount();
 // wait for 2 seconds non-blocking
 if (((t2 - t1) * portTICK_RATE_MS) >= 2000) break;
 }
 gpio_led_state(LED5_RED_ID, 0); // red LED off
 }
}

void vTaskLow(void *pvParameters)
{
	uint32_t led_state, value;
	led_state = 1; // ON
	while(1)
	{
		gpio_led_state(LED4_GREEN_ID, led_state);
		led_state = (led_state == 1) ? 0 : 1;
		value = STM_EVAL_PBGetState(BUTTON_USER);
		if (value == 1) xSemaphoreGive(xBinarySemaphore);
		vTaskDelay(100 / portTICK_RATE_MS); // LED blinking frequency
	}
}

int main(void)
{
	gpio_init();
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
	xBinarySemaphore = xSemaphoreCreateBinary(); // create binary sempahore
	if (xBinarySemaphore != NULL)
	{
		xTaskCreate(vTaskLow, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL);
		xTaskCreate(vTaskHigh, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
		vTaskStartScheduler();
	}
while(1); // should not occur
}
