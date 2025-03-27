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
// ���� Wi-Fi ת����ģ��
//      ģ��ܽ�            ��Ƭ���ܽ�
//      RX                  �鿴 zf_device_wifi_uart.h �� WIFI_UART_RX_PINx �궨��    Ĭ�� P10_5
//      TX                  �鿴 zf_device_wifi_uart.h �� WIFI_UART_TX_PINx �궨��    Ĭ�� P10_6
//      RTS                 �鿴 zf_device_wifi_uart.h �� WIFI_UART_RTS_PINx �궨��   Ĭ�� P10_2
//      RST                 �鿴 zf_device_wifi_uart.h �� WIFI_UART_RST_PINx �궨��   Ĭ�� P11_6
//      VCC                 5V ��Դ
//      GND                 ��Դ��

// *************************** ����ʹ�ò���˵�� ***************************
//1.����Ӳ������˵�����Ӻ�ģ�飬ʹ�õ�Դ����(����������ᵼ��ģ���ѹ����)
//
//2.�鿴���������ӵ�wifi����¼wifi���ƣ����룬IP��ַ
//
//3.���·��Ĵ����������޸ĺ궨�壬WIFI_SSID_TESTΪwifi���ƣ�WIFI_PASSWORD_TESTΪwifi����
//
//4.��zf_device_wifi_uart.h���޸�WIFI_UART_TARGET_IP�궨�壬����Ϊwifi��IP��ַ
//
//5.�������̵���Ƭ���У��� ������� �����������Ĵ���
//
//6.���������֣�����ΪTCP Sever���񣬲�Զ�����ӵ�ģ���IP��ַ

// *************************** ���̲���˵�� ***************************
// 1.�����̻�ͨ�� Debug �������������Ϣ ����ؽӺõ��Դ����Ա��ȡ������Ϣ
//
// 2.���Ӻ�ģ��ͺ��İ�󣨾���ʹ��������������Ա��⹩�粻������⣩ ��¼������ ���¸�λ�����ʼ����
//
// 3.���ģ��δ��������ʼ�� ��ͨ�� DEBUG �������δ�ܳɹ���ʼ����ԭ�� ������᳢�����³�ʼ�� һ����������Ի�ɹ�
//
// 4.���һֱ�� Debug ����������� ����Ҫ��鱨������ ���鿴���ļ��·��ĳ��������б�����Ų�
//
// 5.����Ĭ�ϲ����� WIFI_UART_AUTO_CONNECT �궨�� ͨ�� main �����еĽӿڽ����������� �����Ҫ�̶����н������� ���Կ����ú궨��
//
// 6.��ģ���ʼ����ɺ��ͨ�� DEBUG ���������ǰģ�����Ҫ��Ϣ���̼��汾��IP��Ϣ��MAC��Ϣ��PORT��Ϣ
//
// 7.�������� TCP Client ���� ģ��ᱻ����Ϊ TCP Client ��Ҫ���ӵ��������ڵ� TCP Server ���ܽ���ͨ��
//   Ŀ�����ӵ� TCP Server �� IP ��˿�Ĭ��ʹ�� zf_device_wifi_uart.h �� WIFI_UART_TARGET_IP �� WIFI_UART_TARGET_PORT ����
//   ʵ�ʲ�����Ҫ�����ֳ� TCP Server ��ʵ�� IP ��ַ��˿�����
//
// 8.�������豸�������ӵ� TCP Server ���������ʹ������������ֽ��� TCP Server ģʽ Ȼ�󱾻����ӵ����Ե� IP ��˿ڣ�
//   �����̻������� Server ����һ�β������� ������յ����ݺ���� Debug ���������Ϣ�Լ���ǰ������Ϣ ���������������ͻ�ȥ
//
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�


// **************************** �������� ****************************
#define WIFI_SSID_TEST          "WIFI_TEST"
#define WIFI_PASSWORD_TEST      "SEEKFREE"

uint8 wifi_uart_test_buffer[] = "this is wifi uart test buffer";
uint8 wifi_uart_get_data_buffer[256];
uint16 data_length;

