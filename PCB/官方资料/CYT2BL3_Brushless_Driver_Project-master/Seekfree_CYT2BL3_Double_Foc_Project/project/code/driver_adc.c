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
* 文件名称          driver_adc
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

#include "driver_adc.h"


float battery_voltage_data = 0;

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     电池电压检查
// 参数说明     void
// 返回参数     battery_state_enum  
// 使用示例     battery_check();
// 备注信息     返回当前电压对应的电池状态
//-------------------------------------------------------------------------------------------------------------------
battery_state_enum battery_check(float voltage_data)
{
    battery_state_enum battery_state = BATTERY_ERROR;  
  
#if BATTERY_PROTECT == DRIVER_ENABLE     
    
    static uint32 error_count_num = 0;
    
    static uint32 warning_count_num = 0;
    
    for(int i = 1; i <= 3; i ++)                                               // 检测电池电压是否满足锂电池电压范围 并且检测电压是否充足
    {
        if(voltage_data > (BATTERY_PROTECT_VALUE_MIN * i) && voltage_data < (BATTERY_PROTECT_VALUE_MAX * i))
        {
            if(voltage_data > (BATTERY_PROTECT_VALUE_MIN * i) && voltage_data < (BATTERY_WARNING_VALUE * i))
            {
                battery_state = BATTERY_WARNING;                                // 电池电压高于最小阈值但低于报警阈值
            }
            else
            {
                battery_state = BATTERY_HEALTH;                                 // 电池电压正常
                
                error_count_num = 0;
                
                warning_count_num = 0;
            }
            break;
        }
    }
    if(battery_state == BATTERY_WARNING && warning_count_num ++ < 50)
    {
         battery_state = BATTERY_HEALTH;                                        // 连续检测50次都低于报警阈值才认为应当报警
    }
    if(battery_state == BATTERY_ERROR && error_count_num ++ < 50)
    {
         battery_state = BATTERY_WARNING;                                       // 连续检测50次都低于最小阈值才直接关闭电源
    }
    
    if(battery_state == BATTERY_ERROR)
    {
        motor_left.motor_protect_state  = RROTECT_MODE;
        motor_right.motor_protect_state = RROTECT_MODE;
    }
    
#else
    battery_state = BATTERY_HEALTH;                                             // 电池电压正常
#endif
    return battery_state;
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     驱动的 ADC循环检测函数
// 参数说明     void
// 返回参数     void  
// 使用示例     driver_adc_loop();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void driver_adc_loop(void)
{       
    uint16 adc_data = 0;                                                        // 定义 临时 ADC 采集数据 存储位置
      
    battery_state_enum bat_state;                                               // 定义临时电池状态
    
    adc_data = adc_mean_filter_convert(BAT_ADC, 5);                             // 5次均值采样
    
    battery_voltage_data = adc_data * VOLTAGE_CONVERSION_COEFFICIENT * VOLTAGE_RECTIFY_COEFFICIENT;     // 计算实际电压  ADC数据 * 转换系数 * 矫正系数
    
    bat_state            = battery_check(battery_voltage_data);                 // 根据电压判断当前电池状态
    
    motor_left.battery_voltage  = battery_voltage_data;                         // 电压数据赋值到电机参数结构体
    
    motor_left.battery_state    = bat_state;                                    // 电池状态赋值到电机参数结构体
    
    motor_right.battery_voltage = battery_voltage_data;                         // 电压数据赋值到电机参数结构体
                                                                                
    motor_right.battery_state   = bat_state;                                    // 电池状态赋值到电机参数结构体
}


//-------------------------------------------------------------------------------------------------------------------
// 函数简介     驱动的 ADC 功能初始化
// 参数说明     void
// 返回参数     void  
// 使用示例     driver_adc_init();
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void driver_adc_init(void)
{
    adc_init(BAT_ADC, ADC_12BIT);                                               // 初始化 电池电压采集端口
}















