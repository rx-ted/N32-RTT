/*
 * @Author: rx-ted
 * @Date: 2023-02-04 00:02:03
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-02-04 01:03:16
 */
/**
 * Private configuration file for the SSD1306 library.
 * This example is configured for STM32F0, I2C and including all fonts.
 */

#ifndef __SSD1306_CONF_H__
#define __SSD1306_CONF_H__

#define SSD1306_USE_I2C
#include "n32g4fr.h"
#include "rtconfig.h"
#include "ssd1306_fonts.h"
#include <math.h>
#include <rtdevice.h>
#include <rtthread.h>
#include <stdlib.h>
#include <string.h>
#include"i2c.h"

#define PKG_USING_SSD1306_I2C_BUS_NAME "i2c2"

// Mirror the screen if needed
// #define SSD1306_MIRROR_VERT
// #define SSD1306_MIRROR_HORIZ

// Set inverse color if needed
// # define SSD1306_INVERSE_COLOR

// Include only needed fonts
#define SSD1306_INCLUDE_FONT_6x8
#define SSD1306_INCLUDE_FONT_7x10
#define SSD1306_INCLUDE_FONT_11x18
#define SSD1306_INCLUDE_FONT_16x26

#endif /* __SSD1306_CONF_H__ */