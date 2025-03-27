/*********************************************************************************************************************
* CYT2BL3 Opensourec Library ���� CYT2BL3 ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
*
* ���ļ��� CYT2BL3 ��Դ���һ����
*
* CYT2BL3 ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
*
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
*
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
*
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
*
* �ļ�����          pwm_output
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 9.40.1
* ����ƽ̨          CYT2BL3
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2025-01-03       pudding            first version
********************************************************************************************************************/

#include "pwm_output.h"

//-------------------------------------------------------------------------------------------------------------------
// �������     ����PWMͨ����ʼ��
// ����˵��     void      
// ���ز���     void
// ʹ��ʾ��     motor_left_output_init(PWM_PRIOD_LOAD);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_left_output_init(uint16 timer_period)
{
    /******************************����ֲ�����******************************/
    cy_stc_gpio_pin_config_t            pwm_pin_config;                         // ����PWM�������ö���
    cy_stc_tcpwm_pwm_config_t           tcpwm_pwm_config;                       // ����PWM��ʱ�����ö���    
#if MOTOR_DRIVER_MODE    == FAST_FOC_MODE  
    cy_stc_sysint_irq_t                 tcpwm_irq_cfg;                          // ����PWM�����ж϶���
#endif
    /******************************����ֲ�����******************************/
    
    
    /******************************����PWM����******************************/
    memset(&pwm_pin_config, 0, sizeof(pwm_pin_config));                         // ���PWM���Ŷ������ 
    
    pwm_pin_config.driveMode                     = CY_GPIO_DM_STRONG;           // ����PWM�������ģʽΪǿ����ģʽ
    // ��ʼ��A����������
    pwm_pin_config.hsiom                         = MOTOR_LEFT_A_PIN_HSIOM_H;
    Cy_GPIO_Pin_Init(MOTOR_LEFT_A_PHASE_PORT_H, MOTOR_LEFT_A_PHASE_PIN_H, &pwm_pin_config);
    // ��ʼ��A����������
    pwm_pin_config.hsiom                         = MOTOR_LEFT_A_PIN_HSIOM_L;
    Cy_GPIO_Pin_Init(MOTOR_LEFT_A_PHASE_PORT_L, MOTOR_LEFT_A_PHASE_PIN_L, &pwm_pin_config);
    // ��ʼ��B����������
    pwm_pin_config.hsiom                         = MOTOR_LEFT_B_PIN_HSIOM_H;
    Cy_GPIO_Pin_Init(MOTOR_LEFT_B_PHASE_PORT_H, MOTOR_LEFT_B_PHASE_PIN_H, &pwm_pin_config);
    // ��ʼ��B����������
    pwm_pin_config.hsiom                         = MOTOR_LEFT_B_PIN_HSIOM_L;
    Cy_GPIO_Pin_Init(MOTOR_LEFT_B_PHASE_PORT_L, MOTOR_LEFT_B_PHASE_PIN_L, &pwm_pin_config);
    // ��ʼ��C����������
    pwm_pin_config.hsiom                         = MOTOR_LEFT_C_PIN_HSIOM_H;
    Cy_GPIO_Pin_Init(MOTOR_LEFT_C_PHASE_PORT_H, MOTOR_LEFT_C_PHASE_PIN_H, &pwm_pin_config);
    // ��ʼ��C����������
    pwm_pin_config.hsiom                         = MOTOR_LEFT_C_PIN_HSIOM_L;
    Cy_GPIO_Pin_Init(MOTOR_LEFT_C_PHASE_PORT_L, MOTOR_LEFT_C_PHASE_PIN_L, &pwm_pin_config);
    /******************************����PWM����******************************/

    /****************************����PWM��ʱ��ʱ��***************************/
    // ��ʼ��A��ʱ��  ʹ��16λ��Ƶ����ͨ��2 ����Ƶֱ�����80Mhzʱ�ӵ���ʱ�� 
    Cy_SysClk_PeriphAssignDivider(MOTOR_LEFT_A_PHASE_TCPWM_CLOCK, CY_SYSCLK_DIV_16_BIT, 2);
    Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 2, 0); 
    Cy_SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 2);
    // ��ʼ��B��ʱ��  ʹ��16λ��Ƶ����ͨ��2 ����Ƶֱ�����80Mhzʱ�ӵ���ʱ�� 
    Cy_SysClk_PeriphAssignDivider(MOTOR_LEFT_B_PHASE_TCPWM_CLOCK, CY_SYSCLK_DIV_16_BIT, 2);
    Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 2, 0); 
    Cy_SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 2);
    // ��ʼ��C��ʱ��  ʹ��16λ��Ƶ����ͨ��2 ����Ƶֱ�����80Mhzʱ�ӵ���ʱ�� 
    Cy_SysClk_PeriphAssignDivider(MOTOR_LEFT_C_PHASE_TCPWM_CLOCK, CY_SYSCLK_DIV_16_BIT, 2);
    Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 2, 0); 
    Cy_SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 2);
    /****************************����PWM��ʱ��ʱ��***************************/
    
    /******************************����PWM�ж�******************************/
#if MOTOR_DRIVER_MODE    == FAST_FOC_MODE  
    tcpwm_irq_cfg.sysIntSrc  = MOTOR_LEFT_TCPWM_ISR_CHANNEL;                            // ѡ���жϴ���Դ
    tcpwm_irq_cfg.intIdx     = CPUIntIdx3_IRQn;                                         // ѡ���жϴ���ͨ��Ϊ�û��ж�7
    tcpwm_irq_cfg.isEnabled  = true;                                                    // �����жϴ���
    
    Cy_SysInt_InitIRQ(&tcpwm_irq_cfg);                                                  // ��ʼ���ж����ò���
    Cy_SysInt_SetSystemIrqVector(tcpwm_irq_cfg.sysIntSrc, motor_left_update_isr);       // ���õ�ǰ�жϻص�����Ϊ motor_left_updat_isr
    NVIC_SetPriority(tcpwm_irq_cfg.intIdx, 0u);                                         // �����ж����ȼ�Ϊ0 (������ȼ�)
    NVIC_ClearPendingIRQ(tcpwm_irq_cfg.intIdx);                                         // ����ж�����Ĺ���״̬
    NVIC_EnableIRQ(tcpwm_irq_cfg.intIdx);                                               // ʹ�ܵ�ǰ�ж�
