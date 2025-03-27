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
// 使用 CYT2BL3 核心板直接接线进行测试
//      模块管脚            单片机管脚
//      DIR                 P00_2 或者 P18_6
//      PWM                 P00_3 或者 P18_7
//      GND                 GND
//      接线端子 +          电池正极
//      接线端子 -          电池负极
// 使用 CYT2BL3 学习主板进行测试
//      将模块的电源接线端子与主板的驱动供电端子连接
//      将模块的信号接口使用配套灰排线与主板电机信号接口连接 请注意接线方向 不确定方向就是用万用表确认一下 引脚参考上方核心板连接
//      将主板与供电电池正确连接


// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程 主板电池供电 连接 drv8701 单驱
// 2.如果接了电机 可以看到电机周期正反转
// 3.如果没有接电机 使用万用表可以在驱动电机输出端子上测量到输出电压变化
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查

// **************************** 代码区域 ****************************
#define MAX_DUTY            (50 )                                               // 最大 MAX_DUTY% 占空比
#define DIR1                (P00_2)
#define PWM1                (TCPWM_CH13_P00_3)
#define DIR2                (P18_6)
#define PWM2                (TCPWM_CH50_P18_7)
int8 duty = 0;
bool dir = true;

int main(void)
{
    clock_init(SYSTEM_CLOCK_160M); 	// 时钟配置及系统初始化<务必保留>
    debug_info_init();                  // 调试串口信息初始化
    
    // 此处编写用户代码 例如外设初始化代码等
    
    gpio_init(DIR1, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // GPIO 初始化为输出 默认上拉输出高
    gpio_init(DIR2, GPO, GPIO_HIGH, GPO_PUSH_PULL);                             // GPIO 初始化为输出 默认上拉输出高
    pwm_init(PWM1, 17000, 0);                                                   // PWM 通道初始化频率 17KHz 占空比初始为 0
    pwm_init(PWM2, 17000, 0);                                                   // PWM 通道初始化频率 17KHz 占空比初始为 0
    
    
    
    // 此处编写用户代码 例如外设初始化代码等
    while(true)
    {
        // 此处编写需要循环执行的代码

        if(duty >= 0)                                                           // 正转
        {
            gpio_set_level(DIR1, GPIO_HIGH);                                    // DIR输出高电平
            pwm_set_duty(PWM1, duty * (PWM_DUTY_MAX / 100));                    // 计算占空比
            gpio_set_level(DIR2, GPIO_HIGH);                                    // DIR输出高电平
            pwm_set_duty(PWM2, duty * (PWM_DUTY_MAX / 100));                    // 计算占空比
        }
        else                                                                    // 反转
        {
            gpio_set_level(DIR1, GPIO_LOW);                                     // DIR输出低电平
            pwm_set_duty(PWM1, (-duty) * (PWM_DUTY_MAX / 100));                 // 计算占空比
            gpio_set_level(DIR2, GPIO_LOW);                                     // DIR输出低电平
            pwm_set_duty(PWM2, (-duty) * (PWM_DUTY_MAX / 100));                 // 计算占空比
        }
        if(dir)                                                                 // 根据方向判断计数方向 本例程仅作参考
        {
            duty ++;                                                            // 正向计数
            if(duty >= MAX_DUTY)                                                // 达到最大值
                dir = false;                                                    // 变更计数方向
        }
        else
        {
            duty --;                                                            // 反向计数
            if(duty <= -MAX_DUTY)                                               // 达到最小值
                dir = true;                                                     // 变更计数方向
        }
        system_delay_ms(50);
          
      
        // 此处编写需要循环执行的代码
    }
}

// **************************** 代码区域 ****************************
// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1：电机不转或者模块输出电压无变化
//      如果使用主板测试，主板必须要用电池供电
//      检查模块是否正确连接供电 必须使用电源线供电 不能使用杜邦线
//      查看程序是否正常烧录，是否下载报错，确认正常按下复位按键
//      万用表测量对应 PWM 引脚电压是否变化，如果不变化证明程序未运行，或者引脚损坏，或者接触不良 联系技术客服