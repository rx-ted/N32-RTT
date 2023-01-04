/*
 * @Author: rx-ted
 * @Date: 2022-12-19 11:10:54
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-01-04 22:45:40
 */

#include "board.h"
#include "drv_gpio.h"
#include "drv_usart.h"
#include "pin.h"
#include "serial.h"
#include "ssd1306.h"
#include <rtconfig.h>
#include <rtthread.h>

ALIGN(RT_ALIGN_SIZE)

#define LED1_PIN GET_PIN(A, 8)
#define KEY1_PIN GET_PIN(A, 4)
#define LED3_PIN GET_PIN(B, 5)
#define KEY3_PIN GET_PIN(A, 6)

int main(void)
{
    ssd1306_init();//test if success.
}
