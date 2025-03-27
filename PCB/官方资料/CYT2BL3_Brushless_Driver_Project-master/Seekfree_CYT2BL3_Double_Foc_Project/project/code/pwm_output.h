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

#ifndef _PWM_OUTPUT_H_
#define _PWM_OUTPUT_H_

#include "zf_common_headfile.h"

#if MOTOR_DRIVER_MODE == FAST_FOC_MODE
#define FPWM                (uint16)(20000)           // PWMƵ��
#define PWM_PRIOD_LOAD      (uint16)(4000)            // PWM����װ��ֵ
#else
#define FPWM                (uint16)(40000)           // PWMƵ��
#define PWM_PRIOD_LOAD      (uint16)(2000)            // PWM����װ��ֵ
#endif

#define MOTOR_LEFT_A_PHASE_PORT_H          (GPIO_PRT14)                         // ����A�����ſ������Ŷ˿�
#define MOTOR_LEFT_A_PHASE_PIN_H           (0)                                  // ����A�����ſ������ź�
#define MOTOR_LEFT_A_PIN_HSIOM_H           (P14_0_TCPWM0_LINE48)                // ����A���������Ÿ��ù���

#define MOTOR_LEFT_A_PHASE_PORT_L          (GPIO_PRT14)                         // ����A�����ſ������Ŷ˿�
#define MOTOR_LEFT_A_PHASE_PIN_L           (1)                                  // ����A�����ſ������ź�
#define MOTOR_LEFT_A_PIN_HSIOM_L           (P14_1_TCPWM0_LINE_COMPL48)          // ����A���������Ÿ��ù���

#define MOTOR_LEFT_B_PHASE_PORT_H          (GPIO_PRT18)                         // ����B�����ſ������Ŷ˿�
#define MOTOR_LEFT_B_PHASE_PIN_H           (4)                                  // ����B�����ſ������ź�
#define MOTOR_LEFT_B_PIN_HSIOM_H           (P18_4_TCPWM0_LINE53)                // ����B���������Ÿ��ù���

#define MOTOR_LEFT_B_PHASE_PORT_L          (GPIO_PRT18)                         // ����B�����ſ������Ŷ˿�
#define MOTOR_LEFT_B_PHASE_PIN_L           (5)                                  // ����B�����ſ������ź�
#define MOTOR_LEFT_B_PIN_HSIOM_L           (P18_5_TCPWM0_LINE_COMPL53)          // ����B���������Ÿ��ù���

#define MOTOR_LEFT_C_PHASE_PORT_H          (GPIO_PRT18)                         // ����C�����ſ������Ŷ˿�
#define MOTOR_LEFT_C_PHASE_PIN_H           (6)                                  // ����C�����ſ������ź�
#define MOTOR_LEFT_C_PIN_HSIOM_H           (P18_6_TCPWM0_LINE51)                // ����C���������Ÿ��ù���

#define MOTOR_LEFT_C_PHASE_PORT_L          (GPIO_PRT18)                         // ����C�����ſ������Ŷ˿�
#define MOTOR_LEFT_C_PHASE_PIN_L           (7)                                  // ����C�����ſ������ź�
#define MOTOR_LEFT_C_PIN_HSIOM_L           (P18_7_TCPWM0_LINE_COMPL51)          // ����C���������Ÿ��ù���

#define MOTOR_LEFT_A_PHASE_TCPWM_TIMER     (TCPWM0_GRP0_CNT48)                  // ����A�ඨʱ��
#define MOTOR_LEFT_A_PHASE_TCPWM_CLOCK     (PCLK_TCPWM0_CLOCKS48)               // ����A�ඨʱ��ʱ��ͨ��
#define MOTOR_LEFT_A_PHASE_TCPWM_ADDR      (0x40381800)                         // ����A�ඨʱ��ͨ����ַ(�Ĵ�����ַ)

#define MOTOR_LEFT_B_PHASE_TCPWM_TIMER     (TCPWM0_GRP0_CNT53)                  // ����B�ඨʱ��
#define MOTOR_LEFT_B_PHASE_TCPWM_CLOCK     (PCLK_TCPWM0_CLOCKS53)               // ����B�ඨʱ��ʱ��ͨ��
#define MOTOR_LEFT_B_PHASE_TCPWM_ADDR      (0x40381A80)                         // ����B�ඨʱ��ͨ����ַ(�Ĵ�����ַ)

#define MOTOR_LEFT_C_PHASE_TCPWM_TIMER     (TCPWM0_GRP0_CNT51)                  // ����C�ඨʱ��
#define MOTOR_LEFT_C_PHASE_TCPWM_CLOCK     (PCLK_TCPWM0_CLOCKS51)               // ����C�ඨʱ��ʱ��ͨ��
#define MOTOR_LEFT_C_PHASE_TCPWM_ADDR      (0x40381980)                         // ����C�ඨʱ��ͨ����ַ(�Ĵ�����ַ)

#define MOTOR_LEFT_TCPWM_ISR_CHANNEL       (tcpwm_0_interrupts_48_IRQn)         // ��A�ඨʱ��ͨ�������ж���Ϊ��������ж�     


#define MOTOR_RIGHT_A_PHASE_PORT_H         (GPIO_PRT0)                          // �ҵ��A�����ſ������Ŷ˿�
#define MOTOR_RIGHT_A_PHASE_PIN_H          (2)                                  // �ҵ��A�����ſ������ź�
#define MOTOR_RIGHT_A_PIN_HSIOM_H          (P0_2_TCPWM0_LINE14)                 // �ҵ��A���������Ÿ��ù���
                                                                                
