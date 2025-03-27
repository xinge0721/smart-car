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
* �ļ�����          motor_driver_uart_control
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

#ifndef _motor_driver_uart_control_h_
#define _motor_driver_uart_control_h_


#include "zf_common_headfile.h"


#define MOTOR_DRIVER_UART      UART_2 
#define MOTOR_DRIVER_TX        UART2_RX_P07_0 
#define MOTOR_DRIVER_RX        UART2_TX_P07_1 

typedef enum
{
    NULL_CMD,
    SET_DUTY,
    GET_SPEED,
    SET_ZERO,
    TEST_PHASE,
    GET_PHASE,
    SET_PHASE,
    GET_ENCODER,
    GET_ANGLE,
    GET_PHASE_DUTY,
    GET_VOLTAGE,
    ERROR_CMD
}control_mode_enum;

typedef enum
{
    BYTE_TYPE,
    STRING_TYPE
}control_cmd_type_enum;

typedef enum
{
    CMD_NULL            = 0,    // ������
    CMD_FORTHWITH       = 1,    // ��ʱ���� ������ɺ�������Ӧ
    CMD_LOOP            = 2,    // ѭ������ ���ڵ��õĲ�ѯ��Ӧ
}refresh_state_enum;

typedef struct
{
      uint8                     send_data_buffer[7];
      
      uint8                     select_motor;
      
      int16                     receive_left_phase;
      int16                     receive_left_duty_data;

      int16                     receive_right_phase;
      int16                     receive_right_duty_data;
      
      control_mode_enum         immediate_command;
      control_mode_enum         continue_command;
      
      refresh_state_enum        refresh_flag;
      
      
      control_cmd_type_enum     cmd_type;
}small_device_value_struct;



extern small_device_value_struct motor_value;

void motor_driver_control_callback(small_device_value_struct *device_value);

void motor_driver_control_loop(small_device_value_struct *device_value);

void motor_driver_set_duty(small_device_value_struct *device_value, int left_duty, int right_duty);

void motor_driver_send_speed(small_device_value_struct *device_value, int left_speed, int right_speed);

void motor_driver_uart_init(void);

#endif
