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

#include "motor_flash.h"

uint16 *motor_flash_pointer[] = MOTOR_FLASH_DATA;                                                // ���� flash ��дָ��

uint32 motor_flash_length = (sizeof(motor_flash_pointer) / sizeof(motor_flash_pointer[0]));     // ���� flash ʹ�ó���



//-------------------------------------------------------------------------------------------------------------------
// �������     ��� FLASH ���� ��ȡ
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_flash_read();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_flash_read(void)
{
    flash_read_page_to_buffer(MOTOR_FLASH_SECTOR, MOTOR_FLASH_PAGE, motor_flash_length);         // ��ȡ flash ҳ

    for(int i = 0; i < motor_flash_length; i ++)
    {
        *motor_flash_pointer[i] = flash_union_buffer[i].uint32_type;                             // ��ֵ����Ӧ�ı���
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� FLASH ���� д��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_flash_write();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_flash_write(void)
{
    for(int i = 0; i < motor_flash_length; i ++)
    {
        flash_union_buffer[i].uint32_type = *motor_flash_pointer[i];                             // ��ȡ flash ָ��ָ��ı���
    }

    flash_erase_page(MOTOR_FLASH_SECTOR, MOTOR_FLASH_PAGE);                                      // ���� flash ҳ

    flash_write_page_from_buffer(MOTOR_FLASH_SECTOR, MOTOR_FLASH_PAGE, motor_flash_length);      // д�� flash ҳ
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��� FLASH ������ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_flash_init();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_flash_init(void)
{    
    flash_init();
    
    // δ������������ֱ�Ӷ�ȡ �ᴥ��NOROOT�����߱��� �ÿ�Դ�������⴦�� ���Ῠ��
    motor_flash_read();                                                                          // ��ȡ flash
}










