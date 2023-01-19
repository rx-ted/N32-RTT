/*
 * @Author: rx-ted
 * @Date: 2023-01-15 16:01:24
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-01-16 21:20:45
 */

#ifndef __SSD1306_H__
#define __SSD1306_H__
#include "i2c.h"
#include "rtconfig.h"
#include "rtthread.h"

// Struct to store transformations
typedef struct
{
    uint16_t CurrentX;
    uint16_t CurrentY;
    uint8_t Inverted;
    uint8_t Initialized;
    uint8_t DisplayOn;
} SSD1306_t;
// Enumeration for screen colors
typedef enum
{
    Black = 0x00, // Black color, no pixel
    White = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR;

#define SSD1306_I2C_ADDR    (0x3C << 1)
#define SSD1306_HEIGHT      32
#define SSD1306_WIDTH       128
#define SSD1306_BUFFER_SIZE SSD1306_WIDTH *SSD1306_HEIGHT / 8
#define SSD1306_CTRL_CMD    0x00
#define SSD1306_CTRL_DATA   0x40


static uint8_t SSD1306_Buffer[SSD1306_BUFFER_SIZE];
static struct rt_i2c_bus_device *i2c_bus = RT_NULL; /* I2C总线设备句柄 */
static SSD1306_t SSD1306;

void ssd1306_init();
// Low-level procedures
void ssd1306_Reset(void);
void ssd1306_WriteCommand(uint8_t byte);
void ssd1306_WriteData(uint8_t *buffer, size_t buff_size);
void ssd1306_SetContrast(const uint8_t value);
void ssd1306_SetDisplayOn(const uint8_t on);
void ssd1306_Fill(SSD1306_COLOR color);
void ssd1306_UpdateScreen(void);

#endif // __SSD1306_H__
