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
// ����lora����ģ��
//      ģ��ܽ�            ��Ƭ���ܽ�
//      RX                  P07_0
//      TX                  P07_1
//      GND                 �����Դ�� GND
//      5V                  ���� 5V ��Դ

//================================�ر�ע��================================
// ���ڽ���ʱһ��Ҫ��GND �����޷�����ͨѶ
//================================�ر�ע��================================
//================================�ر�ע��================================
// ���ڽ���ʱһ��Ҫ��GND �����޷�����ͨѶ
//================================�ر�ע��================================
//================================�ر�ע��================================
// ���ڽ���ʱһ��Ҫ��GND �����޷�����ͨѶ
//================================�ر�ע��================================

// ***************************** ���̲���˵�� *****************************
// 1.���İ���¼��ɱ����̣�����ʹ�ú��İ���������������� USB-TTL ģ�飬�ڶϵ�������������
// 2.��LORA����ģ�����ӵ����壬�мǲ鿴�����Ƿ��Ӧ
// 2.���������������� USB-TTL ģ�����ӵ��ԣ�����ϵ�
// 3.������ʹ�ô������ִ򿪶�Ӧ�Ĵ��ڣ����ڲ�����Ϊ DEBUG_UART_BAUDRATE �궨�� Ĭ�� 115200�����İ尴�¸�λ����
// 4.��LORA����ģ����յ���Ӧ����ʱ���᷵����ͬ����Ϣ
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�

// **************************** �������� ****************************
#define LORA_UART_INDEX            (UART_2		  )             
#define LORA_UART_BUAD_RATE        (115200		  )
#define LORA_UART_TX_PIN           (UART2_RX_P07_0        )
#define LORA_UART_RX_PIN           (UART2_TX_P07_1        )


static	fifo_struct 	lora_uart_fifo;
static	uint8      		lora_uart_buffer[WIRELESS_UART_BUFFER_SIZE];
static	uint8       	lora_uart_data = 0;

uint8 data_buffer[32];
uint32 data_len;
void lora_communication_receive(void)
{
    if(uart_query_byte(LORA_UART_INDEX, &lora_uart_data))
    {
        fifo_write_buffer(&lora_uart_fifo, &lora_uart_data, 1);
    }
}

int main(void)
{
    clock_init(SYSTEM_CLOCK_160M); 	// ʱ�����ü�ϵͳ��ʼ��<��ر���>
    debug_info_init();                  // ���Դ�����Ϣ��ʼ��
    
    // �˴���д�û����� ���������ʼ�������
    
    set_wireless_type(WIRELESS_UART, lora_communication_receive);                               // ���ûص�����
    fifo_init(&lora_uart_fifo, FIFO_DATA_8BIT, lora_uart_buffer, WIRELESS_UART_BUFFER_SIZE);
    uart_init (LORA_UART_INDEX, LORA_UART_BUAD_RATE, LORA_UART_RX_PIN, LORA_UART_TX_PIN);       // ��ʼ��LORA����
    
    uart_rx_interrupt(LORA_UART_INDEX, 1);                                                      // �򿪴��ڽ����ж�    
    
    uart_write_byte(LORA_UART_INDEX, '\r');
    uart_write_byte(LORA_UART_INDEX, '\n');
    uart_write_string(LORA_UART_INDEX, "SEEKFREE wireless uart demo.\r\n");              // ��ʼ������ ���������Ϣ
    // �˴���д�û����� ���������ʼ�������
    while(true)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
		data_len = 32;
		fifo_read_buffer(&lora_uart_fifo, data_buffer, &data_len, FIFO_READ_AND_CLEAN);
        if(data_len != 0)                                                       // �յ�����Ϣ ��ȡ�����᷵��ʵ�ʶ�ȡ�������ݸ���
        {
            uart_write_buffer(LORA_UART_INDEX, data_buffer, data_len);                     // ���յ�����Ϣ���ͻ�ȥ
            memset(data_buffer, 0, 32);
            func_uint_to_str((char *)data_buffer, data_len);
            uart_write_string(LORA_UART_INDEX, "\r\ndata len:");                                 // ��ʾʵ���յ���������Ϣ
            uart_write_buffer(LORA_UART_INDEX, data_buffer, strlen((const char *)data_buffer));    // ��ʾ�յ������ݸ���
            uart_write_string(LORA_UART_INDEX, ".\r\n");
        }
        system_delay_ms(50);
      
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

// **************************** �������� ****************************
// **************************** ���̳�������˵�� ****************************
// ��������ʱ�밴�������������б���
// ����1������û������
//      �鿴�������ִ򿪵��Ƿ�����ȷ�Ĵ��ڣ����򿪵� COM ���Ƿ��Ӧ���ǵ������������� USB-TTL ģ��� COM ��
//      �����ʹ����ɿƼ� CMSIS-DAP �������������ӣ���ô������������Ƿ��ɶ��������İ崮�������Ƿ��Ѿ����ӣ��������߲鿴���İ�ԭ��ͼ�����ҵ�
//      �����ʹ�� USB-TTL ģ�����ӣ���ô��������Ƿ������Ƿ��ɶ���ģ�� TX �Ƿ����ӵĺ��İ�� RX��ģ�� RX �Ƿ����ӵĺ��İ�� TX
// ����2��������������
//      �鿴�����������õĲ������Ƿ����������һ�£������� zf_common_debug.h �ļ��� DEBUG_UART_BAUDRATE �궨��Ϊ debug uart ʹ�õĴ��ڲ�����