

#include "drv_gpio.h"
#include "drv_soft_i2c.h"
#include "drv_usart.h"
#include "pin.h"
#include "serial.h"
#include "ssd1306.h"
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

#define I2C_SDA GET_PIN(B, 9)
#define I2C_SCL GET_PIN(B, 8)
static rt_soft_i2c_bus_device_t ssd1306_obj = RT_NULL;
#define OLED_COLUMN_NUMBER 128
#define OLED_LINE_NUMBER 32
#define OLED_PAGE_NUMBER OLED_LINE_NUMBER/8


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

int soft_i2c_hw_init(void)
{
    ssd1306_obj = soft_i2c_user_init(PKG_SOFTI2C_BUS_NAME, I2C_SCL, I2C_SDA, PKG_SOFTI2C_BAUDRATE);
    if (ssd1306_obj == RT_NULL)
    {
        rt_kprintf("fail to init\n");
        return -RT_ERROR;
    }
    rt_kprintf("Success to init\n");

    return RT_EOK;
}

// *****3----3SCK,   4----4SDA,
/**************************IIC模块发送函数************************************************

 *************************************************************************/

const unsigned char OLED_init_cmd[25] =
    {
        0xAE, // 关闭显示
        0xD5, // 设置时钟分频因子,震荡频率
        0x80, //[3:0],分频因子;[7:4],震荡频率
        0xA8, // 设置驱动路数
        0X1F, // 默认(1/32)
        0xD3, // 设置显示偏移
        0X00, // 默认为0
        0x40, // 设置显示开始行 [5:0],行数.
        0x8D, // 电荷泵设置
        0x14, // bit2，开启/关闭
        0x20, // 设置内存地址模式
        0x02, //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
        0xA1, // 段重定义设置,bit0:0,0->0;1,0->127;
        0xC8, // 设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
        0xDA, // 设置COM硬件引脚配置
        0x02, //[5:4]配置
        0x81, // 对比度设置
        0xEF, // 1~255;默认0X7F (亮度设置,越大越亮)
        0xD9, // 设置预充电周期
        0xf1, //[3:0],PHASE 1;[7:4],PHASE 2;
        0xDB, // 设置VCOMH 电压倍率
        0x30, //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
        0xA4, // 全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
        0xA6, // 设置显示方式;bit0:1,反相显示;0,正常显示
        0xAF, // 开启显示
};

// 写入  最后将SDA拉高，以等待从设备产生应答
void IIC_write(unsigned char date)
{
    unsigned char i, temp;
    temp = date;

    for (i = 0; i < 8; i++)
    {
        rt_pin_write(ssd1306_obj->scl, PIN_LOW);

        if ((temp & 0x80) == 0)
            rt_pin_write(ssd1306_obj->sda, PIN_LOW);

        else
            rt_pin_write(ssd1306_obj->sda, PIN_HIGH);

        temp = temp << 1;
        // 最少250ns延时
        rt_pin_write(ssd1306_obj->scl, PIN_HIGH);
    }

    rt_pin_write(ssd1306_obj->scl, PIN_LOW);
    rt_pin_write(ssd1306_obj->sda, PIN_HIGH);
    rt_pin_write(ssd1306_obj->scl, PIN_HIGH);
    // 不进行应答检测
    rt_pin_write(ssd1306_obj->scl, PIN_LOW);
}
// 启动信号
// SCL在高电平期间，SDA由高电平向低电平的变化定义为启动信号
void IIC_start()
{
    rt_pin_write(ssd1306_obj->scl, PIN_HIGH);

    rt_pin_write(ssd1306_obj->sda, PIN_HIGH);
    // 所有操作结束释放SCL
    rt_pin_write(ssd1306_obj->sda, PIN_LOW);
    rt_pin_write(ssd1306_obj->scl, PIN_LOW);

    IIC_write(0x78);
}

// 停止信号
// SCL在高电平期间，SDA由低电平向高电平的变化定义为停止信号
void IIC_stop()
{

    rt_pin_write(ssd1306_obj->sda, PIN_LOW);
    rt_pin_write(ssd1306_obj->scl, PIN_HIGH);
    rt_pin_write(ssd1306_obj->sda, PIN_HIGH);
}

void OLED_send_cmd(unsigned char o_command)
{

    IIC_start();
    IIC_write(0x00);
    IIC_write(o_command);
    IIC_stop();
}
void OLED_send_data(unsigned char o_data)
{
    IIC_start();
    IIC_write(0x40);
    IIC_write(o_data);
    IIC_stop();
}
void Column_set(unsigned char column)
{
    OLED_send_cmd(0x10 | (column >> 4));   // 设置列地址高位
    OLED_send_cmd(0x00 | (column & 0x0f)); // 设置列地址低位
}
void Page_set(unsigned char page)
{
    OLED_send_cmd(0xb0 + page);
}

void OLED_init(void)
{
    unsigned char i;
    for (i = 0; i < 25; i++)
    {
        OLED_send_cmd(OLED_init_cmd[i]);
    }
}

void IO_init(void)
{
    rt_pin_mode(ssd1306_obj->scl, PIN_MODE_OUTPUT_OD);
    rt_pin_mode(ssd1306_obj->sda, PIN_MODE_OUTPUT_OD);
    rt_pin_write(ssd1306_obj->scl, PIN_HIGH);
    rt_pin_write(ssd1306_obj->sda, PIN_HIGH);
}

void OLED_full(void)
  {
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
        Page_set(page);
        Column_set(0);    
  for(column=0;column<OLED_COLUMN_NUMBER;column++)  //column loop
          {
            OLED_send_data(0x00);
          }
      }
  }


/**
 * @brief  Main program
 */
int main(void)
{

    soft_i2c_hw_init();
    IO_init();
    OLED_full();
}

MSH_CMD_EXPORT(led1, "red led blink")
MSH_CMD_EXPORT(led2, "blue led blink")

/*@}*/
//