int main(void)
{
    clock_init(SYSTEM_CLOCK_160M); 	// ʱ�����ü�ϵͳ��ʼ��<��ر���>
    debug_info_init();                  // ���Դ�����Ϣ��ʼ��
    
    // �˴���д�û����� ���������ʼ�������

    printf("\r\n Wi-Fi UART init.");

    // ��ǰʹ�õ��� WIFI ����ģ��� station ģʽ ������������·���� WIFI
    //
    // �������ݷ�ʽ����ʹ�������(Ĭ��) Ҳ����ʹ��͸������ ������ wifi_uart_init �������޸� <��ģ����Ϊ������ʱ ֻ��ʹ�����ʽ��������>
    while(wifi_uart_init(WIFI_SSID_TEST, WIFI_PASSWORD_TEST, WIFI_UART_STATION))
    {
        system_delay_ms(500);                                                   // ��ʼ��ʧ�� �ȴ� 500ms
    }

    // zf_device_wifi_uart.h �ļ��ڵĺ궨����Ը���ģ������(����) WIFI ֮���Ƿ��Զ����� TCP ������������ UDP ���ӡ����� TCP �������Ȳ���
    if(1 != WIFI_UART_AUTO_CONNECT)                                             // ���û�п����Զ����� ����Ҫ�ֶ�����Ŀ�� IP
    {
        while(wifi_uart_connect_tcp_servers(                                    // ��ָ��Ŀ�� IP �� TCP Server �˿ڽ��� TCP ����
            WIFI_UART_TARGET_IP,                                                // ����ʹ�����Զ�����ʱһ����Ŀ�� IP ʵ��ʹ��ʱҲ����ֱ����дĿ�� IP �ַ���
            WIFI_UART_TARGET_PORT,                                              // ����ʹ�����Զ�����ʱһ����Ŀ��˿� ʵ��ʹ��ʱҲ����ֱ����дĿ��˿��ַ���
            WIFI_UART_COMMAND))                                                 // ���������ģʽ ��Ȼ����Ըĳ�͸��ģʽ ʵ���ϲ�𲢲��Ǻܴ�
        {
            // ���һֱ����ʧ�� ����һ���ǲ���û�н�Ӳ����λ
            printf("\r\n Connect TCP Servers error, try again.");
            system_delay_ms(500);                                               // ��������ʧ�� �ȴ� 500ms
        }
    }

    printf("\r\nmodule version:%s", wifi_uart_information.wifi_uart_version);   // ģ��̼��汾
    printf("\r\nmodule mac    :%s", wifi_uart_information.wifi_uart_mac);       // ģ�� MAC ��Ϣ
    printf("\r\nmodule ip     :%s", wifi_uart_information.wifi_uart_local_ip);  // ģ�� IP ��ַ
    printf("\r\nmodule port   :%s", wifi_uart_information.wifi_uart_local_port);// ģ�� PORT ��Ϣ

    // ���Ͳ���������������
    data_length = (uint16)wifi_uart_send_buffer(wifi_uart_test_buffer, sizeof(wifi_uart_test_buffer));
    if(!data_length)
    {
        printf("\r\n send success.");
    }
    else
    {
        printf("\r\n %d bytes data send failed.", data_length);
    }

    // �˴���д�û����� ���������ʼ�������
    while(true)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���

        data_length = (uint16)wifi_uart_read_buffer(wifi_uart_get_data_buffer, sizeof(wifi_uart_get_data_buffer));

        if(data_length)                                                         // ������յ����� ��������������ж�
        {
            if(strstr((char *)wifi_uart_get_data_buffer, "+IPD"))               // �ж����ݸ�ʽ�Ƿ���ͨ�����緢�͹���������
            {
                printf("\r\n Get data: <%s>.", wifi_uart_get_data_buffer);
                if(!wifi_uart_send_buffer(wifi_uart_get_data_buffer, data_length))
                {
                    printf("\r\n send success.");
                    memset(wifi_uart_get_data_buffer, 0, data_length);          // ���ݷ������ �������
                }
                else
                {
                    printf("\r\n %d bytes data send failed.", data_length);
                }
            }
        }
        system_delay_ms(100);


        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

// **************************** �������� ****************************
// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
//
// ����1������û������
//      �鿴 ������� �򿪵��Ƿ�����ȷ�Ĵ��� ���򿪵� COM ���Ƿ��Ӧ���� Debug UART(USB ת TTL ���� ����������) �� COM ��
//
// ����2��������������
//      �鿴 ������� ʹ�õĲ������Ƿ��� zf_common_debug.h �� DEBUG_UART_BAUDRATE �궨���һ�� Ĭ���� 115200
//
// ����3��һֱ��ʾ reset failed ��Ϣ
//      Ĭ��ʹ��Ӳ�����Ÿ�λ ���û�н� WIFI_UART_RST_PIN ��Ӧ�ĸ�λ���� ����Ҫ���ϸ�λ���� �����޸� WIFI_UART_HARDWARE_RST Ϊ����
//
// ����4��һֱ��ʾ Connect UDP Client error, try again. ��Ϣ
//      ���Ĭ��ʹ�õ� UDP Client IP ��ַ��zf_device_wifi_uart.h �� WIFI_UART_TARGET_IP���Ƿ������ʹ�õ� UDP Client IP һ��
//      ���Ĭ��ʹ�õ� UDP Client ͨ�Ŷ˿ڣ�zf_device_wifi_uart.h �� WIFI_UART_TARGET_PORT���Ƿ������ʹ�õ� UDP Client ͨ�Ŷ˿�һ��
//
// ����5��һֱ��ʾ wifi set failed ���� get module information failed ��Ϣ
//      �� WIFI_SSID_TEST �궨���޸�Ϊ�����ʹ�õ� Wi-Fi ����
//      �� WIFI_PASSWORD_TEST �궨���޸�Ϊ�����ʹ�õ� Wi-Fi ����