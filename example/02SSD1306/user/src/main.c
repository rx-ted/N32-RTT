/*
 * @Author: rx-ted
 * @Date: 2023-01-20 19:52:12
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-01-30 23:56:16
 */

#include <drv_gpio.h>
#include <drv_hwtimer.h>
#include <drv_usart.h>
#include <hwtimer.h>
#include <rtthread.h>
#include <serial.h>
#include <u8g2_port.h>
#include "u8g2.h"
#define RED_LED   GET_PIN(A, 8) // red led
#define GREEN_LED GET_PIN(B, 5) // red led

ALIGN(RT_ALIGN_SIZE)

int IR()
{
    return 0;
}

static void ssd1306_12864_hw_i2c_example(int argc, char *argv[])
{
    u8g2_t u8g2;

    // Initialization
    u8g2_Setup_ssd1306_i2c_128x32_univision_1(&u8g2, U8G2_R0, u8x8_byte_rt_hw_i2c, u8x8_rt_gpio_and_delay);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    /* full buffer example, setup procedure ends in _f */
    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);
    u8g2_DrawStr(&u8g2, 1, 18, "U8g2 on RT-Thread");
    u8g2_SendBuffer(&u8g2);

    // Draw Graphics
    u8g2_SetFont(&u8g2, u8g2_font_unifont_t_symbols);
    u8g2_DrawGlyph(&u8g2, 112, 56, 0x2603);
    u8g2_SendBuffer(&u8g2);
}
MSH_CMD_EXPORT(ssd1306_12864_hw_i2c_example, i2c ssd1306 sample);

int main(void)
{

    return 0;
}

// MSH_CMD_EXPORT(IR, "ir example");
