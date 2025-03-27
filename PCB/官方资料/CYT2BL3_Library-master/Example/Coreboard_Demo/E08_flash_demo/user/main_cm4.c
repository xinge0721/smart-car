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
* �ļ�����          main_cm4
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 9.40.1
* ����ƽ̨          CYT2BL3
* ��������          https://seekfree.taobao.com/
*
* �޸ļ�¼
* ����              ����                ��ע
* 2024-11-19       pudding            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"
// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������

// *************************** ����Ӳ������˵�� ***************************
// ʹ����ɿƼ� CMSIS-DAP ��������������
//      ֱ�ӽ���������ȷ�����ں��İ�ĵ������ؽӿڼ���
// ʹ�� USB-TTL ģ������
//      ģ��ܽ�            ��Ƭ���ܽ�
//      USB-TTL-RX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_TX_PIN �궨������� Ĭ�� P14_0
//      USB-TTL-TX          �鿴 zf_common_debug.h �ļ��� DEBUG_UART_RX_PIN �궨������� Ĭ�� P14_1
//      USB-TTL-GND         ���İ��Դ�� GND
//      USB-TTL-3V3         ���İ� 3V3 ��Դ


// *************************** ���̲���˵�� ***************************
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�ڶϵ�������������
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 3.������ʹ�ô������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 4.�����ڴ��������Ͽ������´�����Ϣ��
//      FLASH_SECTION_INDEX: 127, FLASH_PAGE_INDEX: 3, origin data is :
//      ...
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�
// **************************** �������� ****************************

#define FLASH_SECTION_INDEX       (0)                                 // �洢�����õ�����
#define FLASH_PAGE_INDEX          (0)                                // �洢�����õ�ҳ�� ������һ��ҳ��

int main(void)
{
    clock_init(SYSTEM_CLOCK_160M);      // ʱ�����ü�ϵͳ��ʼ��<��ر���>
    
    debug_init();                       // ���Դ��ڳ�ʼ��
    // �˴���д�û����� ���������ʼ�������
    
    flash_init();                                                               // ʹ��flashǰ�ȵ���flash��ʼ��
    
    flash_erase_page(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);                    // ������һҳ

    // ��ע�� ���ݻ�������ÿ��λ��ֻ�ܴ洢һ�����͵�����
    // ��ע�� ���ݻ�������ÿ��λ��ֻ�ܴ洢һ�����͵�����
    // ��ע�� ���ݻ�������ÿ��λ��ֻ�ܴ洢һ�����͵�����

    flash_buffer_clear();                                                       // ��ջ�����
    flash_union_buffer[0].float_type  = 3.1415926;                              // �򻺳����� 0 ��λ��д�� float  ����
    flash_union_buffer[1].uint32_type = 4294967294;                             // �򻺳����� 1 ��λ��д�� uint32 ����
    flash_union_buffer[2].int32_type  = -2147483648;                            // �򻺳����� 2 ��λ��д�� int32  ����
    flash_union_buffer[3].uint16_type = 65535;                                  // �򻺳����� 3 ��λ��д�� uint16 ����
    flash_union_buffer[4].int16_type  = -32768;                                 // �򻺳����� 4 ��λ��д�� int16  ����
    flash_union_buffer[5].uint8_type  = 255;                                    // �򻺳����� 5 ��λ��д�� uint8  ����
    flash_union_buffer[6].int8_type   = -128;                                   // �򻺳����� 6 ��λ��д�� int8   ����
    flash_write_page_from_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX, 7);     // ��ָ�� Flash ������ҳ��д�뻺��������

    printf("\r\n");
    flash_buffer_clear();                                                       // ��ջ�����
    printf("\r\n Flash data buffer default data is :");
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // ���������� 0 ��λ�õ������� float  ��ʽ���
    printf("\r\n uint32_type: %d", flash_union_buffer[1].uint32_type);          // ���������� 1 ��λ�õ������� uint32 ��ʽ���
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // ���������� 2 ��λ�õ������� int32  ��ʽ���
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // ���������� 3 ��λ�õ������� uint16 ��ʽ���
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // ���������� 4 ��λ�õ������� int16  ��ʽ���
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // ���������� 5 ��λ�õ������� uint8  ��ʽ���
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // ���������� 6 ��λ�õ������� int8   ��ʽ���
    
    system_delay_ms(200);
    
    printf("\r\n");
    flash_read_page_to_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX, 7);        // �����ݴ� flash ��ȡ��������
    printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, new data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
    printf("\r\n float_type : %f", flash_union_buffer[0].float_type);           // ���������� 0 ��λ�õ������� float  ��ʽ���
    printf("\r\n uint32_type: %d", flash_union_buffer[1].uint32_type);          // ���������� 1 ��λ�õ������� uint32 ��ʽ���
    printf("\r\n int32_type : %d", flash_union_buffer[2].int32_type);           // ���������� 2 ��λ�õ������� int32  ��ʽ���
    printf("\r\n uint16_type: %u", flash_union_buffer[3].uint16_type);          // ���������� 3 ��λ�õ������� uint16 ��ʽ���
    printf("\r\n int16_type : %d", flash_union_buffer[4].int16_type);           // ���������� 4 ��λ�õ������� int16  ��ʽ���
    printf("\r\n uint8_type : %u", flash_union_buffer[5].uint8_type);           // ���������� 5 ��λ�õ������� uint8  ��ʽ���
    printf("\r\n int8_type  : %d", flash_union_buffer[6].int8_type);            // ���������� 6 ��λ�õ������� int8   ��ʽ���
    
    
    // �˴���д�û����� ���������ʼ�������
    for(;;)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
        

      
      
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

// **************************** �������� ****************************

// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
// ����1������û������
//      �鿴�������ִ򿪵��Ƿ�����ȷ�Ĵ��ڣ����򿪵� COM ���Ƿ��Ӧ���ǵ������������� USB-TTL ģ��� COM ��
//      �����ʹ����ɿƼ� CMSIS-DAP �������������ӣ���ô������������Ƿ��ɶ��������İ崮�������Ƿ��Ѿ����ӣ��������߲鿴���İ�ԭ��ͼ�����ҵ�
//      �����ʹ�� USB-TTL ģ�����ӣ���ô��������Ƿ������Ƿ��ɶ���ģ�� TX �Ƿ����ӵĺ��İ�� RX��ģ�� RX �Ƿ����ӵĺ��İ�� TX
//      ���������鶼������������û��������ݣ��ͽ�����Կ����Ƿ������ԣ����������Ծ͸���������ҳ�볢�ԣ�������ɲ��У���ô��ϵ����֧��
// ����2��������������
//      �鿴�����������õĲ������Ƿ����������һ�£������� zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨��Ϊ debug uart ʹ�õĴ��ڲ�����
// ����3�����ݲ���
//      ����������ҳ�볢�ԣ�����������ɶ�������ȷ����ϵ����֧��
