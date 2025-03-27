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
* 文件名称          driver_config
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
#ifndef _driver_config_h_
#define _driver_config_h_


#include "zf_common_headfile.h"

#define  DRIVER_ENABLE                  (1)             // 使能

#define  DRIVER_DISABLE                 (0)             // 失能


/************************** 驱动模式配置 **************************/

#define  FAST_FOC_MODE                  (1)             // 快速FOC驱动模式

#define  HALL_SIX_STEP_MODE             (2)             // 霍尔六步换相驱动模式   

#define  MOTOR_DRIVER_MODE              FAST_FOC_MODE   // 驱动工作模式 默认为 快速FOC驱动模式

/************************** 驱动模式配置 **************************/


/**************************** 电池保护 ****************************/
#define  BATTERY_PROTECT                DRIVER_ENABLE   // 是否开启电池保护功能(默认开启)      DRIVER_ENABLE: 开启电池保护    DRIVER_DISABLE: 不开启电池保护 
         
#define  BATTERY_PROTECT_VALUE_MIN      (3.5f)          // 允许的单节电芯最小电压 低于此值将直接关闭电机  驱动板蓝灯高频闪烁(100ms）
         
#define  BATTERY_PROTECT_VALUE_MAX      (4.3f)          // 允许的单节电芯最大电压 
         
#define  BATTERY_WARNING_VALUE          (3.9f)          // 单节电芯电压报警阈值 (暂未做出警报动作) 
/**************************** 电池保护 ****************************/


/**************************** 堵转保护 ****************************/
#define  MOTOR_LOCKED_PROTECT           DRIVER_ENABLE   // 是否开启堵转保护功能(默认开启)      DRIVER_ENABLE: 开启堵转保护    DRIVER_DISABLE: 不开启堵转保护 
         
#define  MOTOR_LOCKED_DUTY_MAX          (0.2f)          // 堵转检测最大占空比(默认20%)  若超过此值并且电机未旋转 则认为可能堵转
         
#define  MOTOR_LOCKED_TIME              (500)           // 堵转检测时长(默认500ms)      若认为电机可能堵转 并且持续时长超过此值 则认定为堵转状态
/**************************** 堵转保护 ****************************/


#endif
