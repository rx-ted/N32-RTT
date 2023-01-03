/*
 * @Author: rx-ted
 * @Date: 2022-12-19 11:10:54
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-01-03 21:35:03
 */

#include <rtthread.h>

#include "board.h"
#include "drv_gpio.h"
#include "drv_usart.h"
#include "pin.h"
#include "serial.h"

#include "easyblink.h"

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led0_stack[512], led1_stack[512];

static struct rt_thread led0_thread;
static struct rt_thread led1_thread;

#define LED1_PIN GET_PIN(A, 8)
#define KEY1_PIN GET_PIN(A, 4)
#define LED3_PIN GET_PIN(B, 5)
#define KEY3_PIN GET_PIN(A, 6)

int main(void)
{
    ebled_t led1 = RT_NULL;
    led1 = easyblink_init_led(LED1_PIN, PIN_LOW);

    /* led1 闪20次，周期1000ms，亮500ms */
    easyblink(led1, 20, 500, 1000);

    eb_led_off(led1);

    rt_thread_mdelay(1000);
    eb_led_on(led1);
    rt_thread_mdelay(1000);
    eb_led_toggle(led1);

}
