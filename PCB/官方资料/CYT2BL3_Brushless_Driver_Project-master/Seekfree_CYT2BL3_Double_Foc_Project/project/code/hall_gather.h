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
* �ļ�����          hall_gather
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

#ifndef _hall_gather_h_
#define _hall_gather_h_

#include "zf_common_headfile.h"


#define LEFT_MOTOR_HALL_A_PIN   P06_1           // ���� ���� A������
#define LEFT_MOTOR_HALL_B_PIN   P06_0           // ���� ���� B������
#define LEFT_MOTOR_HALL_C_PIN   P06_3           // ���� ���� C������

#define LEFT_MOTOR_COUNT_TIMER  TC_TIME2_CH0    // ���� ����ʹ�õĶ�ʱ��

#define LEFT_MOTOR_PIT_TIMER    PIT_CH20        // ���� ��ѯ�����ж�



#define RIGHT_MOTOR_HALL_A_PIN  P13_1           // �ҵ�� ���� A������
#define RIGHT_MOTOR_HALL_B_PIN  P13_0           // �ҵ�� ���� B������
#define RIGHT_MOTOR_HALL_C_PIN  P13_3           // �ҵ�� ���� C������

#define RIGHT_MOTOR_COUNT_TIMER TC_TIME2_CH1    // �ҵ�� ����ʹ�õĶ�ʱ��

#define RIGHT_MOTOR_PIT_TIMER   PIT_CH21        // �ҵ�� ��ѯ�����ж�



void motor_left_hall_callback(void);

void motor_right_hall_callback(void);

void hall_gather_init(void);










#endif
