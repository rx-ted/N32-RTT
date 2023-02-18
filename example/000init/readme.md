<!--
 * @Author: rx-ted
 * @Date: 2022-12-15 20:28:07
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-02-18 21:29:05
-->

# 基于 Windows 的 ARM GCC 开发环境

- **目录**
- [基于 Windows 的 ARM GCC 开发环境](#基于-windows-的-arm-gcc-开发环境)
  - [概述](#概述)
  - [开发工具](#开发工具)
    - [软件](#软件)
    - [硬件](#硬件)
  - [开发环境搭建](#开发环境搭建)
    - [安装 VScode 软件](#安装-vscode-软件)
    - [安装 gcc 编译工具链](#安装-gcc-编译工具链)
    - [安装 make for Windows](#安装-make-for-windows)
    - [安装 JLink 工具](#安装-jlink-工具)
  - [目录详细说明](#目录详细说明)
  - [编译和下载](#编译和下载)

## 概述

本文以 N32G4FR 系列 MCU 为例，介绍了在 Windows 环境下基于 vscode 编辑器、GCC 编
译工具链和 GDB 调试工具进行搭建开发环境、编译、固件下载和代码调试的方法。

> 声明：不包含rt-thread

## 开发工具

### 软件

1) 编辑器 Visual Studio Code
2) 编译工具链 arm-none-eabi-gcc
3) Make for Windows
4) 下载工具
5) 调试工具 **（略）**

### 硬件

1) 开发板 N32G4FR
2) 一条数据线

## 开发环境搭建

### 安装 VScode 软件

下载软件：[VScode](https://code.visualstudio.com)

### 安装 gcc 编译工具链

下载地址：[gcc](https://launchpad.net/gcc-arm-embedded)

### 安装 make for Windows

下载地址：[make](http://www.equation.com/servlet/equation.cmd?fa=make)

### 安装 JLink 工具

略

## 目录详细说明

├─build  生成文件  
├─doc  文档  
├─firmware  固件  
│  ├─CMSIS  系统如下  
│  │  ├─core  核心文件  
│  │  └─device  设备文件  
│  │      └─startup  启动文件  
│  ├─n32g4fr_algo_lib  算法库  
│  ├─n32g4fr_std_periph_driver  静态  
│  └─n32g4fr_usbfs_driver  USB  
├─include  头文件  
├─note  随笔  
└─src  源代码  

## 编译和下载

在第一个目录下运行

```cmd
make
```

可以得到运行结果

```cmd
PS D:\N32G4FR> make 
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=soft   -Wall -Os -ffunction-sections -fdata-sections -g -gdwarf-2 -MMD -MP -MF"build/delay.d" -DN32G4fr -DUSE_STDPERIPH_DRIVER -Ifirmware/CMSIS/core/ -Ifirmware/CMSIS/device/ -Ifirmware/n32g4fr_std_periph_driver/inc/ -Ifirmware/n32g4fr_usbfs_driver/inc/ -Iinclude/ -Ifirmware/n32g4fr_algo_lib/inc/  -c -Wa,-a,-ad,-alms=build/delay.lst src/delay.c -o build/delay.o
...
arm-none-eabi-size build/output.elf
   text    data     bss     dec     hex filename
   1516    1088    4904    7508    1d54 build/output.elf
arm-none-eabi-objcopy -O ihex -S build/output.elf build/output.hex
arm-none-eabi-objcopy -O binary -S build/output.elf build/output.bin
```
