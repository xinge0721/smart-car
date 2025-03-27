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
* �ļ�����          motor_flash
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

#ifndef _motor_flash_h_
#define _motor_flash_h_

#include "zf_common_headfile.h"


#define MOTOR_FLASH_SECTOR   (0)                 // ���� FLASH ����������

#define MOTOR_FLASH_PAGE     (11)                // ���� FLASH ������ҳ

// �û��Զ������  ��֧��64λ����
#define MOTOR_FLASH_DATA     {                                    \
        (uint16 *)&(motor_left.zero_location),                    \
        (uint16 *)&(motor_left.rotation_direction),               \
        (uint16 *)&(motor_left.pole_pairs),                       \
        (uint16 *)&(motor_right.zero_location),                   \
        (uint16 *)&(motor_right.rotation_direction),              \
        (uint16 *)&(motor_right.pole_pairs),                      \
}

extern uint32 motor_flash_length;                // ���� flash ʹ�ó���

void motor_flash_read    (void);                 // flash ��ȡ����

void motor_flash_write   (void);                 // flash �������

void motor_flash_init    (void);                 // flash ��ʼ�� 


#endif
