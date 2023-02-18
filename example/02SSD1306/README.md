
# 【国民技术N32项目移植】ssd1306项目移植

国民技术和RT-Thread合作，于是做了一个基于RT-Thread框架开发一个可视化界面，例如接口有GPIO、UART、I2C等等。

## 1.芯片资源

| 接口  |     描述      |
| :---: | :-----------: |
| GPIO  |  点灯，熄灯   |
| UART  |  串口，finsh  |
|  I2C  | ssd1306可视化 |
|  ...  |      ...      |

### GPIO怎么接

点亮LED灯是GPIO的基础功能之一。如何让LED闪烁。

| 引脚  | 序号  |    描述    |
| :---: | :---: | :--------: |
|  PB5  |  D3   | 点灯，熄灯 |
|  PA8  |  D1   | 点灯，熄灯 |

### UART怎么接

UART是默认选UART1，如何让单片机发送接收消息。

| 引脚  | 序号  |   描述   |
| :---: | :---: | :------: |
|  PA9  |  RXD  | 串口接收 |
| PA10  |  TXD  | 串口发送 |

### I2C怎么接

I2C是默认选I2C1，如何让单片机连接SSD1306屏幕。

| 引脚  | 序号  |    描述     |
| :---: | :---: | :---------: |
|  PB8  | SCLK  |   I2C时钟   |
|  PB9  |  SDA  | I2C读写数据 |

## 2.移植实操和过程总结

- 1、N32G4FR在RT-Thread上正常运行
平台上可以选择VS CODE 或者是Keil5,我选择前者。  
需要的工具：
vscode  
arm-eabi-none-gcc(大多数是C语言)
EIDE
烧录工具：pwlink、swd，等
移植库包（SDK、Core，Example等等）

怎么搭建开发环境，[传送门](https://baidu.com)

总结：在过程中搭建环境或者移植中，遇到一些困难，只要认真解决，在群上多问问，多动脑子，多多动手编程，这样会发现原来是这样的，我怎么没想到~

- 2、N32G4FR在finsh上正常运行

FinSH主要用于调试、查看系统信息，也支持敲代码，不再是只看而无法输入代码。  
用户在控制终端输入命令，控制终端通过通信协议的方式将命令传给N32G4FR FinSH，而FinSH会读取设备输入命令，解析并执行输出回应，将结果显示在控制终端上。
本文以串口UART1作为FinSH的输入输出端口与 PC 进行通信，描述如何在 N32G4FR开发板上实现 FinSH shell 功能。
在 RT-Thread Nano 上添加 FinSH 组件，实现FinSH功能需要开启路径：rt-thread/components/finsh,添加头文件路径和源文件。

- 3、N32G4FR在SSD1306上正常运行

SSD1306 IIC读写时序

[IIC读写时序](https://github.com/rx-ted/N32-RTT/blob/main/example/02SSD1306/doc/SSD1306%20IIC%E8%AF%BB%E5%86%99%E6%97%B6%E5%BA%8F.png)

SSD1306 INIT初始化流程

[init初始化流程](https://github.com/rx-ted/N32-RTT/blob/main/example/02SSD1306/doc/init%E5%88%9D%E5%A7%8B%E5%8C%96%E6%B5%81%E7%A8%8B.png)

基于RT-Thread实现，OLED的I2C驱动都是自己修改，因为使用硬件IIC不能与库兼容起来，如果需要兼容则需要修改源码，目前已实现。其他人开发的库，包括I2C和SPI，但我只是删除了SPI函数，目前正常。
我选择RT_USING_I2C，且设置I2C1，速率就默认好了。

在rtconfig.h上面编辑

copy Previous file to this project, called rtconfig.h.

add other functions, such as  ~~~~

```C
#define RT_USING_I2C
#define RT_USING_I2C2 //can choice RT_USING_I2C1 or RT_USING_I2C3
#define RT_USING_RTC  // update date, but this isn't what is needed.
#define RT_USING_SOFT_RTC  // can't need this
//last two lines can be commented.
```

| library name |                          url                           |
| :----------: | :----------------------------------------------------: |
| RTT_SSD1306  | [传送门](https://github.com/luhuadong/rtt-ssd1306.git) |

[rtt-ssd1306 API使用](../../packages/rtt-ssd1306/README.md)

## 3.参赛作品代码与演示视频

### 代码

我上传代码，在github网址/example/02SSD1306，就是SSD1306开源地址，其他项目，欢迎浏览。  
[传送门](https://github.com/rx-ted/N32-RTT/tree/main/example/02SSD1306)

### RUN TEST

[运行测试视频](https://github.com/rx-ted/N32-RTT/blob/main/example/02SSD1306/doc/test.mp4)