#define MOTOR_RIGHT_A_PHASE_PORT_L         (GPIO_PRT0)                          // �ҵ��A�����ſ������Ŷ˿�
#define MOTOR_RIGHT_A_PHASE_PIN_L          (3)                                  // �ҵ��A�����ſ������ź�
#define MOTOR_RIGHT_A_PIN_HSIOM_L          (P0_3_TCPWM0_LINE_COMPL14)           // �ҵ��A���������Ÿ��ù���
                                                                     
#define MOTOR_RIGHT_B_PHASE_PORT_H         (GPIO_PRT2)                          // �ҵ��B�����ſ������Ŷ˿�
#define MOTOR_RIGHT_B_PHASE_PIN_H          (0)                                  // �ҵ��B�����ſ������ź�
#define MOTOR_RIGHT_B_PIN_HSIOM_H          (P2_0_TCPWM0_LINE7)                  // �ҵ��B���������Ÿ��ù���
                              
#define MOTOR_RIGHT_B_PHASE_PORT_L         (GPIO_PRT2)                          // �ҵ��B�����ſ������Ŷ˿�
#define MOTOR_RIGHT_B_PHASE_PIN_L          (1)                                  // �ҵ��B�����ſ������ź�
#define MOTOR_RIGHT_B_PIN_HSIOM_L          (P2_1_TCPWM0_LINE_COMPL7)            // �ҵ��B���������Ÿ��ù���
                        
#define MOTOR_RIGHT_C_PHASE_PORT_H         (GPIO_PRT5)                          // �ҵ��C�����ſ������Ŷ˿�
#define MOTOR_RIGHT_C_PHASE_PIN_H          (0)                                  // �ҵ��C�����ſ������ź�
#define MOTOR_RIGHT_C_PIN_HSIOM_H          (P5_0_TCPWM0_LINE9)                  // �ҵ��C���������Ÿ��ù���
                     
#define MOTOR_RIGHT_C_PHASE_PORT_L         (GPIO_PRT5)                          // �ҵ��C�����ſ������Ŷ˿�
#define MOTOR_RIGHT_C_PHASE_PIN_L          (1)                                  // �ҵ��C�����ſ������ź�
#define MOTOR_RIGHT_C_PIN_HSIOM_L          (P5_1_TCPWM0_LINE_COMPL9)            // �ҵ��C���������Ÿ��ù���
                                                                                
#define MOTOR_RIGHT_A_PHASE_TCPWM_TIMER    (TCPWM0_GRP0_CNT14)                  // �ҵ��A�ඨʱ��
#define MOTOR_RIGHT_A_PHASE_TCPWM_CLOCK    (PCLK_TCPWM0_CLOCKS14)               // �ҵ��A�ඨʱ��ʱ��ͨ��
#define MOTOR_RIGHT_A_PHASE_TCPWM_ADDR     (0x40380700)                         // �ҵ��A�ඨʱ��ͨ����ַ(�Ĵ�����ַ)
                                                                                
#define MOTOR_RIGHT_B_PHASE_TCPWM_TIMER    (TCPWM0_GRP0_CNT7)                   // �ҵ��B�ඨʱ��
#define MOTOR_RIGHT_B_PHASE_TCPWM_CLOCK    (PCLK_TCPWM0_CLOCKS7)                // �ҵ��B�ඨʱ��ʱ��ͨ��
#define MOTOR_RIGHT_B_PHASE_TCPWM_ADDR     (0x40380380)                         // �ҵ��B�ඨʱ��ͨ����ַ(�Ĵ�����ַ)
                                                                                
#define MOTOR_RIGHT_C_PHASE_TCPWM_TIMER    (TCPWM0_GRP0_CNT9)                   // �ҵ��C�ඨʱ��
#define MOTOR_RIGHT_C_PHASE_TCPWM_CLOCK    (PCLK_TCPWM0_CLOCKS9)                // �ҵ��C�ඨʱ��ʱ��ͨ��
#define MOTOR_RIGHT_C_PHASE_TCPWM_ADDR     (0x40380480)                         // �ҵ��C�ඨʱ��ͨ����ַ(�Ĵ�����ַ)
                                                                                
#define MOTOR_RIGHT_TCPWM_ISR_CHANNEL      (tcpwm_0_interrupts_14_IRQn)         // ��A�ඨʱ��ͨ�������ж���Ϊ��������ж�        


void motor_left_phase_check     (void);
void motor_left_duty_set        (uint16 a_duty, uint16 b_duty, uint16 c_duty);
void motor_left_channel_set     (uint8 a_channel, uint8 b_channel, uint8 c_channel);
void motor_left_output_init     (uint16 timer_period);

void motor_right_phase_check    (void);
void motor_right_duty_set       (uint16 a_duty, uint16 b_duty, uint16 c_duty);
void motor_right_channel_set    (uint8 a_channel, uint8 b_channel, uint8 c_channel);
void motor_right_output_init    (uint16 timer_period);

void left_mos_q1q4_open         (uint16 duty);
void left_mos_q1q6_open         (uint16 duty);
void left_mos_q3q2_open         (uint16 duty);
void left_mos_q3q6_open         (uint16 duty);
void left_mos_q5q2_open         (uint16 duty);
void left_mos_q5q4_open         (uint16 duty);
void left_mos_close             (void);

void right_mos_q1q4_open        (uint16 duty);
void right_mos_q1q6_open        (uint16 duty);
void right_mos_q3q2_open        (uint16 duty);
void right_mos_q3q6_open        (uint16 duty);
void right_mos_q5q2_open        (uint16 duty);
void right_mos_q5q4_open        (uint16 duty);
void right_mos_close            (void);


#endif


