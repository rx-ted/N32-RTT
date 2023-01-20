

#include "drv_gpio.h"
#include "drv_usart.h"
#include "pin.h"
#include "serial.h"
#include <rtthread.h>

#ifdef RT_USING_DFS
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/calibration.h>
#include <rtgui/driver.h>
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#endif

// #define I2C_SDA GET_PIN(B, 9)
// #define I2C_SCL GET_PIN(B, 8)
// static rt_soft_i2c_bus_device_t ssd1306_obj = RT_NULL;
// #define OLED_COLUMN_NUMBER 128
// #define OLED_LINE_NUMBER 32
// #define OLED_PAGE_NUMBER OLED_LINE_NUMBER/8

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led0_stack[512], led1_stack[512];

static struct rt_thread led0_thread;
static struct rt_thread led1_thread;

#define LED1_PIN GET_PIN(A, 8)
#define LED3_PIN GET_PIN(B, 5)

/**
 * @brief  led0 thread entry
 */
static void led0_thread_entry(void *parameter)
{
    while (1)
    {
        rt_thread_delay(50); // delay 500ms
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_delay(50); // delay 500ms
        rt_pin_write(LED1_PIN, PIN_LOW);
    }
}

/**
 * @brief  led1 thread entry
 */
static void led1_thread_entry(void *parameter)
{
    while (1)
    {
        rt_thread_delay(25); // delay 250ms
        rt_pin_write(LED3_PIN, PIN_HIGH);
        rt_thread_delay(25); // delay 250ms
        rt_pin_write(LED3_PIN, PIN_LOW);
    }
}

#ifdef RT_USING_RTGUI
rt_bool_t cali_setup(void)
{
    rt_kprintf("cali setup entered\n");
    return RT_FALSE;
}

void cali_store(struct calibration_data *data)
{
    rt_kprintf("cali finished (%d, %d), (%d, %d)\n",
               data->min_x,
               data->max_x,
               data->min_y,
               data->max_y);
}
#endif /* RT_USING_RTGUI */

int led1()
{
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    rt_err_t result;
    /* init led0 thread */
    result = rt_thread_init(&led0_thread, "led0", led0_thread_entry, RT_NULL, (rt_uint8_t *)&led0_stack[0], sizeof(led0_stack), 4, 5);
    if (result != RT_EOK)
    {
        rt_kprintf("create task for red led is failed!\n");
        return -1;
    }
    rt_thread_startup(&led0_thread);
    return 0;
}

int led2()
{
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    rt_err_t result;
    /* init led1 thread */
    result = rt_thread_init(&led1_thread, "led1", led1_thread_entry, RT_NULL, (rt_uint8_t *)&led1_stack[0], sizeof(led1_stack), 5, 5);
    if (result != RT_EOK)
    {
        rt_kprintf("create task for green led is failed!\n");
        return -1;
    }
    rt_thread_startup(&led1_thread);
    return 0;
}

/**
 * @brief  Main program
 */
int main(void)
{

    return 0;
}

MSH_CMD_EXPORT(led1, "red led blink")
MSH_CMD_EXPORT(led2, "blue led blink")

/*@}*/
//
