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
* 文件名称          motor_control
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

#ifndef _motor_control_h_
#define _motor_control_h_


#include "zf_common_headfile.h"


#define ENCODER_PRECISION               (32767)                 // 编码器采样最大值  32767
#define OUTPUT_DUTY_MAX                 (PWM_PRIOD_LOAD)        // 占空比输出最大值

typedef enum
{
    LEFT_MOTOR  = 0,                            // 左侧电机
    RIGHT_MOTOR = 1,                            // 右侧电机
}motor_type_enum;

typedef enum
{
    REVERSE = -1,                               // 反转
    FORWARD = 1,                                // 正转
}motor_dir_enum;

typedef enum
{
    RROTECT_MODE,                               // 电机保护模式(磁编采值错误、电池电压过低)
    NORMAL_RUN_MODE,                            // 电机正常运行模式
}motor_protect_enum;


typedef enum
{
    MOTOR_STOP,                                 // 电机未运行
    MOTOR_RUN,                                  // 电机正在运行
}motor_run_state_enum;

typedef enum
{
    ENCODER_ERROR,                              // 磁编码器采值错误
    ENCODER_NORMAL,                             // 磁编码器工作正常
}magnetic_encoder_state_enum;

typedef enum
{
    BATTERY_HEALTH,                             // 电池电压正常    
    BATTERY_WARNING,                            // 电池低压警告
    BATTERY_ERROR                               // 电池电压异常
}battery_state_enum;

typedef struct
{         
    motor_run_state_enum                run_state;                  // 电机运行状态
        
    float                               motor_duty;                 // 电机当前占空比  0 ~ 1 
        
    int16                               zero_location;              // 电机零点位置
    int16                               rotation_direction;         // 磁编与相位输出方向
    int16                               pole_pairs;                 // 电机极对数
        
    motor_dir_enum                      motor_set_dir;              // 电机当前设置方向        
    motor_dir_enum                      motor_now_dir;              // 电机当前旋转方向
    motor_dir_enum                      motor_menc15a_dir;          // 电机与磁编码器匹配方向
        
    float                              motor_speed;                // 电机当前转速            转速单位：RPM   
    float                              motor_speed_filter;         // 电机当前转速(滤波)      转速单位：RPM   
        
    int8                                hall_value_now;             // 当前霍尔值
    int8                                hall_value_last;            // 上一次霍尔值
        
    int32                               menc15a_value_now;          // 磁编码器当前采集值              
    int32                               menc15a_value_offset;       // 磁编码器当前单次偏差值          
    int32                               menc15a_offset_integral;    // 磁编码器偏差值积分
        
    uint8                               motor_control_angle;        // 电机控制角度 范围：60 - 180 角度越大 转速越快 力矩越小
        
    float                               battery_voltage;            // 电池当前电压
    battery_state_enum                  battery_state;              // 电池当前状态
        
    motor_protect_enum                  motor_protect_state;        // 电机保护模式    
    magnetic_encoder_state_enum         encoder_state;              // 磁编码器状态    
    
    int32                               single_calculation_use_time;// 软件单次计算耗时       
}motor_struct;

extern motor_struct motor_left;
extern motor_struct motor_right;

void motor_left_update_isr(void);
void motor_right_update_isr(void);

void motor_left_zero_calibration(void);
void motor_right_zero_calibration(void);
void motor_both_zero_calibration(void);
void motor_zero_calibration(void);

void motor_foc_control_init(void);
void motor_bldc_control_init(void);
void motor_control_init(void);

void driver_cmd_forthwith(void);
void driver_cmd_loop(void);

#endif