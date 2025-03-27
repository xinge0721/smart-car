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

#include "hall_gather.h"


// ����Ӳ����������
int8 hall_hw_order[7]                  = {0, 6, 2, 3, 1, 5, 4};        

// ����Ӳ����������λ��ת�� 
// �����ɼ�����ֵΪ4 ����λ��ת������ó���ǰλ����6 ��Ӧ����Ӳ���������еĵ�6������ 
//     ��ǰλ��Ϊ6 ���������Ҫ���������ת����������һ��λ�û�����һ��λ�� 
//     �����һ��λ������5 �������Ӳ���������еó���5������ֵΪ5 ���������Ϊ5����λ
//     �����һ��λ������1 �������Ӳ���������еó���1������ֵΪ6 ���������Ϊ6����λ
int8 hall_hw_order_transition[7]       = {0, 4, 2, 3, 6, 5, 1};      

int32  left_change_time = 0;           // �������������������ʱ��

int32 right_change_time = 0;           // �����Ҳ�������������ʱ��

//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ��������ת����
// ����˵��     hall_now_location     ��ǰ�Ļ���λ��
// ����˵��     hall_last_location    ֮ǰ�Ļ���λ��
// ���ز���     motor_dir_enum        �����תλ��  
// ʹ��ʾ��     motor_left.motor_now_dir = motor_direction_calculate(hall_hw_order_transition[motor_left.hall_value_now], hall_hw_order_transition[motor_left.hall_value_last]);
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
motor_dir_enum motor_direction_calculate(int8 hall_now_location, int8 hall_last_location)
{
    int8 temp;
    
    temp = hall_now_location - hall_last_location;      
    
    if(func_abs(temp) > 3)
    {
        if(temp > 3)
        {
            temp -= 6;
        }
        else
        {
            temp += 6;
        }
    }

    return (temp > 0 ? FORWARD : REVERSE);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ������ж����
// ����˵��     void
// ���ز���     void 
// ʹ��ʾ��     motor_left_hall_output();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_left_hall_output(void)
{
    int8  hall_output_temp = 0;
    uint16 output_duty_temp = 0;
    
    if(motor_left.motor_duty >= 0)                                      // ���õ��ռ�ձȴ���0ʱ ִ����תƫ��
    {
       // ����ʵ�ʻ�����λ�� ���Եó���Ҫ����Ļ���λ���Ƕ���
       hall_output_temp = hall_hw_order_transition[motor_left.hall_value_now] + 1;
       
       if(6 < hall_output_temp)                                              // ������������λ��ʱ ��ȥ���λ��ʵ��ѭ��
       {
            hall_output_temp -= 6; 
       }
       
       hall_output_temp = hall_hw_order[hall_output_temp];                        // ��ȡ��Ӧλ�õĻ������루������λ��ƫ�Ƽ��� �������Ӧ�ø���λ�ò�ѯ��ȷ��λ��
    }
    else                                                                // ���õ����תʱִ�з�ת��ƫ�Ʒ���
    {
       // ��ȥʵ�ʻ�����λ�� ���Եó���Ҫ����Ļ���λ���Ƕ���
       hall_output_temp = hall_hw_order_transition[motor_left.hall_value_now] - 2;
    
       if(1 > hall_output_temp)
       {
          hall_output_temp += 6;
       }
       hall_output_temp = hall_hw_order[hall_output_temp];  
    }
    
    output_duty_temp = func_abs((int16)(motor_left.motor_duty * OUTPUT_DUTY_MAX));

    // ���ݼ���õ������λ���ö�Ӧ��������� ʹ�����ת��ָ��λ��
    switch(hall_output_temp)
    {
        case 1:     left_mos_q3q2_open(output_duty_temp);               break;	// 1 
        case 2:     left_mos_q5q4_open(output_duty_temp);               break;	// 2  
        case 3:     left_mos_q5q2_open(output_duty_temp);               break;	// 3 
        case 4:     left_mos_q1q6_open(output_duty_temp);               break;	// 4
        case 5:     left_mos_q3q6_open(output_duty_temp);               break;	// 5 
        case 6:     left_mos_q1q4_open(output_duty_temp);               break;	// 6   
        default:    left_mos_close();			                break;  
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���� �Ҳ����ж����
// ����˵��     void
// ���ز���     void 
// ʹ��ʾ��     motor_left_hall_output();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_right_hall_output(void)
{
    int8  hall_output_temp = 0;
    uint16 output_duty_temp = 0;
    
    if(motor_right.motor_duty >= 0)                                      // ���õ��ռ�ձȴ���0ʱ ִ����תƫ��
    {
         // ����ʵ�ʻ�����λ�� ���Եó���Ҫ����Ļ���λ���Ƕ���
         hall_output_temp = hall_hw_order_transition[motor_right.hall_value_now] + 1;
         
         if(6 < hall_output_temp)                                              // ������������λ��ʱ ��ȥ���λ��ʵ��ѭ��
         {
              hall_output_temp -= 6; 
         }
         
         hall_output_temp = hall_hw_order[hall_output_temp];                        // ��ȡ��Ӧλ�õĻ������루������λ��ƫ�Ƽ��� �������Ӧ�ø���λ�ò�ѯ��ȷ��λ��
    }
    else                                                                // ���õ����תʱִ�з�ת��ƫ�Ʒ���
    {
         // ��ȥʵ�ʻ�����λ�� ���Եó���Ҫ����Ļ���λ���Ƕ���
         hall_output_temp = hall_hw_order_transition[motor_right.hall_value_now] - 2;
      
         if(1 > hall_output_temp)
         {
            hall_output_temp += 6;
         }
         hall_output_temp = hall_hw_order[hall_output_temp];  
    }
    
    output_duty_temp = func_abs((int16)(motor_right.motor_duty * OUTPUT_DUTY_MAX));
    
    // ���ݼ���õ������λ���ö�Ӧ��������� ʹ�����ת��ָ��λ��
    switch(hall_output_temp)
    {
        case 1:     right_mos_q3q2_open(output_duty_temp);               break;	// 1 
        case 2:     right_mos_q5q4_open(output_duty_temp);               break;	// 2 
        case 3:     right_mos_q5q2_open(output_duty_temp);               break;	// 3
        case 4:     right_mos_q1q6_open(output_duty_temp);               break;	// 4
        case 5:     right_mos_q3q6_open(output_duty_temp);               break;	// 5 
        case 6:     right_mos_q1q4_open(output_duty_temp);               break;	// 6  
        default:    right_mos_close();			                  break;  
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���� ����� 20khz ���ڻص�����
// ����˵��     void
// ���ز���     void 
// ʹ��ʾ��     motor_left_hall_callback();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_left_hall_callback(void)
{
    static uint32 left_speed_count = 0;                         // ����������ٶȼƴ�
      
    uint8 hall_data_get[7] = {0};                               // ��������ɼ�����
    
    uint8 hall_data = 0;                                        // ����������ݱ���
    
    motor_left.hall_value_last = motor_left.hall_value_now;     // ������һ�εĻ�������

    for(int i = 0; i < 5; i ++)                                 // �����ɼ�5�λ���
    {
        hall_data = gpio_get_level(LEFT_MOTOR_HALL_A_PIN) * 1 + gpio_get_level(LEFT_MOTOR_HALL_B_PIN) * 2 + gpio_get_level(LEFT_MOTOR_HALL_C_PIN) * 4;
        
        hall_data_get[hall_data] ++;
    }
    
    hall_data = 0;                                              // ������������
    
    for(int i = 0; i < 7; i ++)                                 // ��ȡ�ɼ��������Ļ���ֵ
    {                                                           // �˴�������Ҫ��ͨ����β����˲� ��ֹ�ɼ���ż������������
        if(hall_data < hall_data_get[i])
        {
            hall_data = hall_data_get[i];
            
            motor_left.hall_value_now = i;
        }
    }
    
    if(motor_left.hall_value_now != motor_left.hall_value_last) // �ж��Ƿ���
    {
        motor_left.run_state = MOTOR_RUN;                       // �ɹ���������ĵ������״̬
      
        timer_stop(LEFT_MOTOR_COUNT_TIMER);                     // ֹͣ������
        
        left_change_time = timer_get(LEFT_MOTOR_COUNT_TIMER);   // ��ȡ������ʱ��
          
        timer_clear(LEFT_MOTOR_COUNT_TIMER);                    // �����ʱ������ֵ

        timer_start(LEFT_MOTOR_COUNT_TIMER);                    // ������ʱ������
          
        motor_left.motor_now_dir = motor_direction_calculate(hall_hw_order_transition[motor_left.hall_value_now], hall_hw_order_transition[motor_left.hall_value_last]); // ������ת����
        
        if(left_change_time > 250 || left_change_time == 0)     // ��������ʱ���� 250us ����Ϊ 0 ����������
        {       
            motor_left.motor_speed = 1428571 / left_change_time * motor_left.motor_now_dir;     // ������ת��
            
            motor_left_hall_output();                           // �����������
        }
    }
  
    if(timer_get(LEFT_MOTOR_COUNT_TIMER) > 1 * 1000 || timer_get(LEFT_MOTOR_COUNT_TIMER) == 0)  // �������������1ms ���� Ϊ0 ���������һ��
    {
        motor_left_hall_output();                               // �����������
    }
    
    if(motor_left.run_state == MOTOR_RUN && (timer_get(LEFT_MOTOR_COUNT_TIMER) > 10 * 1000 || timer_get(LEFT_MOTOR_COUNT_TIMER) == 0))  // ������״̬Ϊ������ ���� ����������10ms  ����Ϊ 0 ��ƴ� 
    {
        if(++ left_speed_count > 5)                             // �ƴγ���5�������״̬Ϊֹͣ
        {
            left_speed_count  = 5;                              // �ƴα���
            
            timer_stop(LEFT_MOTOR_COUNT_TIMER);                 // �رն�ʱ������
            
            timer_clear(LEFT_MOTOR_COUNT_TIMER);                // �����ʱ������ֵ
            
            motor_left.motor_speed = 0;                         // �ٶ����ݹ���
            
            motor_left.run_state = MOTOR_STOP;                  // �������״̬����Ϊֹͣ
        }
    }
    else                                                        // ��������ƴ�
    {
        left_speed_count = 0;
    }
    
    motor_left.motor_speed_filter = (motor_left.motor_speed_filter * 19 + motor_left.motor_speed) / 20; // ת���˲�
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ���� �Ҳ��� 20khz ���ڻص�����
// ����˵��     void
// ���ز���     void 
// ʹ��ʾ��     motor_right_hall_callback();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void motor_right_hall_callback(void)
{
    static uint32 right_speed_count = 0;                         // ����������ٶȼƴ�
                                                                 
    uint8 hall_data_get[7] = {0};                                // ��������ɼ�����
                                                                 
    uint8 hall_data = 0;                                         // ����������ݱ���
                                                                 
    motor_right.hall_value_last = motor_right.hall_value_now;    // ������һ�εĻ�������
                                                                 
    for(int i = 0; i < 5; i ++)                                 // �����ɼ�5�λ���
    {
        hall_data = gpio_get_level(RIGHT_MOTOR_HALL_A_PIN) * 1 + gpio_get_level(RIGHT_MOTOR_HALL_B_PIN) * 2 + gpio_get_level(RIGHT_MOTOR_HALL_C_PIN) * 4;
        
        hall_data_get[hall_data] ++;
    }
    
    hall_data = 0;                                              // ������������
                                                                
    for(int i = 0; i < 7; i ++)                                // ��ȡ�ɼ��������Ļ���ֵ 
    {                                                           // �˴�������Ҫ��ͨ����β����˲� ��ֹ�ɼ���ż������������
        if(hall_data < hall_data_get[i])
        {
            hall_data = hall_data_get[i];
            
            motor_right.hall_value_now = i;
        }
    }
    
    if(motor_right.hall_value_now != motor_right.hall_value_last)// �ж��Ƿ���
    {                                                              
        motor_right.run_state = MOTOR_RUN;                        // �ɹ���������ĵ������״̬ 
                                                                   
        timer_stop(RIGHT_MOTOR_COUNT_TIMER);                      // ֹͣ������ 
                                                                   
        right_change_time = timer_get(RIGHT_MOTOR_COUNT_TIMER);   // ��ȡ������ʱ�� 
                                                                   
        timer_clear(RIGHT_MOTOR_COUNT_TIMER);                     // �����ʱ������ֵ 
                                                                   
        timer_start(RIGHT_MOTOR_COUNT_TIMER);                     // ������ʱ������ 
      
        motor_right.motor_now_dir = motor_direction_calculate(hall_hw_order_transition[motor_right.hall_value_now], hall_hw_order_transition[motor_right.hall_value_last]);// ������ת����
        
        if(right_change_time > 250 || right_change_time == 0)     // ��������ʱ���� 250us ����Ϊ 0 ����������
        {       
            motor_right.motor_speed = 1428571 / right_change_time * motor_right.motor_now_dir; // ������ת��
            
            motor_right_hall_output();                            // �����������      
        }
    }
    
    if(timer_get(RIGHT_MOTOR_COUNT_TIMER) > 1 * 1000 || timer_get(RIGHT_MOTOR_COUNT_TIMER) == 0)        // �������������1ms ���� Ϊ0 ���������һ��
    {   
        motor_right_hall_output();                                // �����������
    }
    
    if(motor_right.run_state == MOTOR_RUN && (timer_get(RIGHT_MOTOR_COUNT_TIMER) > 10 * 1000 || timer_get(RIGHT_MOTOR_COUNT_TIMER) == 0)) // ������״̬Ϊ������ ���� ����������10ms  ����Ϊ 0 ��ƴ� 
    {                                                           
        if(++ right_speed_count > 5)                             // �ƴγ���5�������״̬Ϊֹͣ  
        {                                                        
            right_speed_count  = 5;                              // �ƴα���
                                                                 
            timer_stop(RIGHT_MOTOR_COUNT_TIMER);                 // �رն�ʱ������
                                                                 
            motor_right.motor_speed = 0;                         // �����ʱ������ֵ
                                                                 
            motor_right.run_state = MOTOR_STOP;                  // �ٶ����ݹ���
        }                                                        
    }                                                            // �������״̬����Ϊֹͣ
    else                                                         
    {                                                            
        right_speed_count = 0;                                   // ��������ƴ�
    }
    
    motor_right.motor_speed_filter = (motor_right.motor_speed_filter * 19 + motor_right.motor_speed) / 20; // ת���˲�
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ���� �ɼ���ʼ��
// ����˵��     void
// ���ز���     void 
// ʹ��ʾ��     hall_gather_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
void hall_gather_init(void)
{         
    gpio_init(LEFT_MOTOR_HALL_A_PIN, GPI, 1, GPI_FLOATING_IN);   // ��ʼ�� ����� A�� ��������
    
    gpio_init(LEFT_MOTOR_HALL_B_PIN, GPI, 1, GPI_FLOATING_IN);   // ��ʼ�� ����� B�� ��������
    
    gpio_init(LEFT_MOTOR_HALL_C_PIN, GPI, 1, GPI_FLOATING_IN);   // ��ʼ�� ����� C�� ��������
    
    pit_us_init(LEFT_MOTOR_PIT_TIMER, 50);                       // ��ʼ�� ����� ��ѯ�����ж�    
    
    timer_init(LEFT_MOTOR_COUNT_TIMER, TIMER_US);                // ��ʼ�� �����������ʱ��
    
    gpio_init(RIGHT_MOTOR_HALL_A_PIN, GPI, 1, GPI_FLOATING_IN);  // ��ʼ�� �Ҳ��� A�� ��������
    
    gpio_init(RIGHT_MOTOR_HALL_B_PIN, GPI, 1, GPI_FLOATING_IN);  // ��ʼ�� �Ҳ��� B�� ��������
    
    gpio_init(RIGHT_MOTOR_HALL_C_PIN, GPI, 1, GPI_FLOATING_IN);  // ��ʼ�� �Ҳ��� C�� ��������
    
    pit_us_init(RIGHT_MOTOR_PIT_TIMER, 50);                      // ��ʼ�� �Ҳ��� ��ѯ�����ж�    
    
    timer_init(RIGHT_MOTOR_COUNT_TIMER, TIMER_US);               // ��ʼ�� �Ҳ���������ʱ��
}   












