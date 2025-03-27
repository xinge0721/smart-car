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
* 文件名称          hall_gather
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 9.40.1
* 适用平台          CYT2BL3
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2025-01-03       pudding            first version
********************************************************************************************************************/

#ifndef _hall_gather_h_
#define _hall_gather_h_

#include "zf_common_headfile.h"


#define LEFT_MOTOR_HALL_A_PIN   P06_1           // 左电机 霍尔 A相引脚
#define LEFT_MOTOR_HALL_B_PIN   P06_0           // 左电机 霍尔 B相引脚
#define LEFT_MOTOR_HALL_C_PIN   P06_3           // 左电机 霍尔 C相引脚

#define LEFT_MOTOR_COUNT_TIMER  TC_TIME2_CH0    // 左电机 计数使用的定时器

#define LEFT_MOTOR_PIT_TIMER    PIT_CH20        // 左电机 轮询周期中断



#define RIGHT_MOTOR_HALL_A_PIN  P13_1           // 右电机 霍尔 A相引脚
#define RIGHT_MOTOR_HALL_B_PIN  P13_0           // 右电机 霍尔 B相引脚
#define RIGHT_MOTOR_HALL_C_PIN  P13_3           // 右电机 霍尔 C相引脚

#define RIGHT_MOTOR_COUNT_TIMER TC_TIME2_CH1    // 右电机 计数使用的定时器

#define RIGHT_MOTOR_PIT_TIMER   PIT_CH21        // 右电机 轮询周期中断



void motor_left_hall_callback(void);

void motor_right_hall_callback(void);

void hall_gather_init(void);










#endif
