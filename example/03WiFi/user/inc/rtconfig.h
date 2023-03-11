#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

#define RT_USING_TINY_SIZE

/* RT-Thread Kernel */

#define RT_NAME_MAX   8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND     100
#define RT_USING_OVERFLOW_CHECK
#define IDLE_THREAD_STACK_SIZE 256
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO       4
#define RT_TIMER_THREAD_STACK_SIZE 512
#define RT_DEBUG
#define RT_DEBUG_INIT_CONFIG
#define RT_DEBUG_INIT 1

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX

/* Memory Management */

#define RT_USING_SMALL_MEM
#define RT_USING_HEAP

/* Kernel Device Object */

#define RT_USING_DEVICE
#define RT_USING_CONSOLE
#define RT_CONSOLEBUF_SIZE     2048
#define RT_CONSOLE_DEVICE_NAME "usart1"
#define RT_VER_NUM             0x30104
#define ARM_CORTEX_M4

/* RT-Thread Components */

#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN

/* C++ features */

/* Command shell */

#define RT_USING_FINSH
#define FINSH_THREAD_NAME "tshell"
#define FINSH_USING_HISTORY
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB
#define FINSH_USING_DESCRIPTION
#define FINSH_THREAD_PRIORITY   20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_CMD_SIZE          80
#define FINSH_USING_MSH
#define FINSH_USING_MSH_DEFAULT
#define FINSH_USING_MSH_ONLY
#define FINSH_ARG_MAX 10

/* Device Drivers */

#define RT_USING_DEVICE_IPC
#define RT_USING_SERIAL
#define RT_USING_USART1
#define RT_USING_HWTIMER
#define RT_USING_I2C
// #define RT_I2C_DEBUG
// #define RT_USING_I2C_BITOPS
// #define RT_I2C_BITOPS_DEBUG
#define RT_USING_PIN

/* Using USB */

/* POSIX layer and C standard library */

#define RT_USING_LIBC

/* RT-Thread online packages */

/* IoT - internet of things */

/* Wi-Fi */

/* Marvell WiFi */

/* Wiced WiFi */

/* IoT Cloud */

/* security packages */

/* language packages */

/* multimedia packages */

/* tools packages */

/* system packages */

/* peripheral libraries and drivers */

// #define RT_USING_I2C1
#define RT_USING_I2C2
#define RT_USING_RTC
#define RT_USING_SOFT_RTC
#define RT_USING_MESSAGEQUEUE

#endif
