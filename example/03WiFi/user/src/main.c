/*
 * @Author: rx-ted
 * @Date: 2023-01-20 19:52:12
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-03-06 10:08:49
 */

#include <drv_gpio.h>
#include <drv_hwtimer.h>
#include <drv_usart.h>
#include <hwtimer.h>
#include <rtc.h>
#include <rtthread.h>
#include <serial.h>
#include <stdio.h>
#define RED_LED GET_PIN(A, 8)   // red led
#define GREEN_LED GET_PIN(B, 5) // GREEN led
#define SAMPLE_UART_NAME "usart1"
ALIGN(RT_ALIGN_SIZE)

struct rx_msg
{
    rt_device_t dev;
    rt_size_t size;
};

static struct rt_messagequeue rx_mq;
static rt_device_t serial;

static rt_err_t uart_input(rt_device_t dev, rt_size_t size)
{
    struct rx_msg msg;
    rt_err_t result;
    msg.dev = dev;
    msg.size = size;
    result = rt_mq_send(&rx_mq, &msg, sizeof(msg));
    if (result == -RT_EFULL)
    {
        rt_kprintf("message queue full!\n");
    }
    return result;
}

static void serial_thread_entry(void *parameter)
{
    struct rx_msg msg;
    rt_err_t result;
    rt_uint32_t rx_lenght;
    static char rx_buffer[RT_CONSOLEBUF_SIZE + 1];
    while (1)
    {
        rt_memset(&msg, 0, sizeof(msg));
        result = rt_mq_recv(&rx_mq, &msg, sizeof(msg), RT_WAITING_FOREVER);
        if (result == RT_EOK)
        {
            rx_lenght = rt_device_read(msg.dev, 0, rx_buffer, msg.size);
            rx_buffer[rx_lenght] = '\0';
            rt_device_write(serial, 0, rx_buffer, rx_lenght);
            rt_kprintf("%s\n", rx_buffer);
        }
    }
}

static int uart_dma_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    char uart_name[RT_NAME_MAX];
    static char msg_pool[256];
    char str[] = "hello rt_thread!\r\n";
    if (argc == 2)
    {
        rt_strncpy(uart_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(uart_name, SAMPLE_UART_NAME, RT_NAME_MAX);
    }
    serial = rt_device_find(uart_name);
    if (!serial)
    {
        rt_kprintf("find %s failed!\n", uart_name);
        return RT_ERROR;
    }
    rt_mq_init(&rx_mq, "rx_mq", msg_pool, sizeof(struct rx_msg), sizeof(msg_pool), RT_IPC_FLAG_FIFO);
    rt_device_open(serial, 0x2000 | 0x4000);
    rt_device_set_rx_indicate(serial, uart_input);
    rt_device_write(serial, 0, str, sizeof(str) - 1);
    rt_thread_t thread = rt_thread_create("serial", serial_thread_entry, RT_NULL, 1024, 25, 10);
    if (thread!=RT_NULL)
    {
        rt_thread_startup(thread);
    }else{
        ret = RT_ERROR;
    }
    return ret;
}

int main(void)
{

    rt_pin_mode(RED_LED, PIN_MODE_OUTPUT);
    rt_pin_mode(GREEN_LED, PIN_MODE_OUTPUT);

    return 0;
}

MSH_CMD_EXPORT(uart_dma_sample, uart device dma sample);