#endif
    /******************************����PWM�ж�******************************/
    
    /*****************************����PWM��ʱ��******************************/
    memset(&tcpwm_pwm_config, 0, sizeof(tcpwm_pwm_config));                     // �����ʱ�����ò���
    
    tcpwm_pwm_config.pwmMode            = CY_TCPWM_PWM_MODE_DEADTIME      ;     // ��ǰģʽΪPWM����ģʽ ���Ի������������������ʱ��
    tcpwm_pwm_config.countDirection     = CY_TCPWM_COUNTER_COUNT_UP       ;     // ���������ϼ���
    tcpwm_pwm_config.cc0MatchMode       = CY_TCPWM_PWM_TR_CTRL2_SET       ;     // ���ȽϼĴ���0�������ƥ��ʱ �����������
    tcpwm_pwm_config.cc1MatchMode       = CY_TCPWM_PWM_TR_CTRL2_CLEAR     ;     // ���ȽϼĴ���1�������ƥ��ʱ �����������
    tcpwm_pwm_config.overflowMode       = CY_TCPWM_PWM_TR_CTRL2_CLEAR     ;     // ������������ʱ �����������
    tcpwm_pwm_config.underflowMode      = CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE ;     // ������������ʱ ��������仯(���ϼ���ģʽ���ᴥ����������)
    tcpwm_pwm_config.deadTime           = 10                              ;     // ����ʱ��Ϊ10��ʱ������ 80mhzʱ�ӵ�10������Ϊ125ns
    tcpwm_pwm_config.deadTimeComp       = 10                              ;     // ����ͨ������ʱ��ҲΪ10��ʱ������ 
    tcpwm_pwm_config.runMode            = CY_TCPWM_PWM_CONTINUOUS         ;     // �������� �������PWM�ź�
    tcpwm_pwm_config.clockPrescaler     = CY_TCPWM_PRESCALER_DIVBY_1      ;     // ʱ��1��Ƶ 80Mhzʱ��ֱ�������ڶ�ʱ�� ��λʱ������Ϊ12.5ns
    tcpwm_pwm_config.period             = (timer_period - 1)              ;     // ��ʱ������Ϊtimer_period 80Mhz�������ڵõ�Ƶ��
    tcpwm_pwm_config.compare0           = 0                               ;     // �ȽϼĴ���0���
    tcpwm_pwm_config.compare1           = 0                               ;     // �ȽϼĴ���1���
    tcpwm_pwm_config.enableCompare0Swap = true                            ;     // �Ƚ���0����ʹ�� �˴�ΪԤװ�ع���ʵ�� �û��ıȽ�����д�뻺���� ����¼��������������������Լ�ʵ�ʱȽϼĴ�����ֵ
    tcpwm_pwm_config.enableCompare1Swap = true                            ;     // �Ƚ���1����ʹ��
    tcpwm_pwm_config.killMode           = CY_TCPWM_PWM_STOP_ON_KILL       ;     // �رն�ʱ��ʱֹͣ����
    tcpwm_pwm_config.countInputMode     = CY_TCPWM_INPUT_LEVEL            ;     // �����¼�Ϊ����
    tcpwm_pwm_config.countInput         = 1uL                             ;     // �����¼�����ߵ�ƽ
    tcpwm_pwm_config.trigger0EventCfg   = CY_TCPWM_COUNTER_OVERFLOW       ;     // �жϴ����¼�0Ϊ���ʱ�����ж�
    tcpwm_pwm_config.trigger1EventCfg   = CY_TCPWM_COUNTER_OVERFLOW       ;     // �жϴ����¼�1Ϊ���ʱ�����ж�

    // ��ʼ��A��PWMͨ��   �����������ͨ�����ò���һ�� ��ֱ��ʹ��ͬһ�����ö��������ͨ����ɲ�������
    Cy_Tcpwm_Pwm_Init(MOTOR_LEFT_A_PHASE_TCPWM_TIMER, &tcpwm_pwm_config);
    Cy_Tcpwm_Pwm_Enable(MOTOR_LEFT_A_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_Counter_SetTC_IntrMask(MOTOR_LEFT_A_PHASE_TCPWM_TIMER);            // ʹ�ܶ�ʱ���ж�
#if MOTOR_DRIVER_MODE    == FAST_FOC_MODE  
    Cy_Tcpwm_TriggerStart(MOTOR_LEFT_A_PHASE_TCPWM_TIMER);
#endif
    // ��ʼ��B��PWMͨ��   �����������ͨ�����ò���һ�� ��ֱ��ʹ��ͬһ�����ö��������ͨ����ɲ�������
    Cy_Tcpwm_Pwm_Init(MOTOR_LEFT_B_PHASE_TCPWM_TIMER, &tcpwm_pwm_config);
    Cy_Tcpwm_Pwm_Enable(MOTOR_LEFT_B_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_TriggerStart(MOTOR_LEFT_B_PHASE_TCPWM_TIMER);
    
    // ��ʼ��C��PWMͨ��   �����������ͨ�����ò���һ�� ��ֱ��ʹ��ͬһ�����ö��������ͨ����ɲ�������
    Cy_Tcpwm_Pwm_Init(MOTOR_LEFT_C_PHASE_TCPWM_TIMER, &tcpwm_pwm_config);
    Cy_Tcpwm_Pwm_Enable(MOTOR_LEFT_C_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_TriggerStart(MOTOR_LEFT_C_PHASE_TCPWM_TIMER);
    /*****************************����PWM��ʱ��******************************/
    
    /***************************��ʱ������ͬ������****************************/
    // ��������ͨ�����Ƕ����Ķ�ʱ�� ��ôcounter�Ĵ����ļ���ֵҲ�Ǹ��Լ���
    // ���counter��ͬ���Ļ� �������·PWM���ξ��޷�����
    // �˴�Ϊ��򵥵�αͬ��������������ת�������·counter�Ĵ�������
    // ���Ȼ�ȡcounter�Ĵ����ĵ�ַ
    uint32_t pwm_a_count_address = MOTOR_LEFT_A_PHASE_TCPWM_ADDR + 0x00000008;                    // ͨ����ַ + COUNTER�Ĵ���ƫ����
    uint32_t pwm_b_count_address = MOTOR_LEFT_B_PHASE_TCPWM_ADDR + 0x00000008;                    // ͨ����ַ + COUNTER�Ĵ���ƫ����
    uint32_t pwm_c_count_address = MOTOR_LEFT_C_PHASE_TCPWM_ADDR + 0x00000008;                    // ͨ����ַ + COUNTER�Ĵ���ƫ����
    // ͨ��ָ����ʼĴ�����ַ
    volatile uint32_t *pwm_a_count_pointer = (volatile uint32_t *)pwm_a_count_address;
    volatile uint32_t *pwm_b_count_pointer = (volatile uint32_t *)pwm_b_count_address;
    volatile uint32_t *pwm_c_count_pointer = (volatile uint32_t *)pwm_c_count_address;
    // ֱ�Ӷ�ָ��ָ��ļĴ�����ֵ0
    *pwm_a_count_pointer     = 0;    
    *pwm_b_count_pointer     = 0;
    *pwm_c_count_pointer     = 0;
    /***************************��ʱ������ͬ������****************************/
    
    motor_left_channel_set(1,1,1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���������ͨ��ռ�ձ�����
// ����˵��     a_duty       A��ռ�ձ���Ϣ ���ֵ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)
// ����˵��     b_duty       A��ռ�ձ���Ϣ ���ֵ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)
// ����˵��     c_duty       A��ռ�ձ���Ϣ ���ֵ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)
// ���ز���     void
// ʹ��ʾ��     motor_left_duty_set(200, 300, 400);
// ��ע��Ϣ     ���±Ƚ������ҽ�����������
//-------------------------------------------------------------------------------------------------------------------
void motor_left_duty_set(uint16 a_duty, uint16 b_duty, uint16 c_duty)
{
    MOTOR_LEFT_A_PHASE_TCPWM_TIMER->unCC0_BUFF.u32Register = (PWM_PRIOD_LOAD - a_duty) / 2;  // ����A��ͨ���Ƚ���1��ֵ
    MOTOR_LEFT_A_PHASE_TCPWM_TIMER->unCC1_BUFF.u32Register = (PWM_PRIOD_LOAD + a_duty) / 2;  // ����A��ͨ���Ƚ���2��ֵ
    MOTOR_LEFT_B_PHASE_TCPWM_TIMER->unCC0_BUFF.u32Register = (PWM_PRIOD_LOAD - b_duty) / 2;  // ����B��ͨ���Ƚ���1��ֵ
    MOTOR_LEFT_B_PHASE_TCPWM_TIMER->unCC1_BUFF.u32Register = (PWM_PRIOD_LOAD + b_duty) / 2;  // ����B��ͨ���Ƚ���2��ֵ
    MOTOR_LEFT_C_PHASE_TCPWM_TIMER->unCC0_BUFF.u32Register = (PWM_PRIOD_LOAD - c_duty) / 2;  // ����C��ͨ���Ƚ���1��ֵ
    MOTOR_LEFT_C_PHASE_TCPWM_TIMER->unCC1_BUFF.u32Register = (PWM_PRIOD_LOAD + c_duty) / 2;  // ����C��ͨ���Ƚ���2��ֵ
    MOTOR_LEFT_A_PHASE_TCPWM_TIMER->unTR_CMD.u32Register  |= 1;  // ����A��ͨ������ʹ��
    MOTOR_LEFT_B_PHASE_TCPWM_TIMER->unTR_CMD.u32Register  |= 1;  // ����B��ͨ������ʹ��
    MOTOR_LEFT_C_PHASE_TCPWM_TIMER->unTR_CMD.u32Register  |= 1;  // ����C��ͨ������ʹ��
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���������ͨ��ʹ��ѡ��
// ����˵��     a_channel       0���ر�A�����ͨ��  1������A�����ͨ��  
// ����˵��     b_channel       0���ر�B�����ͨ��  1������B�����ͨ��  
// ����˵��     c_channel       0���ر�C�����ͨ��  1������C�����ͨ��  
// ���ز���     void
// ʹ��ʾ��     motor_left_channel_set(1,0,1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_left_channel_set(uint8 a_channel, uint8 b_channel, uint8 c_channel)
{     
    if(a_channel)                                                               // ��A��ͨ��ʹ������ͨ��
    {
        MOTOR_LEFT_A_PHASE_TCPWM_TIMER->unCTRL.u32Register       |= 0x80000000;              // ʹ�ܶ�ʱ��
        MOTOR_LEFT_A_PHASE_TCPWM_TIMER->unTR_CMD.u32Register      = 0x00000004;              // ��������
    }
    else                                                                        // ����ر�A��ͨ��ʹ��
    {
        MOTOR_LEFT_A_PHASE_TCPWM_TIMER->unCTRL.u32Register       &= 0x7FFFFFFF;              // �ر�A��ͨ��ʹ��
    }   
    if(b_channel)                                                               // ��B��ͨ��ʹ������ͨ��
    {                                                                             
        MOTOR_LEFT_B_PHASE_TCPWM_TIMER->unCTRL.u32Register        |= 0x80000000;              // ʹ�ܶ�ʱ�� 
        MOTOR_LEFT_B_PHASE_TCPWM_TIMER->unTR_CMD.u32Register       = 0x00000004;              // �������� 
    }                                                                             
    else                                                                        // ����ر�B��ͨ��ʹ��
    {                                                                             
        MOTOR_LEFT_B_PHASE_TCPWM_TIMER->unCTRL.u32Register        &= 0x7FFFFFFF;              // �ر�B��ͨ��ʹ�� 
    }
    if(c_channel)                                                               // ��C��ͨ��ʹ������ͨ��
    {                                                                               
        MOTOR_LEFT_C_PHASE_TCPWM_TIMER->unCTRL.u32Register       |= 0x80000000;              // ʹ�ܶ�ʱ��  
        MOTOR_LEFT_C_PHASE_TCPWM_TIMER->unTR_CMD.u32Register      = 0x00000004;              // ��������  
    }                                                                               
    else                                                                        // ����ر�C��ͨ��ʹ��
    {                                                                               
        MOTOR_LEFT_C_PHASE_TCPWM_TIMER->unCTRL.u32Register       &= 0x7FFFFFFF;              // �ر�C��ͨ��ʹ��  
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���������MOS��Ԥ�����ܲ��� 
// ���ز���     void
// ʹ��ʾ��     motor_left_phase_check();
// ��ע��Ϣ     �ú�����ͨ�����Ʋ�ͬͨ����MOS��ʹ���������ͬƵ�ʵ����������ڲ���Ӳ�����ܣ����ú�������������ʼ��PWM��ʱ��ģ��  
//-------------------------------------------------------------------------------------------------------------------
void motor_left_phase_check(void)
{
    uint16 check_period;
    uint16 delay_time = 100;
    
    // ��һ��  A������ �� B������
    check_period = 36000;                       // 2.222khz
    
    motor_left_output_init(check_period);
    
    motor_left_channel_set(1,1,0);
    
    motor_left_duty_set(check_period / 50, 0, 0);
    
    system_delay_ms(delay_time);
    
    motor_left_duty_set(0, 0, 0);
    
    system_delay_ms(50);
    
    // �ڶ���  B������ �� C������
    check_period = 35000;                       // 2.285khz
    
    motor_left_output_init(check_period);
    
    motor_left_channel_set(0,1,1);
    
    motor_left_duty_set(0, check_period / 50, 0);
    
    system_delay_ms(delay_time);
    
    motor_left_duty_set(0, 0, 0);
    
    system_delay_ms(50);
    
    // ������  C������ �� A������
    check_period = 34000;                       // 2.352khz
    
    motor_left_output_init(check_period);
    
    motor_left_channel_set(1,0,1);
    
    motor_left_duty_set(0, 0, check_period / 50);
    
    system_delay_ms(delay_time);
    
    motor_left_duty_set(0, 0, 0);
    
    system_delay_ms(50);
    
    Cy_Tcpwm_Pwm_DeInit(MOTOR_LEFT_A_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_Pwm_DeInit(MOTOR_LEFT_B_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_Pwm_DeInit(MOTOR_LEFT_C_PHASE_TCPWM_TIMER);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �Ҳ���PWMͨ����ʼ��
// ����˵��     void      
// ���ز���     void
// ʹ��ʾ��     motor_right_output_init(PWM_PRIOD_LOAD);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_right_output_init(uint16 timer_period)
{
    /******************************����ֲ�����******************************/
    cy_stc_gpio_pin_config_t            pwm_pin_config;                         // ����PWM�������ö���
    cy_stc_tcpwm_pwm_config_t           tcpwm_pwm_config;                       // ����PWM��ʱ�����ö���
#if MOTOR_DRIVER_MODE    == FAST_FOC_MODE  
    cy_stc_sysint_irq_t                 tcpwm_irq_cfg;                          // ����PWM�����ж϶���
#endif
    /******************************����ֲ�����******************************/
    
    
    /******************************����PWM����******************************/
    memset(&pwm_pin_config, 0, sizeof(pwm_pin_config));                         // ���PWM���Ŷ������ 
    
    pwm_pin_config.driveMode                     = CY_GPIO_DM_STRONG;           // ����PWM�������ģʽΪǿ����ģʽ
    // ��ʼ��A����������
    pwm_pin_config.hsiom                         = MOTOR_RIGHT_A_PIN_HSIOM_H;
    Cy_GPIO_Pin_Init(MOTOR_RIGHT_A_PHASE_PORT_H, MOTOR_RIGHT_A_PHASE_PIN_H, &pwm_pin_config);
    // ��ʼ��A����������
    pwm_pin_config.hsiom                         = MOTOR_RIGHT_A_PIN_HSIOM_L;
    Cy_GPIO_Pin_Init(MOTOR_RIGHT_A_PHASE_PORT_L, MOTOR_RIGHT_A_PHASE_PIN_L, &pwm_pin_config);
    // ��ʼ��B����������
    pwm_pin_config.hsiom                         = MOTOR_RIGHT_B_PIN_HSIOM_H;
    Cy_GPIO_Pin_Init(MOTOR_RIGHT_B_PHASE_PORT_H, MOTOR_RIGHT_B_PHASE_PIN_H, &pwm_pin_config);
    // ��ʼ��B����������
    pwm_pin_config.hsiom                         = MOTOR_RIGHT_B_PIN_HSIOM_L;
    Cy_GPIO_Pin_Init(MOTOR_RIGHT_B_PHASE_PORT_L, MOTOR_RIGHT_B_PHASE_PIN_L, &pwm_pin_config);
    // ��ʼ��C����������
    pwm_pin_config.hsiom                         = MOTOR_RIGHT_C_PIN_HSIOM_H;
    Cy_GPIO_Pin_Init(MOTOR_RIGHT_C_PHASE_PORT_H, MOTOR_RIGHT_C_PHASE_PIN_H, &pwm_pin_config);
    // ��ʼ��C����������
    pwm_pin_config.hsiom                         = MOTOR_RIGHT_C_PIN_HSIOM_L;
    Cy_GPIO_Pin_Init(MOTOR_RIGHT_C_PHASE_PORT_L, MOTOR_RIGHT_C_PHASE_PIN_L, &pwm_pin_config);
    /******************************����PWM����******************************/

    /****************************����PWM��ʱ��ʱ��***************************/
    // ��ʼ��A��ʱ��  ʹ��16λ��Ƶ����ͨ��1 ����Ƶֱ�����80Mhzʱ�ӵ���ʱ�� 
    Cy_SysClk_PeriphAssignDivider(MOTOR_RIGHT_A_PHASE_TCPWM_CLOCK, CY_SYSCLK_DIV_16_BIT, 2);
    Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 2, 0); 
    Cy_SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 2);
    // ��ʼ��B��ʱ��  ʹ��16λ��Ƶ����ͨ��1 ����Ƶֱ�����80Mhzʱ�ӵ���ʱ�� 
    Cy_SysClk_PeriphAssignDivider(MOTOR_RIGHT_B_PHASE_TCPWM_CLOCK, CY_SYSCLK_DIV_16_BIT, 2);
    Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 2, 0); 
    Cy_SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 2);
    // ��ʼ��C��ʱ��  ʹ��16λ��Ƶ����ͨ��1 ����Ƶֱ�����80Mhzʱ�ӵ���ʱ�� 
    Cy_SysClk_PeriphAssignDivider(MOTOR_RIGHT_C_PHASE_TCPWM_CLOCK, CY_SYSCLK_DIV_16_BIT, 2);
    Cy_SysClk_PeriphSetDivider(CY_SYSCLK_DIV_16_BIT, 2, 0); 
    Cy_SysClk_PeriphEnableDivider(CY_SYSCLK_DIV_16_BIT, 2);
    /****************************����PWM��ʱ��ʱ��***************************/
    
    /******************************����PWM�ж�******************************/
#if MOTOR_DRIVER_MODE    == FAST_FOC_MODE  
    tcpwm_irq_cfg.sysIntSrc  = MOTOR_RIGHT_TCPWM_ISR_CHANNEL;                           // ѡ���жϴ���Դ
    tcpwm_irq_cfg.intIdx     = CPUIntIdx4_IRQn;                                         // ѡ���жϴ���ͨ��Ϊ�û��ж�7
    tcpwm_irq_cfg.isEnabled  = true;                                                    // �����жϴ���
    
    Cy_SysInt_InitIRQ(&tcpwm_irq_cfg);                                                  // ��ʼ���ж����ò���
    Cy_SysInt_SetSystemIrqVector(tcpwm_irq_cfg.sysIntSrc, motor_right_update_isr);      // ���õ�ǰ�жϻص�����Ϊ motor_right_updat_isr
    NVIC_SetPriority(tcpwm_irq_cfg.intIdx, 0u);                                         // �����ж����ȼ�Ϊ0 (������ȼ�)
    NVIC_ClearPendingIRQ(tcpwm_irq_cfg.intIdx);                                         // ����ж�����Ĺ���״̬
    NVIC_EnableIRQ(tcpwm_irq_cfg.intIdx);                                               // ʹ�ܵ�ǰ�ж�
#endif
    /******************************����PWM�ж�******************************/
    
    /*****************************����PWM��ʱ��******************************/
    memset(&tcpwm_pwm_config, 0, sizeof(tcpwm_pwm_config));                     // �����ʱ�����ò���
    
    tcpwm_pwm_config.pwmMode            = CY_TCPWM_PWM_MODE_DEADTIME      ;     // ��ǰģʽΪPWM����ģʽ ���Ի������������������ʱ��
    tcpwm_pwm_config.countDirection     = CY_TCPWM_COUNTER_COUNT_UP       ;     // ���������ϼ���
    tcpwm_pwm_config.cc0MatchMode       = CY_TCPWM_PWM_TR_CTRL2_SET       ;     // ���ȽϼĴ���0�������ƥ��ʱ �����������
    tcpwm_pwm_config.cc1MatchMode       = CY_TCPWM_PWM_TR_CTRL2_CLEAR     ;     // ���ȽϼĴ���1�������ƥ��ʱ �����������
    tcpwm_pwm_config.overflowMode       = CY_TCPWM_PWM_TR_CTRL2_CLEAR     ;     // ������������ʱ �����������
    tcpwm_pwm_config.underflowMode      = CY_TCPWM_PWM_TR_CTRL2_NO_CHANGE ;     // ������������ʱ ��������仯(���ϼ���ģʽ���ᴥ����������)
    tcpwm_pwm_config.deadTime           = 10                              ;     // ����ʱ��Ϊ10��ʱ������ 80mhzʱ�ӵ�10������Ϊ125ns
    tcpwm_pwm_config.deadTimeComp       = 10                              ;     // ����ͨ������ʱ��ҲΪ10��ʱ������ 
    tcpwm_pwm_config.runMode            = CY_TCPWM_PWM_CONTINUOUS         ;     // �������� �������PWM�ź�
    tcpwm_pwm_config.clockPrescaler     = CY_TCPWM_PRESCALER_DIVBY_1      ;     // ʱ��1��Ƶ 80Mhzʱ��ֱ�������ڶ�ʱ�� ��λʱ������Ϊ12.5ns
    tcpwm_pwm_config.period             = (timer_period - 1)              ;     // ��ʱ������Ϊtimer_period 80Mhz�������ڵõ�Ƶ��
    tcpwm_pwm_config.compare0           = 0                               ;     // �ȽϼĴ���0���
    tcpwm_pwm_config.compare1           = 0                               ;     // �ȽϼĴ���1���
    tcpwm_pwm_config.enableCompare0Swap = true                            ;     // �Ƚ���0����ʹ�� �˴�ΪԤװ�ع���ʵ�� �û��ıȽ�����д�뻺���� ����¼��������������������Լ�ʵ�ʱȽϼĴ�����ֵ
    tcpwm_pwm_config.enableCompare1Swap = true                            ;     // �Ƚ���1����ʹ��
    tcpwm_pwm_config.killMode           = CY_TCPWM_PWM_STOP_ON_KILL       ;     // �رն�ʱ��ʱֹͣ����
    tcpwm_pwm_config.countInputMode     = CY_TCPWM_INPUT_LEVEL            ;     // �����¼�Ϊ����
    tcpwm_pwm_config.countInput         = 1uL                             ;     // �����¼�����ߵ�ƽ
    tcpwm_pwm_config.trigger0EventCfg   = CY_TCPWM_COUNTER_OVERFLOW       ;     // �жϴ����¼�0Ϊ���ʱ�����ж�
    tcpwm_pwm_config.trigger1EventCfg   = CY_TCPWM_COUNTER_OVERFLOW       ;     // �жϴ����¼�1Ϊ���ʱ�����ж�
    // ��ʼ��A��PWMͨ��   �����������ͨ�����ò���һ�� ��ֱ��ʹ��ͬһ�����ö��������ͨ����ɲ�������
    Cy_Tcpwm_Pwm_Init(MOTOR_RIGHT_A_PHASE_TCPWM_TIMER, &tcpwm_pwm_config);
    Cy_Tcpwm_Pwm_Enable(MOTOR_RIGHT_A_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_Counter_SetTC_IntrMask(MOTOR_RIGHT_A_PHASE_TCPWM_TIMER);            // ʹ�ܶ�ʱ���ж�
#if MOTOR_DRIVER_MODE    == FAST_FOC_MODE  
    Cy_Tcpwm_TriggerStart(MOTOR_RIGHT_A_PHASE_TCPWM_TIMER);
#endif
    // ��ʼ��B��PWMͨ��   �����������ͨ�����ò���һ�� ��ֱ��ʹ��ͬһ�����ö��������ͨ����ɲ�������
    Cy_Tcpwm_Pwm_Init(MOTOR_RIGHT_B_PHASE_TCPWM_TIMER, &tcpwm_pwm_config);
    Cy_Tcpwm_Pwm_Enable(MOTOR_RIGHT_B_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_TriggerStart(MOTOR_RIGHT_B_PHASE_TCPWM_TIMER);
    
    // ��ʼ��C��PWMͨ��   �����������ͨ�����ò���һ�� ��ֱ��ʹ��ͬһ�����ö��������ͨ����ɲ�������
    Cy_Tcpwm_Pwm_Init(MOTOR_RIGHT_C_PHASE_TCPWM_TIMER, &tcpwm_pwm_config);
    Cy_Tcpwm_Pwm_Enable(MOTOR_RIGHT_C_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_TriggerStart(MOTOR_RIGHT_C_PHASE_TCPWM_TIMER);
    /*****************************����PWM��ʱ��******************************/
    
    /***************************��ʱ������ͬ������****************************/
    // ��������ͨ�����Ƕ����Ķ�ʱ�� ��ôcounter�Ĵ����ļ���ֵҲ�Ǹ��Լ���
    // ���counter��ͬ���Ļ� �������·PWM���ξ��޷�����
    // �˴�Ϊ��򵥵�αͬ��������������ת�������·counter�Ĵ�������
    // ���Ȼ�ȡcounter�Ĵ����ĵ�ַ
    uint32_t pwm_a_count_address = MOTOR_RIGHT_A_PHASE_TCPWM_ADDR + 0x00000008;                    // ͨ����ַ + COUNTER�Ĵ���ƫ����
    uint32_t pwm_b_count_address = MOTOR_RIGHT_B_PHASE_TCPWM_ADDR + 0x00000008;                    // ͨ����ַ + COUNTER�Ĵ���ƫ����
    uint32_t pwm_c_count_address = MOTOR_RIGHT_C_PHASE_TCPWM_ADDR + 0x00000008;                    // ͨ����ַ + COUNTER�Ĵ���ƫ����
    // ͨ��ָ����ʼĴ�����ַ
    volatile uint32_t *pwm_a_count_pointer = (volatile uint32_t *)pwm_a_count_address;
    volatile uint32_t *pwm_b_count_pointer = (volatile uint32_t *)pwm_b_count_address;
    volatile uint32_t *pwm_c_count_pointer = (volatile uint32_t *)pwm_c_count_address;
    // ֱ�Ӷ�ָ��ָ��ļĴ�����ֵ0
    *pwm_a_count_pointer     = 0;    
    *pwm_b_count_pointer     = 0;
    *pwm_c_count_pointer     = 0;
    /***************************��ʱ������ͬ������****************************/
    
    motor_right_channel_set(1,1,1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �Ҳ�������ͨ��ռ�ձ�����
// ����˵��     a_duty       A��ռ�ձ���Ϣ ���ֵ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)
// ����˵��     b_duty       A��ռ�ձ���Ϣ ���ֵ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)
// ����˵��     c_duty       A��ռ�ձ���Ϣ ���ֵ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)
// ���ز���     void
// ʹ��ʾ��     motor_left_duty_set(200, 300, 400);
// ��ע��Ϣ     ���±Ƚ������ҽ�����������
//-------------------------------------------------------------------------------------------------------------------
void motor_right_duty_set(uint16 a_duty, uint16 b_duty, uint16 c_duty)
{
    MOTOR_RIGHT_A_PHASE_TCPWM_TIMER->unCC0_BUFF.u32Register = (PWM_PRIOD_LOAD - a_duty) / 2;  // ����A��ͨ���Ƚ���1��ֵ
    MOTOR_RIGHT_A_PHASE_TCPWM_TIMER->unCC1_BUFF.u32Register = (PWM_PRIOD_LOAD + a_duty) / 2;  // ����A��ͨ���Ƚ���2��ֵ
    MOTOR_RIGHT_B_PHASE_TCPWM_TIMER->unCC0_BUFF.u32Register = (PWM_PRIOD_LOAD - b_duty) / 2;  // ����B��ͨ���Ƚ���1��ֵ
    MOTOR_RIGHT_B_PHASE_TCPWM_TIMER->unCC1_BUFF.u32Register = (PWM_PRIOD_LOAD + b_duty) / 2;  // ����B��ͨ���Ƚ���2��ֵ
    MOTOR_RIGHT_C_PHASE_TCPWM_TIMER->unCC0_BUFF.u32Register = (PWM_PRIOD_LOAD - c_duty) / 2;  // ����C��ͨ���Ƚ���1��ֵ
    MOTOR_RIGHT_C_PHASE_TCPWM_TIMER->unCC1_BUFF.u32Register = (PWM_PRIOD_LOAD + c_duty) / 2;  // ����C��ͨ���Ƚ���2��ֵ
    MOTOR_RIGHT_A_PHASE_TCPWM_TIMER->unTR_CMD.u32Register  |= 1;  // ����A��ͨ������ʹ��
    MOTOR_RIGHT_B_PHASE_TCPWM_TIMER->unTR_CMD.u32Register  |= 1;  // ����B��ͨ������ʹ��
    MOTOR_RIGHT_C_PHASE_TCPWM_TIMER->unTR_CMD.u32Register  |= 1;  // ����C��ͨ������ʹ��
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �Ҳ�������ͨ��ʹ��ѡ��
// ����˵��     a_channel       0���ر�A�����ͨ��  1������A�����ͨ��  
// ����˵��     b_channel       0���ر�B�����ͨ��  1������B�����ͨ��  
// ����˵��     c_channel       0���ر�C�����ͨ��  1������C�����ͨ��  
// ���ز���     void
// ʹ��ʾ��     motor_channel_set(1,0,1);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_right_channel_set(uint8 a_channel, uint8 b_channel, uint8 c_channel)
{     
    if(a_channel)                                                               // ��A��ͨ��ʹ������ͨ��
    {
        MOTOR_RIGHT_A_PHASE_TCPWM_TIMER->unCTRL.u32Register       |= 0x80000000;              // ʹ�ܶ�ʱ��
        MOTOR_RIGHT_A_PHASE_TCPWM_TIMER->unTR_CMD.u32Register      = 0x00000004;              // ��������
    }
    else                                                                        // ����ر�A��ͨ��ʹ��
    {
        MOTOR_RIGHT_A_PHASE_TCPWM_TIMER->unCTRL.u32Register       &= 0x7FFFFFFF;              // �ر�A��ͨ��ʹ��
    }   
    if(b_channel)                                                               // ��B��ͨ��ʹ������ͨ��
    {                                                                             
        MOTOR_RIGHT_B_PHASE_TCPWM_TIMER->unCTRL.u32Register        |= 0x80000000;              // ʹ�ܶ�ʱ�� 
        MOTOR_RIGHT_B_PHASE_TCPWM_TIMER->unTR_CMD.u32Register       = 0x00000004;              // �������� 
    }                                                                             
    else                                                                        // ����ر�B��ͨ��ʹ��
    {                                                                             
        MOTOR_RIGHT_B_PHASE_TCPWM_TIMER->unCTRL.u32Register        &= 0x7FFFFFFF;              // �ر�B��ͨ��ʹ�� 
    }
    if(c_channel)                                                               // ��C��ͨ��ʹ������ͨ��
    {                                                                               
        MOTOR_RIGHT_C_PHASE_TCPWM_TIMER->unCTRL.u32Register       |= 0x80000000;              // ʹ�ܶ�ʱ��  
        MOTOR_RIGHT_C_PHASE_TCPWM_TIMER->unTR_CMD.u32Register      = 0x00000004;              // ��������  
    }                                                                               
    else                                                                        // ����ر�C��ͨ��ʹ��
    {                                                                               
        MOTOR_RIGHT_C_PHASE_TCPWM_TIMER->unCTRL.u32Register       &= 0x7FFFFFFF;              // �ر�C��ͨ��ʹ��  
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �Ҳ�������MOS��Ԥ�����ܲ��� 
// ���ز���     void
// ʹ��ʾ��     motor_right_phase_check();
// ��ע��Ϣ     �ú�����ͨ�����Ʋ�ͬͨ����MOS��ʹ���������ͬƵ�ʵ����������ڲ���Ӳ�����ܣ����ú�������������ʼ��PWM��ʱ��ģ��  
//-------------------------------------------------------------------------------------------------------------------
void motor_right_phase_check(void)
{
    uint16 check_period;
    uint16 delay_time = 100;
    
    // ��һ��  A�����š�B������
    check_period = 36000;               // 2.222khz
      
    motor_right_output_init(check_period);      
    
    motor_right_channel_set(1,1,0);
    
    motor_right_duty_set(check_period / 50, 0, 0);
    
    system_delay_ms(delay_time);
    
    motor_right_duty_set(0, 0, 0);
    
    system_delay_ms(50);
    
    // �ڶ���  B�����š�C������
    check_period = 35000;               // 2.285khz
    
    motor_right_output_init(check_period);
    
    motor_right_channel_set(0,1,1);
    
    motor_right_duty_set(0, check_period / 50, 0);
    
    system_delay_ms(delay_time);
    
    motor_right_duty_set(0, 0, 0);
    
    system_delay_ms(50);
    
    // ������  C�����š�A������
    check_period = 34000;               // 2.352khz
    
    motor_right_output_init(check_period);
    
    motor_right_channel_set(1,0,1);
    
    motor_right_duty_set(0, 0, check_period / 50);
    
    system_delay_ms(delay_time);
    
    motor_right_duty_set(0, 0, 0);
    
    system_delay_ms(50);
    
    Cy_Tcpwm_Pwm_DeInit(MOTOR_RIGHT_A_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_Pwm_DeInit(MOTOR_RIGHT_B_PHASE_TCPWM_TIMER);
    Cy_Tcpwm_Pwm_DeInit(MOTOR_RIGHT_C_PHASE_TCPWM_TIMER);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ��� A���Լ�B������MOS �ر�B�������Լ�C��MOS A�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)
// ���ز���     void
// ʹ��ʾ��     left_mos_q1q4_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void left_mos_q1q4_open(uint16 duty)
{
    motor_left_channel_set(1, 1, 0);         
    motor_left_duty_set(duty, 0, 0);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ��� A���Լ�C������MOS �ر�C�������Լ�B��MOS A�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     left_mos_q1q6_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void left_mos_q1q6_open(uint16 duty)
{
    motor_left_channel_set(1, 0, 1);
    motor_left_duty_set(duty, 0, 0);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ��� B���Լ�A������MOS �ر�A�������Լ�C��MOS B�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     left_mos_q3q2_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void left_mos_q3q2_open(uint16 duty)
{
    motor_left_channel_set(1, 1, 0);
    motor_left_duty_set(0, duty, 0);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ��� B���Լ�C������MOS �ر�C�������Լ�A��MOS B�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     left_mos_q3q6_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void left_mos_q3q6_open(uint16 duty)
{
    motor_left_channel_set(0, 1, 1);
    motor_left_duty_set(0, duty, 0);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ��� C���Լ�A������MOS �ر�A�������Լ�B��MOS C�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     left_mos_q5q2_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void left_mos_q5q2_open(uint16 duty)
{
    motor_left_channel_set(1, 0, 1);
    motor_left_duty_set(0, 0, duty);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ��� C���Լ�B������MOS �ر�B�������Լ�A��MOS C�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     left_mos_q5q4_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void left_mos_q5q4_open(uint16 duty)
{
    motor_left_channel_set(0, 1, 1);
    motor_left_duty_set(0, 0, duty);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     �ر� ��� ����MOS
// ����˵��     void        
// ���ز���     void
// ʹ��ʾ��     left_mos_close();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void left_mos_close(void)
{
    motor_left_duty_set(0, 0, 0);
    motor_left_channel_set(1, 1, 1);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ���� �Ҳ� A���Լ�B������MOS �ر�B�������Լ�C��MOS A�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)
// ���ز���     void
// ʹ��ʾ��     right_mos_q1q4_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void right_mos_q1q4_open(uint16 duty)
{
    motor_right_channel_set(1, 1, 0);         
    motor_right_duty_set(duty, 0, 0);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� �Ҳ� A���Լ�C������MOS �ر�C�������Լ�B��MOS A�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     right_mos_q1q6_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void right_mos_q1q6_open(uint16 duty)
{
    motor_right_channel_set(1, 0, 1);
    motor_right_duty_set(duty, 0, 0);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� �Ҳ� B���Լ�A������MOS �ر�A�������Լ�C��MOS B�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     right_mos_q3q2_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void right_mos_q3q2_open(uint16 duty)
{
    motor_right_channel_set(1, 1, 0);
    motor_right_duty_set(0, duty, 0);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� �Ҳ� B���Լ�C������MOS �ر�C�������Լ�A��MOS B�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     right_mos_q3q6_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void right_mos_q3q6_open(uint16 duty)
{
    motor_right_channel_set(0, 1, 1);
    motor_right_duty_set(0, duty, 0);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� �Ҳ� C���Լ�A������MOS �ر�A�������Լ�B��MOS C�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     right_mos_q5q2_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void right_mos_q5q2_open(uint16 duty)
{
    motor_right_channel_set(1, 0, 1);
    motor_right_duty_set(0, 0, duty);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ���� �Ҳ� C���Լ�B������MOS �ر�B�������Լ�A��MOS C�����ռ�ձȲ���
// ����˵��     duty        ռ�ձ���Ϣ PWM_PRIOD_LOAD (motor.hͷ�ļ��к궨��)        
// ���ز���     void
// ʹ��ʾ��     right_mos_q5q4_open(200);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void right_mos_q5q4_open(uint16 duty)
{
    motor_right_channel_set(0, 1, 1);
    motor_right_duty_set(0, 0, duty);
}
//-------------------------------------------------------------------------------------------------------------------
// �������     �ر� �Ҳ� ����MOS
// ����˵��     void        
// ���ز���     void
// ʹ��ʾ��     right_mos_close();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void right_mos_close(void)
{
    motor_right_duty_set(0, 0, 0);
    motor_right_channel_set(1, 1, 1);
}

