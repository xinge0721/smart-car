/*********************************************************************************************************************
* TC364 Opensourec Library 即（TC364 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是 TC364 开源库的一部分
*
* TC364 开源库 是免费软件
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
* 文件名称          zf_driver_adc
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          ADS v1.9.20
* 适用平台          TC364DP
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者                备注
* 2022-11-02       pudding            first version
********************************************************************************************************************/

#include "Evadc/Adc/IfxEvadc_Adc.h"
#include "zf_common_debug.h"
#include "zf_driver_adc.h"

#define ADC_SAMPLE_FREQUENCY	10000000 // 最大10Mhz

static uint8 adc_resolution[150];

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ADC 转换一次
// 参数说明     ch              选择 ADC 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 返回参数     uint16          转换的 ADC 值
// 使用示例     adc_convert(ADC1_CH0_A0);
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_convert (adc_channel_enum vadc_chn)
{
    Ifx_EVADC_G_RES result;
    uint8 temp;
    do
    {
        result = IfxEvadc_getResult(&MODULE_EVADC.G[(vadc_chn / 16)], vadc_chn%16);
    } while (!result.B.VF);

    temp = 4 - (adc_resolution[vadc_chn] * 2);
    return((result.U&0x0fff)>>temp);
}

//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ADC 均值滤波转换
// 参数说明     ch              选择 ADC 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 参数说明     count           均值滤波次数
// 返回参数     uint16          转换的 ADC 值
// 使用示例     adc_mean_filter_convert(ADC1_CH0_A0, 5);                        // 采集5次 然后返回平均值
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter_convert (adc_channel_enum vadc_chn, uint8 count)
{
    uint8 i;
    uint32 sum;

    zf_assert(count);// 断言次数不能为0

    sum = 0;
    for(i=0; i<count; i++)
    {
        sum += adc_convert(vadc_chn);
    }

    sum = sum/count;

    return (uint16)sum;
}

//-------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     ADC 初始化
// 参数说明     ch              选择 ADC 通道 (详见 zf_driver_adc.h 中枚举 adc_channel_enum 定义)
// 参数说明     resolution      选择选择通道分辨率(如果同一个 ADC 模块初始化时设置了不同的分辨率 则最后一个初始化的分辨率生效)
// 返回参数     void
// 使用示例     adc_init(ADC0_CH0_A0, ADC_8BIT);                                // 初始化 A0 为 ADC1 的 channel0 输入功能 分辨率为8位
// 备注信息
//-------------------------------------------------------------------------------------------------------------------
void adc_init (adc_channel_enum vadc_chn, adc_resolution_enum resolution)
{
    static uint8 mudule_init_flag = 0;
    static uint8 group_init_flag[9];
    IfxEvadc_Adc evadc;
    IfxEvadc_Adc_Group adcGroup;
    IfxEvadc_Adc_Config adcConfig;
    IfxEvadc_Adc_GroupConfig adcGroupConfig;

    IfxEvadc_Adc_initModuleConfig(&adcConfig, &MODULE_EVADC);
    if(!mudule_init_flag)
    {
        mudule_init_flag = 1;
        IfxEvadc_Adc_initModule(&evadc, &adcConfig);
    }
    else
    {
        evadc.evadc = adcConfig.evadc;
    }

    IfxEvadc_Adc_initGroupConfig(&adcGroupConfig, &evadc);

    adcGroupConfig.groupId = (IfxEvadc_GroupId)(vadc_chn / 16);
    adcGroupConfig.master  = adcGroupConfig.groupId;
    adcGroupConfig.arbiter.requestSlotQueue0Enabled  = TRUE;
    adcGroupConfig.queueRequest[0].triggerConfig.gatingMode = IfxEvadc_GatingMode_always;
    adcGroupConfig.inputClass[0].sampleTime = 1.0f/ADC_SAMPLE_FREQUENCY;
    adcGroupConfig.inputClass[1].sampleTime = 1.0f/ADC_SAMPLE_FREQUENCY;

    if(!group_init_flag[(vadc_chn / 16)])
    {
        group_init_flag[(vadc_chn / 16)] = 1;
        IfxEvadc_Adc_initGroup(&adcGroup, &adcGroupConfig);
    }
    else
    {
        adcGroup.groupId = adcGroupConfig.groupId;
        adcGroup.module = *adcGroupConfig.module;
        adcGroup.group = &adcGroupConfig.module->evadc->G[adcGroup.groupId];
    }

    IfxEvadc_Adc_Channel       adcChannel;
    IfxEvadc_Adc_ChannelConfig adcChannelConfig;

    IfxEvadc_Adc_initChannelConfig(&adcChannelConfig, &adcGroup);
    adcChannelConfig.channelId         = (IfxEvadc_ChannelId)(vadc_chn%16);
    adcChannelConfig.resultRegister    = (IfxEvadc_ChannelResult)(vadc_chn%16);
    IfxEvadc_Adc_initChannel(&adcChannel, &adcChannelConfig);
    IfxEvadc_Adc_addToQueue(&adcChannel, IfxEvadc_RequestSource_queue0, IFXEVADC_QUEUE_REFILL);
    IfxEvadc_Adc_startQueue(&adcGroup, IfxEvadc_RequestSource_queue0);

    adc_resolution[vadc_chn] = resolution;
}

