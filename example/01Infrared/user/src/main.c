/*
 * @Author: rx-ted
 * @Date: 2023-01-20 19:52:12
 * @LastEditors: rx-ted
 * @LastEditTime: 2023-01-20 19:57:05
 */


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


ALIGN(RT_ALIGN_SIZE)



int main(void)
{

    return 0;
}


