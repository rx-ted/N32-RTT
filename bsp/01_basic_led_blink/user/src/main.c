/*
 * @Author: rx-ted
 * @Date: 2023-01-06 22:17:59
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-01-10 22:57:08
 */

#include <rtthread.h>

#include "drv_gpio.h"
// #include "drv_usart.h"
#include "pin.h"
// #include "serial.h"

ALIGN(RT_ALIGN_SIZE)


#define LED1_PIN GET_PIN(A, 8)
#define LED3_PIN GET_PIN(B, 5)



int main(void)
{

	rt_err_t result;

	rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
	rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
	while (1)
	{
		rt_thread_delay(25); // delay 250ms
		rt_pin_write(LED3_PIN, PIN_HIGH);
		rt_thread_delay(25); // delay 250ms
		rt_pin_write(LED3_PIN, PIN_LOW);
		rt_thread_delay(50); // delay 500ms
		rt_pin_write(LED1_PIN, PIN_HIGH);
		rt_thread_delay(50); // delay 500ms
		rt_pin_write(LED1_PIN, PIN_LOW);
	}
}
