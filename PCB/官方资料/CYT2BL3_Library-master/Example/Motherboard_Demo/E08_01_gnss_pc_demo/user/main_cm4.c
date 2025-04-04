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
// 使用 USB-TTL 模块连接
//      模块管脚            单片机管脚
//      USB-TTL-RX          查看 zf_common_debug.h 文件中 DEBUG_UART_TX_PIN 宏定义的引脚 默认 P14_0
//      USB-TTL-TX          查看 zf_common_debug.h 文件中 DEBUG_UART_RX_PIN 宏定义的引脚 默认 P14_1
//      USB-TTL-GND         核心板电源地 GND
//      USB-TTL-3V3         核心板 3V3 电源
// 接入gnss TAU1201连接
//      模块管脚            单片机管脚
//      RX                  查看 zf_device_gnss.h 文件中 gnss_RX 宏定义的引脚 默认 P15_7
//      TX                  查看 zf_device_gnss.h 文件中 gnss_TX 宏定义的引脚 默认 P15_6
//      GND                 电源地
//      VCC                 5V电源



// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，单独使用核心板与调试下载器或者 USB-TTL 模块，并连接好gnss，在断电情况下完成连接
// 2.将调试下载器或者 USB-TTL 模块连接电脑，完成上电
// 3.电脑上使用 逐飞助手 打开对应的串口，串口波特率为 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义 默认 115200，核心板按下复位按键
// 4.可以在 逐飞助手 上看到如下串口信息：
//      now time:......
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查


// **************************** 代码区域 ****************************

int main(void)
{
    clock_init(SYSTEM_CLOCK_160M); 	// 时钟配置及系统初始化<务必保留>
    debug_info_init();                  // 调试串口信息初始化
    
    // 此处编写用户代码 例如外设初始化代码等

    gnss_init(TAU1201);
    printf("dis:%f\r\n", get_two_points_distance(45.714935, 126.626564, 45.714855, 126.626960));        // 计算两点距离示例
    printf("dir:%f\r\n", get_two_points_azimuth(45.714935, 126.626564, 45.714855, 126.626960));         // 计算两点夹角示例
    
    // 此处编写用户代码 例如外设初始化代码等
    while(true)
    {
        // 此处编写需要循环执行的代码

        //gnss数据接收与解析都是通过串口中断调用gnss_uart_callback函数进行实现的
        //数据解析完毕之后gnss_flag标志位会置1
        if(gnss_flag)
        {
            gnss_flag = 0;

            gnss_data_parse();           //开始解析数据

            printf("now time:\r\n");                                            // 输出年月日时分秒
            printf("year-%d, month-%d, day-%d\r\n", gnss.time.year, gnss.time.month, gnss.time.day);           // 输出年月日时分秒
            printf("hour-%d, minute-%d, second-%d\r\n", gnss.time.hour, gnss.time.minute, gnss.time.second);   // 输出年月日时分秒
            printf("gnss_state       = %d\r\n", gnss.state);              //输出当前定位有效模式 1：定位有效  0：定位无效
            printf("latitude        = %f\r\n", gnss.latitude);           //输出纬度信息
            printf("longitude       = %f\r\n", gnss.longitude);          //输出经度信息
            printf("speed           = %f\r\n", (double)gnss.speed);              //输出速度信息
            printf("direction       = %f\r\n", (double)gnss.direction);          //输出方向信息
            printf("satellite_used  = %d\r\n", gnss.satellite_used);     //输出当前用于定位的卫星数量
            printf("height          = %f\r\n", (double)gnss.height);             //输出当前gnss天线所处高度
        }
        system_delay_ms(1000);//这里延时主要目的是为了降低输出速度，便于在 逐飞助手 中观察数据，实际使用的时候不需要这样去延时

        // 此处编写需要循环执行的代码
    }
}

// **************************** 代码区域 ****************************
// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1：串口没有数据
//      查看 逐飞助手 打开的是否是正确的串口，检查打开的 COM 口是否对应的是调试下载器或者 USB-TTL 模块的 COM 口
//      如果是使用逐飞科技 CMSIS-DAP 调试下载器连接，那么检查下载器线是否松动，检查核心板串口跳线是否已经焊接，串口跳线查看核心板原理图即可找到
//      如果是使用 USB-TTL 模块连接，那么检查连线是否正常是否松动，模块 TX 是否连接的核心板的 RX，模块 RX 是否连接的核心板的 TX
//      检查一下gnss模块接线是否正常
// 问题2：串口数据乱码
//      查看 逐飞助手 设置的波特率是否与程序设置一致，程序中 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义为 debug uart 使用的串口波特率
// 问题3：数据显示除了时间以外全部是0
//      需要把天线放到室外 需要接收到卫星信号才能有数据