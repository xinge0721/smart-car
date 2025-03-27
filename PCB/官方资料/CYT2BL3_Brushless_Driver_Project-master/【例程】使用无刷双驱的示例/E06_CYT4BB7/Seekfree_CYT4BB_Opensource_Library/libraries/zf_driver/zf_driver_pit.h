/*********************************************************************************************************************
* CYT4BB Opensourec Library 即（ CYT4BB 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 CYT4BB 开源库的一部分
*
* CYT4BB 开源库 是免费软件
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
* 文件名称          zf_driver_pit
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 9.40.1
* 适用平台          CYT4BB
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2024-1-9       pudding            first version
* 2024-5-14      pudding            新增12个PIT周期中断
********************************************************************************************************************/

#ifndef _zf_driver_pit_h_
#define _zf_driver_pit_h_

#include "zf_common_typedef.h"

typedef enum // 枚举通道号
{
    PIT_CH0,            // 通道0 - 通道3 支持周期中断范围： 10us - 536s
    PIT_CH1,
    PIT_CH2,
    
    PIT_CH10,           // 通道10 - 通道21 支持周期中断范围： 10us - 1s
    PIT_CH11,
    PIT_CH12,
    PIT_CH13,
    PIT_CH14,
    PIT_CH15,
    PIT_CH16,
    PIT_CH17,
    PIT_CH18,
    PIT_CH19,
    PIT_CH20,
    PIT_CH21,
}pit_index_enum;


//====================================================PIT 基础函数====================================================
void pit_isr_flag_clear      (pit_index_enum pit_index);
void pit_all_close           (void);
void pit_disable             (pit_index_enum pit_index);
void pit_enable              (pit_index_enum pit_index);
void pit_init                (pit_index_enum pit_index, uint32 time);
//====================================================PIT 基础函数====================================================

//====================================================PIT 扩展函数====================================================
//-------------------------------------------------------------------------------------------------------------------
//  函数简介      pit_ms初始化
//  参数说明      pit_index           选择 pit 模块
//  参数说明      time                周期时间(单位：毫秒)
//  返回参数      void
//  使用示例      pit_ms_init(PIT_CH0, 5);      // 设置周期中断5ms
//-------------------------------------------------------------------------------------------------------------------
#define pit_ms_init(pit_index, time)  pit_init((pit_index), (time*1000))   // (单位为 毫秒)
//-------------------------------------------------------------------------------------------------------------------
//  函数简介      pit_us初始化 
//  参数说明      pit_index           选择 pit 模块
//  参数说明      time                周期时间(单位：微秒)
//  返回参数      void
//  使用示例      pit_us_init(PIT_CH0, 5);      // 设置周期中断5us
//-------------------------------------------------------------------------------------------------------------------
#define pit_us_init(pit_index, time)  pit_init((pit_index), (time))        // (单位为 微秒)
//====================================================PIT 扩展函数====================================================

#endif
