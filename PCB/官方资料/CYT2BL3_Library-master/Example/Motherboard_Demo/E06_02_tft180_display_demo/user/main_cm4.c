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
//      ģ��ܽ�            ��Ƭ���ܽ�
//      SCL                 �鿴 zf_device_tft180.h �� TFT180_SCL_PIN �궨�� 
//      SDA                 �鿴 zf_device_tft180.h �� TFT180_SDA_PIN �궨�� 
//      RES                 �鿴 zf_device_tft180.h �� TFT180_RES_PIN �궨�� 
//      DC                  �鿴 zf_device_tft180.h �� TFT180_DC_PIN  �궨�� 
//      CS                  �鿴 zf_device_tft180.h �� TFT180_CS_PIN  �궨�� 
//      BL                  �鿴 zf_device_tft180.h �� TFT180_BL_PIN  �궨�� 
//      GND                 ���İ��Դ�� GND
//      3V3                 ���İ� 3V3 ��Դ



// *************************** ���̲���˵�� ***************************
// 1.���İ���¼������ ���������� 1.8��TFT ��ʾģ������������Ļ�ӿ������� ��ע�����Ŷ�Ӧ ��Ҫ���
// 2.��ع��� �ϵ�� 1.8��TFT ��Ļ���� ��ʾ�ַ����ָ������Ͳ���ͼ
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�


// **************************** �������� ****************************


int main(void)
{
    clock_init(SYSTEM_CLOCK_160M); 	// ʱ�����ü�ϵͳ��ʼ��<��ر���>
    debug_info_init();                  // ���Դ�����Ϣ��ʼ��
    
    // �˴���д�û����� ���������ʼ�������
    
    uint16_t data[128];
    int16_t data_index = 0;
    for( ; data_index < 64; data_index ++)
        data[data_index] = data_index;
    for(data_index = 64; data_index < 128; data_index ++)
        data[data_index] = 128 - data_index;

    tft180_set_dir(TFT180_PORTAIT);
    tft180_set_color(RGB565_RED, RGB565_BLACK);
    tft180_init();
    
    // �˴���д�û����� ���������ʼ�������
    while(true)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���

        tft180_clear();
        tft180_show_rgb565_image(4, 60, (const uint16 *)gImage_seekfree_logo, 240, 80, 120, 40, 0); // ��ʾһ��RGB565ɫ��ͼƬ ԭͼ240*80 ��ʾ240*80 ��λ��ǰ
        system_delay_ms(1500);

        tft180_full(RGB565_GRAY);
        tft180_show_string( 0,  16*0,   "SEEKFREE");                            // ��ʾ�ַ���
        tft180_show_chinese(0,  16*1,   16, (const uint8 *)chinese_test, 4, RGB565_BLUE);           // ��ʾ����

        // ��ʾ�� flaot ���� �����ʾ 8bit λ���� �����ʾ 6bit λС��
        tft180_show_float(  0,  16*2,   -13.141592,     1, 6);                  // ��ʾ float ���� 1bit ���� 6bit С�� Ӧ����ʾ -3.141592 �ܹ����� 9 ���ַ�����ʾռλ
        tft180_show_float(  0,  16*3,   13.141592,      8, 4);                  // ��ʾ float ���� 8bit ���� 4bit С�� Ӧ����ʾ 13.1415 �ܹ����� 14 ���ַ�����ʾռλ ������� 5 ���ַ��Ŀհ�ռλ

        tft180_show_int(    0,  16*4,   -127,           2);                     // ��ʾ int8 ����
        tft180_show_uint(   0,  16*5,   255,            4);                     // ��ʾ uint8 ����

        tft180_show_int(    0,  16*6,  -32768,          4);                     // ��ʾ int16 ����
        tft180_show_uint(   0,  16*7,  65535,           6);                     // ��ʾ uint16 ����

        tft180_show_int(    0,  16*8,  -2147483648,     8);                     // ��ʾ int32 ���� 8bit ���� Ӧ����ʾ -47483648
        tft180_show_uint(   0,  16*9,  4294967295,      8);                     // ��ʾ uint32 ���� 10bit ���� Ӧ����ʾ 4294967295

        system_delay_ms(1000);

        tft180_full(RGB565_GRAY);
        tft180_show_wave(32, 64, data, 128, 64,  64, 32);                       // ��ʾһ�����ǲ��� ���ο�� 128 �������ֵ 64 ��ʾ��� 64 ��ʾ���ֵ 32
        system_delay_ms(1000);
        tft180_full(RGB565_GRAY);
        tft180_show_wave( 0, 48, data, 128, 64, 128, 64);                       // ��ʾһ�����ǲ��� ���ο�� 128 �������ֵ 64 ��ʾ��� 128 ��ʾ���ֵ 64
        system_delay_ms(1000);

        // ʹ�û��ߺ��� �Ӷ��������ǻ�����
        tft180_clear();
        for(data_index = 0; data_index < 128; data_index += 10)
        {
            tft180_draw_line(0, 0, data_index, 160 - 1, RGB565_66CCFF);
            system_delay_ms(20);
        }
        tft180_draw_line(0, 0, 128 - 1, 160 - 1, RGB565_66CCFF);
        for(data_index = 150; data_index >= 0; data_index -= 10)
        {
            tft180_draw_line(0, 0, 128 - 1, data_index, RGB565_66CCFF);
            system_delay_ms(20);
        }

        tft180_draw_line(128 - 1, 0, 128 - 1, 160 - 1, RGB565_66CCFF);
        for(data_index = 120; data_index > 0; data_index -= 10)
        {
            tft180_draw_line(128 - 1, 0, data_index, 160 - 1, RGB565_66CCFF);
            system_delay_ms(20);
        }
        tft180_draw_line(128 - 1, 0, 0, 160 - 1, RGB565_66CCFF);
        for(data_index = 150; data_index >= 0; data_index -= 10)
        {
            tft180_draw_line(128 - 1, 0, 0, data_index, RGB565_66CCFF);
            system_delay_ms(20);
        }
        system_delay_ms(1000);

        tft180_full(RGB565_RED);
        system_delay_ms(500);
        tft180_full(RGB565_GREEN);
        system_delay_ms(500);
        tft180_full(RGB565_BLUE);
        system_delay_ms(500);
        tft180_full(RGB565_WHITE);
        system_delay_ms(500);
      
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}

// **************************** �������� ****************************
// *************************** ���̳�������˵�� ***************************
// ��������ʱ�밴�������������б���
// ����1����Ļ����ʾ
//      ���ʹ��������ԣ��������Ҫ�õ�ع��� �����Ļ�������ŵ�ѹ
//      �����Ļ�ǲ��ǲ��λ���� ������Ŷ�Ӧ��ϵ
//      �����Ӧ���Ŷ���ȷ ���һ���Ƿ������Ų��β��� ��Ҫ��ʾ����
//      �޷���ɲ��β�������һ��GPIO���̽���Ļ����IO��ʼ��ΪGPIO��ת��ƽ �����Ƿ��ܿ�
