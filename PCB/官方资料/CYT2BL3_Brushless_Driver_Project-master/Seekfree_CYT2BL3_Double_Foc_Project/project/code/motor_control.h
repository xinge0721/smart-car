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
* �ļ�����          motor_control
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

#ifndef _motor_control_h_
#define _motor_control_h_


#include "zf_common_headfile.h"


#define ENCODER_PRECISION               (32767)                 // �������������ֵ  32767
#define OUTPUT_DUTY_MAX                 (PWM_PRIOD_LOAD)        // ռ�ձ�������ֵ

typedef enum
{
    LEFT_MOTOR  = 0,                            // �����
    RIGHT_MOTOR = 1,                            // �Ҳ���
}motor_type_enum;

typedef enum
{
    REVERSE = -1,                               // ��ת
    FORWARD = 1,                                // ��ת
}motor_dir_enum;

typedef enum
{
    RROTECT_MODE,                               // �������ģʽ(�ű��ֵ���󡢵�ص�ѹ����)
    NORMAL_RUN_MODE,                            // �����������ģʽ
}motor_protect_enum;


typedef enum
{
    MOTOR_STOP,                                 // ���δ����
    MOTOR_RUN,                                  // �����������
}motor_run_state_enum;

typedef enum
{
    ENCODER_ERROR,                              // �ű�������ֵ����
    ENCODER_NORMAL,                             // �ű�������������
}magnetic_encoder_state_enum;

typedef enum
{
    BATTERY_HEALTH,                             // ��ص�ѹ����    
    BATTERY_WARNING,                            // ��ص�ѹ����
    BATTERY_ERROR                               // ��ص�ѹ�쳣
}battery_state_enum;

typedef struct
{         
    motor_run_state_enum                run_state;                  // �������״̬
        
    float                               motor_duty;                 // �����ǰռ�ձ�  0 ~ 1 
        
    int16                               zero_location;              // ������λ��
    int16                               rotation_direction;         // �ű�����λ�������
    int16                               pole_pairs;                 // ���������
        
    motor_dir_enum                      motor_set_dir;              // �����ǰ���÷���        
    motor_dir_enum                      motor_now_dir;              // �����ǰ��ת����
    motor_dir_enum                      motor_menc15a_dir;          // �����ű�����ƥ�䷽��
        
    float                              motor_speed;                // �����ǰת��            ת�ٵ�λ��RPM   
    float                              motor_speed_filter;         // �����ǰת��(�˲�)      ת�ٵ�λ��RPM   
        
    int8                                hall_value_now;             // ��ǰ����ֵ
    int8                                hall_value_last;            // ��һ�λ���ֵ
        
    int32                               menc15a_value_now;          // �ű�������ǰ�ɼ�ֵ              
    int32                               menc15a_value_offset;       // �ű�������ǰ����ƫ��ֵ          
    int32                               menc15a_offset_integral;    // �ű�����ƫ��ֵ����
        
    uint8                               motor_control_angle;        // ������ƽǶ� ��Χ��60 - 180 �Ƕ�Խ�� ת��Խ�� ����ԽС
        
    float                               battery_voltage;            // ��ص�ǰ��ѹ
    battery_state_enum                  battery_state;              // ��ص�ǰ״̬
        
    motor_protect_enum                  motor_protect_state;        // �������ģʽ    
    magnetic_encoder_state_enum         encoder_state;              // �ű�����״̬    
    
    int32                               single_calculation_use_time;// ������μ����ʱ       
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