/*
 * @Author: rx-ted
 * @Date: 2023-01-07 19:48:49
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-01-10 22:59:40
 */
#ifndef RT_CONFIG_H__
#define RT_CONFIG_H__

/* Automatically generated file; DO NOT EDIT. */
/* RT-Thread Configuration */

/* RT-Thread Kernel */

#define RT_NAME_MAX 8
#define RT_USING_ARCH_DATA_TYPE
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 100
#define RT_USING_OVERFLOW_CHECK
#define RT_USING_HOOK
#define RT_USING_IDLE_HOOK
#define RT_IDLE_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 256
#define RT_USING_TIMER_SOFT
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 512
#define RT_DEBUG

/* Inter-Thread communication */

#define RT_USING_SEMAPHORE
#define RT_USING_MUTEX
#define RT_USING_EVENT
#define RT_USING_MAILBOX
#define RT_USING_MESSAGEQUEUE

/* Memory Management */

#define RT_USING_MEMPOOL
#define RT_USING_SMALL_MEM
#define RT_USING_HEAP
// #define RT_USING_CONSOLE

/* Kernel Device Object */

#define RT_USING_DEVICE


#define RT_USING_COMPONENTS_INIT
#define RT_USING_USER_MAIN
#define RT_MAIN_THREAD_STACK_SIZE 2048
#define RT_MAIN_THREAD_PRIORITY 10


#define RT_CONSOLE_DEVICE_NAME      "usart1"
#define RT_CONSOLEBUF_SIZE          128
// #define RT_USING_SERIAL
// #define RT_USING_USART1
#define RT_USING_PIN

#define RCC_GPIOA_CLK_ENABLE
#define RCC_GPIOB_CLK_ENABLE
#define RCC_GPIOC_CLK_ENABLE



#endif
