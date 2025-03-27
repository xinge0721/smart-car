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
* �ļ�����          fast_foc
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

#ifndef _fast_foc_h_
#define _fast_foc_h_


#include "zf_common_headfile.h"

typedef struct 
{
    float       encoder_proportion;
    int32       encoder_pole_pairs;
    float       duty_proportion;
    
}fast_foc_calculate_struct;


typedef struct 
{
    fast_foc_calculate_struct calculate_value;
  
    int32 encoder_max_data;
    int32 duty_max_data;
    int32 motor_pole_pairs;
    int32 motor_zero_location;
    int32 motor_rotation_direction;
    
    uint16 ouput_duty[3];
}fast_foc_struct;


extern fast_foc_struct motor_left_foc_driver;

extern fast_foc_struct motor_right_foc_driver;



void fast_foc_calculate(fast_foc_struct *fast_foc_pointer, int32 now_encoder_data, float output_duty_max, int32 traction_angle);

void fast_foc_init(fast_foc_struct *fast_foc_pointer, int32 encoder_max_data, int32 duty_max_data, uint32 motor_pole_pairs, int32 zero_location, int32 rotation_direction);



#endif

