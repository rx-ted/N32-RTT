/*
 * @Author: rx-ted
 * @Date: 2023-01-20 19:52:12
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-02-05 11:34:02
 */

#include "ssd1306.h"
#include <drv_gpio.h>
#include <drv_hwtimer.h>
#include <drv_usart.h>
#include <hwtimer.h>
#include <rtc.h>
#include <rtthread.h>
#include <serial.h>
#include <stdio.h>

#define RED_LED   GET_PIN(A, 8) // red led
#define GREEN_LED GET_PIN(B, 5) // red led

ALIGN(RT_ALIGN_SIZE)

void ssd1306_TestBorder()
{
    ssd1306_Fill(Black);

    u32 start = rt_tick_get();
    u32 end   = start;
    uint8_t x = 0;
    uint8_t y = 0;
    do {
        ssd1306_DrawPixel(x, y, Black);

        if ((y == 0) && (x < 127))
            x++;
        else if ((x == 127) && (y < 31))
            y++;
        else if ((y == 31) && (x > 0))
            x--;
        else
            y--;

        ssd1306_DrawPixel(x, y, White);
        ssd1306_UpdateScreen();

        rt_thread_mdelay(5);
        end = rt_tick_get();
    } while ((end - start) < 2000);

    rt_thread_mdelay(1000);
}

void ssd1306_TestFonts()
{
    ssd1306_Fill(Black);
    ssd1306_SetCursor(2, 0);
    ssd1306_WriteString("Font 16x26", Font_16x26, White);
    ssd1306_UpdateScreen();
    rt_thread_mdelay(1000);
    ssd1306_Fill(Black);
    ssd1306_SetCursor(2, 0);
    ssd1306_WriteString("Font 11x18", Font_11x18, White);
    ssd1306_UpdateScreen();
    rt_thread_mdelay(1000);
    ssd1306_Fill(Black);
    ssd1306_SetCursor(2, 0);
    ssd1306_WriteString("Font 7x10", Font_7x10, White);
    ssd1306_SetCursor(2, 10);
    ssd1306_WriteString("Font 6x8", Font_6x8, White);
    ssd1306_UpdateScreen();
}

void ssd1306_TestFPS()
{
    ssd1306_Fill(White);

    ssd1306_SetCursor(2, 0);
    ssd1306_WriteString("Test-", Font_7x10, Black);
    ssd1306_UpdateScreen();
    // ssd1306_Fill(White);
    // ssd1306_UpdateScreen();
    u32 start      = rt_tick_get();
    u32 end        = start;
    int fps        = 0;
    char message[] = "ABCDEFGHIJK";
    char buff[20];
    do {
        snprintf(buff, sizeof(buff), "FPS:%.2f", fps / ((end - start) / 1000.0));
        ssd1306_SetCursor(46, 15);
        ssd1306_WriteString(message, Font_7x10, Black);
        ssd1306_SetCursor(40, 0);
        ssd1306_WriteString(buff, Font_7x10, Black);
        ssd1306_UpdateScreen();

        char ch = message[0];
        memmove(message, message + 1, sizeof(message) - 2);
        message[sizeof(message) - 2] = ch;

        fps++;
        end = rt_tick_get();
    } while ((end - start) < 1000);

    rt_thread_mdelay(1000);
}

void ssd1306_TestLine()
{
    ssd1306_Line(1, 1, SSD1306_WIDTH - 1, SSD1306_HEIGHT - 1, White);
    ssd1306_Line(SSD1306_WIDTH - 1, 1, 1, SSD1306_HEIGHT - 1, White);
    ssd1306_UpdateScreen();
    return;
}

void ssd1306_TestRectangle()
{
    u32 delta;

    for (delta = 0; delta < 5; delta++)
    {
        ssd1306_DrawRectangle(1 + (5 * delta), 1 + (5 * delta), SSD1306_WIDTH - 1 - (5 * delta), SSD1306_HEIGHT - 1 - (5 * delta), White);
    }
    ssd1306_UpdateScreen();
    return;
}

void ssd1306_TestCircle()
{
    u32 delta;

    for (delta = 0; delta < 5; delta++)
    {
        ssd1306_DrawCircle(20 * delta + 30, 30, 10, White);
    }
    ssd1306_UpdateScreen();
    return;
}

void ssd1306_TestArc()
{
    ssd1306_DrawArc(30, 30, 30, 20, 270, White);
    ssd1306_UpdateScreen();
    return;
}

void ssd1306_TestPolyline()
{
    SSD1306_VERTEX loc_vertex[] =
        {
            {35, 40},
            {40, 20},
            {45, 28},
            {50, 10},
            {45, 16},
            {50, 10},
            {53, 16}};

    ssd1306_Polyline(loc_vertex, sizeof(loc_vertex) / sizeof(loc_vertex[0]), White);
    ssd1306_UpdateScreen();
    return;
}

void ssd1306_TestAll()
{

    ssd1306_TestFPS();
    rt_thread_mdelay(3000);

    ssd1306_TestBorder();

    ssd1306_TestFonts();
    rt_thread_mdelay(3000);

    ssd1306_Fill(Black);
    ssd1306_TestRectangle();
    ssd1306_TestLine();
    rt_thread_mdelay(3000);

    ssd1306_Fill(Black);
    ssd1306_TestPolyline();
    rt_thread_mdelay(3000);

    ssd1306_Fill(Black);
    ssd1306_TestArc();
    rt_thread_mdelay(3000);

    ssd1306_Fill(Black);
    ssd1306_TestCircle();
    rt_thread_mdelay(3000);
}
int main(void)
{
    ssd1306_Init();
    while (1)
    {
        ssd1306_TestAll();
    }
    return 0;
}

#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(ssd1306_TestAll, test ssd1306 oled driver);
#endif
// MSH_CMD_EXPORT(IR, "ir example");
