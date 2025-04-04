/*********************************************************************************************************************
* CYT2BL3 Opensourec Library 即（ CYT2BL3 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 CYT2BL3 开源库的一部分
*
* CYT2BL3 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main_cm4
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 9.40.1
* 适用平台          CYT2BL3
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2024-11-19       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// *************************** 例程硬件连接说明 ***************************
// 使用逐飞科技 CMSIS-DAP 调试下载器连接
//      直接将下载器正确连接在核心板的调试下载接口即可
// 
// 使用 USB-TTL 模块连接
//      模块管脚            单片机管脚
//      USB-TTL-RX          查看 zf_common_debug.h 文件中 DEBUG_UART_TX_PIN 宏定义的引脚 默认 B12
//      USB-TTL-TX          查看 zf_common_debug.h 文件中 DEBUG_UART_RX_PIN 宏定义的引脚 默认 B13
//      USB-TTL-GND         核心板电源地 GND
//      USB-TTL-3V3         核心板 3V3 电源


// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，单独使用核心板与调试下载器或者 USB-TTL 模块，在断电情况下完成连接
// 
// 2.将调试下载器或者 USB-TTL 模块连接电脑，完成上电
// 
// 3.电脑上使用串口助手打开对应的串口，串口波特率为 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义 默认 115200，核心板按下复位按键
// 
// 4.可以在串口助手上看到如下串口信息：
//      Timer count is 540 us.
//      Timer count is 80003 us.
//      Timer count is 1000 ms.
// 
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查

// **************************** 代码区域 ****************************

int main(void)
{
    clock_init(SYSTEM_CLOCK_160M);      // 时钟配置及系统初始化<务必保留>
    
    debug_init();                       // 调试串口初始化
    // 此处编写用户代码 例如外设初始化代码等
    
    timer_init(TC_TIME2_CH0, TIMER_US);                                         // 定时器使用 TC_TIME2_CH0 使用微秒级计数
    timer_start(TC_TIME2_CH0);                                                  // 启动定时
    system_delay_us(540);                                                       // 
    timer_stop(TC_TIME2_CH0);                                                   // 停止定时器
    printf("Timer count is %d us.\r\n", timer_get(TC_TIME2_CH0));               // 获取定时器的值并输出
    timer_clear(TC_TIME2_CH0);                                                  // 计时值使用完毕后记得清除，避免导致下次计时不从0开始
    
    
    timer_init(TC_TIME2_CH0, TIMER_US);                                         // 定时器使用 TC_TIME2_CH0 使用微秒级计数
    timer_start(TC_TIME2_CH0);                                                  // 启动定时
    system_delay_ms(80);                                                        // 
    timer_stop(TC_TIME2_CH0);                                                   // 停止定时器
    printf("Timer count is %d us.\r\n", timer_get(TC_TIME2_CH0));               // 获取定时器的值并输出
    timer_clear(TC_TIME2_CH0);                                                  // 计时值使用完毕后记得清除，避免导致下次计时不从0开始
    
    
    timer_init(TC_TIME2_CH0, TIMER_MS);                                         // 定时器使用 TC_TIME2_CH0 使用毫秒级计数
    timer_start(TC_TIME2_CH0);                                                  // 启动定时
    system_delay_ms(1000);                                                      //
    timer_stop(TC_TIME2_CH0);                                                   // 停止定时器
    printf("Timer count is %d ms.\r\n", timer_get(TC_TIME2_CH0));               // 获取定时器的值并输出
    timer_clear(TC_TIME2_CH0);                                                  // 计时值使用完毕后记得清除，避免导致下次计时不从0开始
    
    
    // 此处编写用户代码 例如外设初始化代码等
    for(;;)
    {
        // 此处编写需要循环执行的代码
        

      
      
        // 此处编写需要循环执行的代码
    }
}

// **************************** 代码区域 ****************************
