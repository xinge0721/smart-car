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


// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，单独使用核心板与调试下载器或者 USB-TTL 模块，在断电情况下完成连接
// 2.将调试下载器或者 USB-TTL 模块连接电脑，完成上电
// 3.电脑上使用串口助手打开对应的串口，串口波特率为 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义 默认 115200，核心板按下复位按键
// 4.可以在串口助手上看到如下串口信息：
//      FLASH_SECTION_INDEX: 127, FLASH_PAGE_INDEX: 3, origin data is :
//      ...
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查
// **************************** 代码区域 ****************************

#define FLASH_SECTION_INDEX       (0)                                 // 存储数据用的扇区
#define FLASH_PAGE_INDEX          (0)                                // 存储数据用的页码 倒数第一个页码

int main(void)
{
    clock_init(SYSTEM_CLOCK_160M);      // 时钟配置及系统初始化<务必保留>
    
    debug_init();                       // 调试串口初始化
    // 此处编写用户代码 例如外设初始化代码等
    
    flash_init();                                                               // 使用flash前先调用flash初始化
    
    flash_erase_page(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);                    // 擦除这一页

    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
    // 请注意 数据缓冲区的每个位置只能存储一种类型的数据

    flash_buffer_clear();                                                       // 清空缓冲区
    flash_union_buffer[0].float_type  = 3.1415926;                              // 向缓冲区第 0 个位置写入 float  数据
    flash_union_buffer[1].uint32_type = 4294967294;                             // 向缓冲区第 1 个位置写入 uint32 数据
    flash_union_buffer[2].int32_type  = -2147483648;                            // 向缓冲区第 2 个位置写入 int32  数据
    flash_union_buffer[3].uint16_type = 65535;                                  // 向缓冲区第 3 个位置写入 uint16 数据
    flash_union_buffer[4].int16_type  = -32768;                                 // 向缓冲区第 4 个位置写入 int16  数据
    flash_union_buffer[5].uint8_type  = 255;                                    // 向缓冲区第 5 个位置写入 uint8  数据
    flash_union_buffer[6].int8_type   = -128;                                   // 向缓冲区第 6 个位置写入 int8   数据
    flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX, 7);     // 向指定 Flash 扇区的页码写入缓冲区数据

    printf("\r\n");
    flash_buffer_clear();                                                       // 清空缓冲区
    printf("\r\n Flash data buffer default data is :");
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以 float  格式输出
    printf("\r\n uint32_type: %d", flash_union_buffer[1].uint32_type);          // 将缓冲区第 1 个位置的数据以 uint32 格式输出
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // 将缓冲区第 2 个位置的数据以 int32  格式输出
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // 将缓冲区第 3 个位置的数据以 uint16 格式输出
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // 将缓冲区第 4 个位置的数据以 int16  格式输出
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // 将缓冲区第 5 个位置的数据以 uint8  格式输出
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // 将缓冲区第 6 个位置的数据以 int8   格式输出
    
    system_delay_ms(200);
    
    printf("\r\n");
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX, 7);        // 将数据从 flash 读取到缓冲区
    printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, new data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // 将缓冲区第 0 个位置的数据以 float  格式输出
    printf("\r\n uint32_type: %d", flash_union_buffer[1].uint32_type);          // 将缓冲区第 1 个位置的数据以 uint32 格式输出
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // 将缓冲区第 2 个位置的数据以 int32  格式输出
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // 将缓冲区第 3 个位置的数据以 uint16 格式输出
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // 将缓冲区第 4 个位置的数据以 int16  格式输出
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // 将缓冲区第 5 个位置的数据以 uint8  格式输出
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // 将缓冲区第 6 个位置的数据以 int8   格式输出
    
    
    // 此处编写用户代码 例如外设初始化代码等
    for(;;)
    {
        // 此处编写需要循环执行的代码
        

      
      
        // 此处编写需要循环执行的代码
    }
}

// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1：串口没有数据
//      查看串口助手打开的是否是正确的串口，检查打开的 COM 口是否对应的是调试下载器或者 USB-TTL 模块的 COM 口
//      如果是使用逐飞科技 CMSIS-DAP 调试下载器连接，那么检查下载器线是否松动，检查核心板串口跳线是否已经焊接，串口跳线查看核心板原理图即可找到
//      如果是使用 USB-TTL 模块连接，那么检查连线是否正常是否松动，模块 TX 是否连接的核心板的 RX，模块 RX 是否连接的核心板的 TX
//      如果上述检查都正常，但依旧没有输出数据，就进入调试看看是否进入断言，如果进入断言就更换扇区和页码尝试，如果依旧不行，那么联系技术支持
// 问题2：串口数据乱码
//      查看串口助手设置的波特率是否与程序设置一致，程序中 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义为 debug uart 使用的串口波特率
// 问题3：数据不对
//      更换扇区和页码尝试，如果数据依旧读出不正确，联系技术支持
