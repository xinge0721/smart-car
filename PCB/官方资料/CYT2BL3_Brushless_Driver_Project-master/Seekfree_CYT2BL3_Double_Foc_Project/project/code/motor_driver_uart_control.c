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

#include "motor_driver_uart_control.h"

small_device_value_struct motor_value;

fifo_struct     motor_driver_fifo;              // ����ͨѶ�� FIFO �ṹ��

uint8           driver_fifo_buffer[128];        // FIFO ָ��Ļ�������

uint8           read_buffer[128];               // ����ʱ����ȡ���ݵĻ�������

int16           receive_enter_flag = 0;         // �س���־λ


//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͨѶ FIFO ����ָ�����ȵ�����
// ����˵��     clear_length        Ҫ�����ĳ���
// ���ز���     void
// ʹ��ʾ��     motor_driver_fifo_clear(1); 
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_driver_fifo_clear(uint32 clear_length)
{
    fifo_read_buffer(&motor_driver_fifo, read_buffer, &clear_length, FIFO_READ_AND_CLEAN);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͨѶ ���ݰ���������
// ����˵��     device_value        ͨѶ�����ṹ��
// ����˵��     statement_buffer    һ��������
// ���ز���     void
// ʹ��ʾ��     motor_driver_control_loop(&motor_value, read_buffer); 
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_driver_parse_statement(small_device_value_struct *device_value, uint8 *statement_buffer)
{
    if(BYTE_TYPE == device_value->cmd_type)                                     // �жϴ��������������Ƿ�Ϊ �ֽ�ͨѶ ����
    {
        switch(statement_buffer[1])                                             // �ж� �ֽ�ͨѶ �Ĺ����� 
        {
            case 0x01:{                                                         // ������ 0x01 ����ռ�ձ�
  
                device_value->receive_left_duty_data   = (((int)statement_buffer[2] << 8) | (int)statement_buffer[3]);  // �����ռ�ձ����
                
                device_value->receive_right_duty_data  = (((int)statement_buffer[4] << 8) | (int)statement_buffer[5]);  // �Ҳ���ռ�ձ����
                
                device_value->immediate_command        = SET_DUTY;              // ��ʱָ��(����Ӧһ��)״̬����Ϊ SET_DUTY 
                
                device_value->refresh_flag             = CMD_FORTHWITH;         // ��ʱָ��ˢ�±�־λ����  ��Ҫ����ִ������
            }break;
            
            case 0x02:{                                                         // ������ 0x02 ��ȡ���ٶ���Ϣ
              
                device_value->continue_command         = GET_SPEED;             // ����ָ��(���ڳ������)״̬����Ϊ GET_SPEED 
                
            }break;
            
            case 0x03:{                                                         // ������ 0x03 �Խ������
              
                device_value->immediate_command        = SET_ZERO;              // ��ʱָ��(����Ӧһ��)״̬����Ϊ SET_ZERO 
                
                device_value->refresh_flag             = CMD_LOOP;              // ��ʱָ��ˢ�±�־λ����  ��������ִ��
            }break;
            
            default:break;
        }
    }
    else if(STRING_TYPE == device_value->cmd_type)                              // �жϴ��������������Ƿ�Ϊ �ַ�ͨѶ ����
    {
        char *location1 = NULL;                                                 // ��������λ��ָ�� ���ڽ�������
        char *location2 = NULL;
        
        char data_string[10];                                                   // ����һ���������� ���� �ַ��� ת ����
        
        if(statement_buffer[0] == 'S')                                          // �ж� �ַ� ָ������ַ��Ƿ�Ϊ 'S'
        {
            if(strstr((const char *)statement_buffer, "SET-DUTY"))              // ���� �������������Ƿ��� "SET-DUTY" �ؼ���  
            {                                                                   // SET-DUTYָ���ʽΪ��"SET-DUTY,num_1,num_2\r\n" ���� num_1 Ϊ�����ռ�ձȣ� num_2 Ϊ�Ҳ���ռ�ձ� ��Χ���� -10000 ~ 10000
              
                location1 = strchr((char *)statement_buffer, ',');              // ������һ�����ŵ�λ�� 
                
                if(location1 != 0x00)                                           // ����ɹ������� �����  ����Ĭ�Ͻ�ռ�ձ�����Ϊ 0
                {
                    location1 ++;                                               // λ������ Խ����һ������
                    
                    location2 = strchr(location1, ',');                         // �����ڶ������ŵ�λ��
                    
                    if(location2 != 0x00)                                       // ����ɹ������� �����
                    {
                        memset(data_string, 0x00, 10);                          // ��ջ�������
                      
                        memcpy(data_string, location1, location2 - location1);  // ȡ����������֮�������
                        
                        device_value->receive_left_duty_data = func_str_to_int(data_string);    // ���ַ�������תΪ���� ��һ������Ϊ�����ռ�ձ�
                        
                        device_value->receive_left_duty_data = func_limit_ab(device_value->receive_left_duty_data, -10000, 10000);  // �����޷�
                        
                        location2 ++;                                           // λ������ Խ���ڶ�������
                        
                        location1 = strchr(location2, '\n');                    // �����س���λ��
                        
                        memset(data_string, 0x00, 10);                          // ��ջ�������
                        
                        memcpy(data_string, location2, location1 - location2);  // ȡ���ڶ������ŵ��س�֮�������
                        
                        device_value->receive_right_duty_data = func_str_to_int(data_string);   // ���ַ�������תΪ���� �ڶ�������Ϊ�Ҳ���ռ�ձ�
                        
                        device_value->receive_right_duty_data = func_limit_ab(device_value->receive_right_duty_data, -10000, 10000);  // �����޷�
                    }                                                                  
                    else                                                        // δ�������ڶ������� �������س� ��һ������ �ɽ������ռ�ձ�
                    {
                        location2 = strchr(location1, '\n');                    // �����س���λ��
                        
                        memset(data_string, 0x00, 10);                          // ��ջ�������
                                                                                
                        memcpy(data_string, location1, location2 - location1);  // ȡ����һ�����ŵ��س�֮�������
                        
                        device_value->receive_left_duty_data = func_str_to_int(data_string);    // ���ַ�������תΪ���� ��һ������Ϊ�����ռ�ձ�
                        
                        device_value->receive_left_duty_data = func_limit_ab(device_value->receive_left_duty_data, -10000, 10000);  // �����޷�
                      
                        device_value->receive_right_duty_data = 0;              // û�еڶ������� �Ҳ�ռ�ձ����ݽ���ʧ�� ����ռ�ձ�Ϊ 0 
                    }
                    
                }
                else
                {
                    device_value->receive_left_duty_data  = 0;                  // û�ж��� ����ָ������쳣 ����ռ�ձ�Ϊ 0 
                    
                    device_value->receive_right_duty_data = 0;                  // û�ж��� ����ָ������쳣 ����ռ�ձ�Ϊ 0 
                }
                
                device_value->immediate_command        = SET_DUTY;              // ��ʱָ��(����Ӧһ��)״̬����Ϊ SET_DUTY 
                        
                device_value->refresh_flag             = CMD_FORTHWITH;         // ��ʱָ��ˢ�±�־λ����  ��Ҫ����ִ������
            }
            else if(strstr((const char *)statement_buffer, "SET-ZERO"))        // ���� �������������Ƿ��� "SET-ZERO" �ؼ���
            {   
                device_value->immediate_command        = SET_ZERO;              // ��ʱָ��(����Ӧһ��)״̬����Ϊ SET_ZERO 
                
                device_value->refresh_flag             = CMD_LOOP;              // ��ʱָ��ˢ�±�־λ����  ��������ִ������
            } 
            else if(strstr((const char *)statement_buffer, "SET-PHASE"))       // ���� �������������Ƿ��� "SET-PHASE" �ؼ���
            {
                device_value->refresh_flag             = CMD_LOOP;              // ��ʱָ��ˢ�±�־λ����  ��������ִ������
            }
            else if(strstr((const char *)statement_buffer, "STOP-SEND"))       // ���� �������������Ƿ��� "STOP-SEND" �ؼ���
            {
                device_value->continue_command         = NULL_CMD;              // ����ָ��(���ڳ������)״̬����Ϊ NULL_CMD 
            } 
            else                                                                // ��ǰָ���Э��ָ�� �����ʾ error cmd
            {
                device_value->immediate_command        = ERROR_CMD;             // ��ʱָ��(����Ӧһ��)״̬����Ϊ ERROR_CMD 
                
                device_value->refresh_flag             = CMD_LOOP;              // ��ʱָ��ˢ�±�־λ����  ��������ִ������
            }
        }
        else if(statement_buffer[0] == 'G')                                    // �ж� �ַ� ָ������ַ��Ƿ�Ϊ 'G'
        {
            if(strstr((const char *)statement_buffer, "GET-SPEED"))            // ���� �������������Ƿ��� "GET-SPEED" �ؼ���
            {
                device_value->continue_command         = GET_SPEED;             // ����ָ��(���ڳ������)״̬����Ϊ GET_SPEED 
            } 

            else if(strstr((const char *)statement_buffer, "GET-PHASE-DUTY"))  // ���� �������������Ƿ��� "GET-PHASE-DUTY" �ؼ���
            {                                                                   // GET-PHASE-DUTYָ���ʽΪ��"GET-PHASE-DUTY,num\r\n" ���� num Ϊѡ��ĵ���� 0 Ϊ�����  1Ϊ�Ҳ��� ���� Ϊ���һ����л�
              
                location1 = strchr((char *)statement_buffer, ',');              // ������һ�����ŵ�λ�� 
                
                if(location1 != 0x00)                                           // ����ɹ������� �����  ����Ĭ�� ���ҵ�� �����л�
                {
                    location1 ++;                                               // λ������ Խ����һ������
                    
                    location2 = strchr(location1, '\n');                        // �����س���λ��
                    
                    memset(data_string, 0x00, 10);                              // ��ջ�������
                                                                                
                    memcpy(data_string, location2, location2 - location1);      // ȡ����һ�����ŵ��س�֮�������
                    
                    device_value->select_motor = func_str_to_int(data_string);  // ���ַ�������תΪ���� ��һ������Ϊ�����ռ�ձ�
                    
                    if(device_value->select_motor != LEFT_MOTOR)                // �����޷� ��ֹ�û������쳣����  �������ͽ���ѡ�������(O) �����Ҳ���(1)
                    {
                        device_value->select_motor = RIGHT_MOTOR;               
                    }
                }
                else
                {
                    if(device_value->select_motor == LEFT_MOTOR)                // �жϵ�ǰѡ��ĵ������ �����л�������һ����� 
                    {
                        device_value->select_motor = RIGHT_MOTOR;
                    }
                    else
                    {
                        device_value->select_motor = LEFT_MOTOR;
                    }
                }
                device_value->continue_command         = GET_PHASE_DUTY;        // ����ָ��(���ڳ������)״̬����Ϊ GET_PHASE_DUTY 
            } 
            else if(strstr((const char *)statement_buffer, "GET-ENCODER"))     // ���� �������������Ƿ��� "GET-ENCODER" �ؼ���
            {
                device_value->continue_command         = GET_ENCODER;           // ����ָ��(���ڳ������)״̬����Ϊ GET_ENCODER 
            }
            else if(strstr((const char *)statement_buffer, "GET-ANGLE"))       // ���� �������������Ƿ��� "GET-ANGLE" �ؼ���
            {
                device_value->continue_command         = GET_ANGLE;             // ����ָ��(���ڳ������)״̬����Ϊ GET_ANGLE 
            }  
            else if(strstr((const char *)statement_buffer, "GET-VOLTAGE"))     // ���� �������������Ƿ��� "GET-VOLTAGE" �ؼ���
            {
                device_value->continue_command         = GET_VOLTAGE;           // ����ָ��(���ڳ������)״̬����Ϊ GET_VOLTAGE 
            }  
            else                                                                // ��ǰָ���Э��ָ�� �����ʾ error cmd
            {   
                device_value->immediate_command        = ERROR_CMD;             // ��ʱָ��(����Ӧһ��)״̬����Ϊ ERROR_CMD 
                
                device_value->refresh_flag             = CMD_LOOP;              // ��ʱָ��ˢ�±�־λ����  ��������ִ������
            }                                                                   
        }
        else if(statement_buffer[0] == 'T')                                     // �ж� �ַ� ָ������ַ��Ƿ�Ϊ 'T'
        {
            if(strstr((const char *)statement_buffer, "TEST-PHASE"))           // ���� �������������Ƿ��� "TEST-PHASE" �ؼ���
            {
                device_value->refresh_flag             = CMD_LOOP;              // ��ʱָ��ˢ�±�־λ����  ��������ִ������
            } 
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͨѶ���� ѭ���������� 
// ����˵��     device_value        ͨѶ�����ṹ��
// ���ز���     void
// ʹ��ʾ��     motor_driver_control_loop(&motor_value); 
// ��ע��Ϣ     �ɷ����ڴ��ڽ����жϡ�PIT�����жϡ���ѭ��  
//-------------------------------------------------------------------------------------------------------------------
void motor_driver_control_loop(small_device_value_struct *device_value)
{    
    uint32 read_length = 0;                                                     // �����ȡ���ȱ���
    
    uint8  check_data = 0;                                                      // ��������У�����
  
    if(fifo_used(&motor_driver_fifo) >= 7)                                      // �ж� FIFO �����������Ƿ����7
    {
        fifo_read_element(&motor_driver_fifo, &read_buffer[0], FIFO_READ_ONLY); // ����ȡ��һ������
        
        if(read_buffer[0] == 0XA5)                                              // �ж��Ƿ�Ϊ֡ͷ �������ֽ�ͨѶ��֡ͷ ���ж��Ƿ�Ϊ�ַ���ͨѶ
        {
            read_length = 7;                                                    // �ɹ��жϵ�֡ͷ ����ȡһ������(����Ϊ7λ)
            
            fifo_read_buffer(&motor_driver_fifo, read_buffer, &read_length, FIFO_READ_ONLY);
            
            for(int i = 0; i < 6; i ++)                                         // ��У�����
            {
                check_data += read_buffer[i];
            }
            if(check_data == read_buffer[6])                                    // �жϺ�У��
            {
                read_length = 7;                                                // �ɹ�ͨ����У�� �� FIFO ��ȡ������ һ������(����Ϊ7λ)
                
                fifo_read_buffer(&motor_driver_fifo, read_buffer, &read_length, FIFO_READ_AND_CLEAN);
                
                device_value->cmd_type = BYTE_TYPE;                             // ����ͨѶ����Ϊ �ֽ�ͨѶ
                
                motor_driver_parse_statement(device_value, read_buffer);        // �������ݽ���      
            }
            else
            {
                motor_driver_fifo_clear(1);                                     // ��У��δͨ�� ���һ�����������ݣ�״̬�����ƣ�
            }
        }
        else if(read_buffer[0] == 'S' || read_buffer[0] == 'G'|| read_buffer[0] == 'T')         // �ж��Ƿ�Ϊ�ַ���ͨѶ�� ����ĸ
        {
            if(receive_enter_flag == 1)                                         // �ж��Ƿ��յ� �س� �ַ�
            {
                receive_enter_flag = 0;                                         // ��� �س� �ַ���־λ
                
                read_length = fifo_used(&motor_driver_fifo);                    // ��ȡ���� FIFO �е��ַ��ܳ���
                
                fifo_read_buffer(&motor_driver_fifo, read_buffer, &read_length, FIFO_READ_ONLY);        // ���������� ����ȡ ����
                
                for(int i = 0; i < read_length; i ++)                           // ���� �س� �ַ�λ�� 
                {
                    if(read_buffer[i] == '\n')                                  // �ж��Ƿ�Ϊ �س�
                    {
                        read_length = i + 1;                                    // ��ȡ�� �س���λ��    
                        
                        memset(read_buffer, 0x00, 128);                         // ��յ�ǰ����������
                        
                        fifo_read_buffer(&motor_driver_fifo, read_buffer, &read_length, FIFO_READ_AND_CLEAN);   // �� �س� ֮ǰ�������ַ��� FIFO ��������ȡ���Ҳ���
                        
                        break;                                                  // ����ѭ��
                    }   
                }
                
                device_value->cmd_type = STRING_TYPE;                           // ����ͨѶ����Ϊ �ַ�ͨѶ
                
                motor_driver_parse_statement(device_value, read_buffer);        // �������ݽ���      
            }
        }
        else
        {
            motor_driver_fifo_clear(1);                                         // �ֽڰ�ͨѶ���ַ���ͨѶЭ�� �������� ���һ�����������ݣ�״̬�����ƣ�
        }
    }
    
    driver_cmd_forthwith();
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ����ռ�ձ���Ϣ  �ֽڰ�����
// ����˵��     device_value        ͨѶ�����ṹ��
// ����˵��     left_speed          �����ռ�ձ�
// ����˵��     right_speed         �Ҳ���ռ�ձ�
// ���ز���     void
// ʹ��ʾ��     motor_driver_set_duty(&motor_value, 500, 500);   // �ֽڰ�ͨѶ����Э������� ռ�ձȷ�Χ -10000 ~ 10000
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_driver_set_duty(small_device_value_struct *device_value, int left_duty, int right_duty)
{
    device_value->send_data_buffer[0] = 0xA5;
    device_value->send_data_buffer[1] = 0X01;
    device_value->send_data_buffer[2] = (uint8)((left_duty  & 0xFF00) >> 8);
    device_value->send_data_buffer[3] = (uint8)( left_duty  & 0x00FF);
    device_value->send_data_buffer[4] = (uint8)((right_duty & 0xFF00) >> 8);
    device_value->send_data_buffer[5] = (uint8)( right_duty & 0x00FF);
    device_value->send_data_buffer[6] = device_value->send_data_buffer[0] + 
                                        device_value->send_data_buffer[1] + 
                                        device_value->send_data_buffer[2] + 
                                        device_value->send_data_buffer[3] + 
                                        device_value->send_data_buffer[4] + 
                                        device_value->send_data_buffer[5];

    uart_write_buffer(MOTOR_DRIVER_UART, device_value->send_data_buffer, 7);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �����ٶ���Ϣ  �ֽڰ�����
// ����˵��     device_value        ͨѶ�����ṹ��
// ����˵��     left_speed          ������ٶ�
// ����˵��     right_speed         �Ҳ����ٶ�
// ���ز���     void
// ʹ��ʾ��     motor_driver_send_speed(&motor_value, motor_left.motor_speed_filter, motor_right.motor_speed_filter);   // �ֽڰ�ͨѶ����Э�������
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_driver_send_speed(small_device_value_struct *device_value, int left_speed, int right_speed)
{
    device_value->send_data_buffer[0] = 0xA5;
    device_value->send_data_buffer[1] = 0X02;
    device_value->send_data_buffer[2] = (uint8)((left_speed  & 0xFF00) >> 8);
    device_value->send_data_buffer[3] = (uint8)( left_speed  & 0x00FF);
    device_value->send_data_buffer[4] = (uint8)((right_speed & 0xFF00) >> 8);
    device_value->send_data_buffer[5] = (uint8)( right_speed & 0x00FF);
    device_value->send_data_buffer[6] = device_value->send_data_buffer[0] + 
                                        device_value->send_data_buffer[1] + 
                                        device_value->send_data_buffer[2] + 
                                        device_value->send_data_buffer[3] + 
                                        device_value->send_data_buffer[4] + 
                                        device_value->send_data_buffer[5];
    uart_write_buffer(MOTOR_DRIVER_UART, device_value->send_data_buffer, 7);
}

uint32 uart_use_time;
//-------------------------------------------------------------------------------------------------------------------
// �������     ����ͨѶ���� �ص�����
// ����˵��     device_value        ͨѶ�����ṹ��
// ���ز���     void
// ʹ��ʾ��     motor_driver_control_callback(&motor_value);
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_driver_control_callback(small_device_value_struct *device_value)
{
    uint8 receive_data;                                                         // ���崮�ڽ��ձ���
    
    if(uart_query_byte(MOTOR_DRIVER_UART, &receive_data) == 1)                  // �ж��Ƿ���յ���������
    {
        fifo_write_element(&motor_driver_fifo, receive_data);                   // ������д�� fifo
        
        if(receive_data == '\n')                                                // �����յ�����ָ�� �س���'\n'  �򽫻س���־λ��λ ���ں�������
        {
            receive_enter_flag = 1;
        }
        
        motor_driver_control_loop(device_value);                                // �������ݽ��� �ú���Ҳ��������λ�õ���
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ����ͨѶ ��ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_driver_uart_init();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_driver_uart_init(void)
{
    fifo_init(&motor_driver_fifo, FIFO_DATA_8BIT, driver_fifo_buffer, 128);     // ��ʼ�� fifo �ṹ��
      
    uart_init(MOTOR_DRIVER_UART, 460800, MOTOR_DRIVER_RX, MOTOR_DRIVER_TX);     // ��ʼ�� ͨѶ���Դ��� 
    
    uart_rx_interrupt(MOTOR_DRIVER_UART, 1);                                    // �򿪴��ڽ����ж�
    
    timer_init(TC_TIME2_CH0, TIMER_US);
}













