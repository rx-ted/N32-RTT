# ssd1306 example

## rtconfig.h

copy Previous file to this project, called rtconfig.h.

add other functions, such as  

```C
#define RT_USING_I2C
#define RT_USING_I2C2 //can choice RT_USING_I2C1 or RT_USING_I2C3
#define RT_USING_RTC  // update date, but this isn't what is needed.
#define RT_USING_SOFT_RTC  // can't need this
//last two lines can be commented.
```

## SSD1306 IIC读写时序

[IIC读写时序](https://github.com/rx-ted/N32-RTT/blob/main/example/02SSD1306/doc/SSD1306%20IIC%E8%AF%BB%E5%86%99%E6%97%B6%E5%BA%8F.png)

## SSD1306 INIT初始化流程

[init初始化流程](https://github.com/rx-ted/N32-RTT/blob/main/example/02SSD1306/doc/init%E5%88%9D%E5%A7%8B%E5%8C%96%E6%B5%81%E7%A8%8B.png)

## usage

ssd1306 i2c 128X32  
Others developed the library, including I2C and SPI, But I simply delete the SPI functions, currently normal.  
I choice RT_USING_I2C, speed is set to 1000000(1000K).

```c
#define I2C2_SPEED  1000000 //It was 100K,now it's 1000K
```

| library name |                          url                           |
| :----------: | :----------------------------------------------------: |
| RTT_SSD1306  | [传送门](https://github.com/luhuadong/rtt-ssd1306.git) |

[rtt-ssd1306怎么使用](../../packages/rtt-ssd1306/README.md)


## RUN TEST

[运行测试视频](https://github.com/rx-ted/N32-RTT/blob/main/example/02SSD1306/doc/test.mp4)
