/*
 * @Author: rx-ted
 * @Date: 2023-01-20 19:52:12
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-01-27 21:26:30
 */

#include <drv_gpio.h>
#include <drv_hwtimer.h>
#include <drv_usart.h>
#include <hwtimer.h>
#include <infrared.h>
#include <rtthread.h>
#include <serial.h>

#define RED_LED   GET_PIN(A, 8) // red led
#define GREEN_LED GET_PIN(B, 5) // red led
struct infrared_decoder_data infrared_data;
ALIGN(RT_ALIGN_SIZE)

int IR()
{
    return 0;
}

int main(void)
{
    /* set LED0 pin mode to output */
    uint8_t key = RT_NULL;
    rt_pin_mode(RED_LED, PIN_MODE_OUTPUT);
    rt_pin_mode(GREEN_LED, PIN_MODE_OUTPUT);
    rt_kprintf("IR driver!\n");
    ir_select_decoder("nec");
    while (1)
    {
        // rt_pin_write(RED_LED, PIN_HIGH);
        /* 读取数据 */
        infrared_read("nec", &infrared_data);

        // rt_pin_write(GREEN_LED, PIN_HIGH);
        // rt_thread_mdelay(250);
        rt_kprintf("RECEIVE OK: addr:0x%02X key:0x%02X repeat:%d\n", infrared_data.data.nec.addr,
                   infrared_data.data.nec.key,
                   infrared_data.data.nec.repeat);
        // rt_pin_write(GREEN_LED, PIN_LOW);
        rt_thread_mdelay(1000);
        // key = infrared_data.data.nec.key;

        // rt_pin_write(RED_LED, PIN_LOW);
    }
    return 0;
}

// MSH_CMD_EXPORT(IR, "ir example");
