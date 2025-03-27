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
* �ļ�����          motor_control
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

#include "motor_control.h"

motor_struct motor_left;

motor_struct motor_right;

//-------------------------------------------------------------------------------------------------------------------
// �������     ���������ж�
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_left_updat_isr();
// ��ע��Ϣ     ��ǰִ�к�ʱ 8us  
//-------------------------------------------------------------------------------------------------------------------
void motor_left_update_isr(void)
{
#if MOTOR_DRIVER_MODE    == FAST_FOC_MODE  
  
    static uint8  left_speed_count = 0;                                         // �ٶ���ϼƴ�
    
#if MOTOR_LOCKED_PROTECT == DRIVER_ENABLE    
    
    static uint32 left_protect_count = 0;                                       // ��������ƴ�
      
#endif    
    
    Cy_Tcpwm_Counter_ClearTC_Intr(MOTOR_LEFT_A_PHASE_TCPWM_TIMER);              // ����жϱ�־λ  

    motor_left.menc15a_value_now = menc15a_get_absolute_data(menc15a_1_module); // �ɼ�������ű�������ֵ
    
    motor_left.menc15a_value_offset = menc15a_absolute_offset_data[0];          // ��ȡ�ű���������һ�ε�ƫ��ֵ
    
    motor_left.menc15a_offset_integral += motor_left.menc15a_value_offset;      // ƫ��ֵ���� �����ٶȼ���
    
    if(++ left_speed_count >= (FPWM / 1000))                                    // ÿ�������һ���ٶ�
    {
        left_speed_count = 0;
        
        motor_left.motor_speed = (motor_left.menc15a_offset_integral * 1.8310546875f);    // �ٶ��������
        
        motor_left.motor_speed_filter = ((motor_left.motor_speed_filter * 19.0f + motor_left.motor_speed) / 20.0f);  // �ٶ����ݵ�ͨ�˲�
        
        motor_left.menc15a_offset_integral = 0;                                 // ƫ�ƻ��ֹ���
        
#if MOTOR_LOCKED_PROTECT == DRIVER_ENABLE        
        
        if(func_abs(motor_left.motor_speed_filter) < 10.0f && func_abs(motor_left.motor_duty) >= MOTOR_LOCKED_DUTY_MAX)  // �ж��Ƿ��ת  ռ�ձȴ���10%������ת�����ݳ��� 500ms
        {
            left_protect_count ++;
            
            if(left_protect_count > MOTOR_LOCKED_TIME)
            {
                left_protect_count = MOTOR_LOCKED_TIME;
                
                motor_left.motor_protect_state = RROTECT_MODE;                  // ��������  �����������״̬
            }
        }
        else
        {
            left_protect_count = 0;                                             // ������ձ����ƴ�
        }
#endif
    }
      
    fast_foc_calculate(&motor_left_foc_driver,                                  // FAST-FOC ���� �������ֵ        
                       motor_left.menc15a_value_now, 
                       motor_left.motor_duty > 0 ? motor_left.motor_duty : -motor_left.motor_duty, 
                       motor_left.motor_duty > 0 ? motor_left.motor_control_angle : -motor_left.motor_control_angle);  
    
    if(motor_left.motor_protect_state == RROTECT_MODE || motor_left.encoder_state == ENCODER_ERROR)
    {
        motor_left_duty_set(0, 0, 0);                                           // �������״̬ ���� �ű��������� �����0ռ�ձ� ɲ��
    }
    else
    {
        motor_left_duty_set(motor_left_foc_driver.ouput_duty[0], motor_left_foc_driver.ouput_duty[1], motor_left_foc_driver.ouput_duty[2]); // �����������ռ�ձ�
    }
#else    
    Cy_Tcpwm_Counter_ClearTC_Intr((volatile stc_TCPWM_GRP_CNT_t*) &TCPWM0->GRP[1].CNT[(LEFT_MOTOR_PIT_TIMER - 3)]);              // ����жϱ�־λ  
    
    motor_left_hall_callback();                                                 // ����������ɼ��ص�
#endif
}


//-------------------------------------------------------------------------------------------------------------------
// �������     �ҵ�������ж�
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_right_updat_isr();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_right_update_isr(void)
{       
#if MOTOR_DRIVER_MODE    == FAST_FOC_MODE    
  
    static uint8  right_speed_count = 0;                                        // �ٶ���ϼƴ�

#if MOTOR_LOCKED_PROTECT == DRIVER_ENABLE
    
    static uint32 right_protect_count = 0;                                      // ��������ƴ�

#endif
    
    Cy_Tcpwm_Counter_ClearTC_Intr(MOTOR_RIGHT_A_PHASE_TCPWM_TIMER);             // ����жϱ�־λ  
                                                                                
    motor_right.menc15a_value_now = menc15a_get_absolute_data(menc15a_2_module);// �ɼ�������ű�������ֵ
                                                                                
    motor_right.menc15a_value_offset = menc15a_absolute_offset_data[1];         // ��ȡ�ű���������һ�ε�ƫ��ֵ
                                                                                
    motor_right.menc15a_offset_integral += motor_right.menc15a_value_offset;    // ƫ��ֵ���� �����ٶȼ���
                                                                                
    if(++ right_speed_count >= 20)                                              // ÿ�������һ���ٶ� 
    {
        right_speed_count = 0;
        
        motor_right.motor_speed = (motor_right.menc15a_offset_integral * 1.8310546875f);    // �ٶ��������
        
        motor_right.motor_speed_filter = ((motor_right.motor_speed_filter * 19.0f + motor_right.motor_speed) / 20.0f);     // �ٶ����ݵ�ͨ�˲�
        
        motor_right.menc15a_offset_integral = 0;                                // ƫ�ƻ��ֹ���        

#if MOTOR_LOCKED_PROTECT == DRIVER_ENABLE
        
        if(func_abs(motor_right.motor_speed_filter) < 10.0f && func_abs(motor_right.motor_duty) >= MOTOR_LOCKED_DUTY_MAX)  // �ж��Ƿ��ת  ռ�ձȴ��� 10% ������ת�����ݳ��� 500ms
        {
            right_protect_count ++;
            
            if(right_protect_count > MOTOR_LOCKED_TIME)
            {
                right_protect_count = MOTOR_LOCKED_TIME;
                
                motor_right.motor_protect_state = RROTECT_MODE;                 // ��������  �����������״̬
            }
        }
        else
        {
            right_protect_count = 0;                                            // ������ձ����ƴ�
        }
#endif        
    }
      
    fast_foc_calculate(&motor_right_foc_driver,                                 // FAST-FOC ���� �������ֵ        
                       motor_right.menc15a_value_now, 
                       motor_right.motor_duty > 0 ? motor_right.motor_duty : -motor_right.motor_duty, 
                       motor_right.motor_duty > 0 ? motor_right.motor_control_angle : -motor_right.motor_control_angle);  
    
    if(motor_right.motor_protect_state == RROTECT_MODE || motor_right.encoder_state == ENCODER_ERROR)
    {
        motor_right_duty_set(0, 0, 0);                                          // ����״̬���0ռ�ձ� ɲ��
    }
    else
    {
        motor_right_duty_set(motor_right_foc_driver.ouput_duty[0], motor_right_foc_driver.ouput_duty[1], motor_right_foc_driver.ouput_duty[2]);     // �������ռ�ձ�
    }
#else    
    Cy_Tcpwm_Counter_ClearTC_Intr((volatile stc_TCPWM_GRP_CNT_t*) &TCPWM0->GRP[1].CNT[(RIGHT_MOTOR_PIT_TIMER - 3)]);             // ����жϱ�־λ  
    
    motor_right_hall_callback();                                                // �Ҳ��������ɼ��ص�
#endif
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ������㼰��ת�������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_left_zero_calibration();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_left_zero_calibration(void)
{        
    int16  rotation_direction = 0; 
    int32  encoder_data_integral = 0;
    uint16 stop_encoder_data = 0;
    
    // �������ʱĬ�ϻָ������������״̬
    motor_left.motor_protect_state  = NORMAL_RUN_MODE;          
    
    // ��ʼ��Ĭ�����ò���
    fast_foc_init(&motor_left_foc_driver, ENCODER_PRECISION, OUTPUT_DUTY_MAX, 1, 0, 1);          
    
    // ������λ 20% ռ�ձ�
    fast_foc_calculate(&motor_left_foc_driver, 0, 0.2, 0);                              
    
    // ���ռ�ձȵ����
    motor_left_duty_set(motor_left_foc_driver.ouput_duty[0], motor_left_foc_driver.ouput_duty[1], motor_left_foc_driver.ouput_duty[2]); 
    
    // ��ʱ 200ms �ȴ�����ص����
    system_delay_ms(200);                                                 
    
    // ��ȡ��ǰ�ű�����
    menc15a_get_absolute_data((menc15a_module_enum)LEFT_MOTOR);  
    
    // ����ǣ�� 100 �� 
    for(uint16_t i = 0; i <= 100; i ++)                                                                         
    {
        // �� 10% ռ�ձ�ѭ��ǣ��
        fast_foc_calculate(&motor_left_foc_driver, ENCODER_PRECISION * i / 100, 0.1, 0);
        
        // ���ռ�ձȵ����
        motor_left_duty_set(motor_left_foc_driver.ouput_duty[0], motor_left_foc_driver.ouput_duty[1], motor_left_foc_driver.ouput_duty[2]);
        
        // ����ǣ�����Ϊ��Ĭ��5ms�� 
        system_delay_ms(5);                                                                   
        
        // ��ȡ��ǰ�ű�������ֵ
        menc15a_get_absolute_data((menc15a_module_enum)LEFT_MOTOR);                         
        
        // �ۼƵ���ǣ������ת����
        if(menc15a_absolute_offset_data[LEFT_MOTOR] > 0)                                                                 
        {
            rotation_direction ++;
        }
        else if(menc15a_absolute_offset_data[LEFT_MOTOR] < 0)
        {
            rotation_direction --;
        }
        
        // �ۻ�����ǣ������ת��ֵ
        encoder_data_integral += menc15a_absolute_offset_data[LEFT_MOTOR];
    }                                                               
    
    // ��ȡǣ������ʱ�Ĵű�������ֵ
    stop_encoder_data = menc15a_absolute_data[LEFT_MOTOR];        
    
    // �ر����
    motor_left_duty_set(0, 0, 0);                                                        
    
    // �ж��Ƿ���ȷ��ȡ���ű����� ����ǣ������С�� 1000 ����Ϊ���û����ת   ��������Ϊ11����ζ�ų��� 32 �Լ��ĵ���޷����
    if(func_abs(encoder_data_integral) < 1000)
    {
        // �������ű�����״̬��־
        motor_left.encoder_state = ENCODER_ERROR;
        
        // ����Ĭ�ϲ���
        motor_left.zero_location = 0;
        motor_left.rotation_direction = 1;
        motor_left.pole_pairs = 7;
        
        // ������Ϣ��ӡ�� ����
        printf("left motor magnetic encoder error!!\r\n");   
    }
    else
    {
        // �������ű�����״̬��־
        motor_left.encoder_state = ENCODER_NORMAL;
        
        // ��ת�����һ�� ��ת��Ϊ 1  ��ת��Ϊ -1
        motor_left.rotation_direction = rotation_direction / (rotation_direction > 0 ? rotation_direction : -rotation_direction);      
        
        // ��ת����Ҫ��ǣ�������ı�������ֵ����
        if(motor_left.rotation_direction == -1)                                                                     
        {
            stop_encoder_data = ENCODER_PRECISION - stop_encoder_data;
        }
        
        // ���㼫����  �ű����ֵ ���� ��Ȧ��ǶȻ���ֵ ��������
        motor_left.pole_pairs = (uint16)round(ENCODER_PRECISION / func_abs(encoder_data_integral));
        
        
        // �������λ��  ����λ�� ���� ��ǶȵĴű���ֵ��Χ ȡ��
        motor_left.zero_location = stop_encoder_data % (ENCODER_PRECISION / motor_left.pole_pairs);                      
        
        // ���ռ�����������³�ʼ��fast_foc����
        fast_foc_init(&motor_left_foc_driver, ENCODER_PRECISION, OUTPUT_DUTY_MAX, motor_left.pole_pairs, motor_left.zero_location, motor_left.rotation_direction);       
        
        // ������Ϣ��ӡ�� ����
        printf("left motor zero:%d, dir:%s, pole pairs:%d\r\n", motor_left_foc_driver.motor_zero_location, 
                                                                 motor_left_foc_driver.motor_rotation_direction == 1 ? "forward" : "reverse", 
                                                                 motor_left.pole_pairs);     
    }
    
}

//-------------------------------------------------------------------------------------------------------------------
// �������     �ҵ����㼰��ת�������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_right_zero_calibration();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_right_zero_calibration(void)
{        
    int16  rotation_direction = 0; 
    int32  encoder_data_integral = 0;
    uint16 stop_encoder_data = 0;
    
    
    // �������ʱĬ�ϻָ������������״̬
    motor_right.motor_protect_state  = NORMAL_RUN_MODE;     
    
    // ��ʼ��Ĭ�����ò���
    fast_foc_init(&motor_right_foc_driver, ENCODER_PRECISION, OUTPUT_DUTY_MAX, 1, 0, 1);   
    
    // ������λ 20% ռ�ձ�        
    fast_foc_calculate(&motor_right_foc_driver, 0, 0.2, 0);                                     
    
    // ���ռ�ձȵ����
    motor_right_duty_set(motor_right_foc_driver.ouput_duty[0], motor_right_foc_driver.ouput_duty[1], motor_right_foc_driver.ouput_duty[2]); 
    
    // ��ʱ 200ms �ȴ�����ص����
    system_delay_ms(200);                                                                                       
    
    // ��ȡ��ǰ�ű����� 
    menc15a_get_absolute_data((menc15a_module_enum)RIGHT_MOTOR);  
    
    // ����ǣ�� 100 �� 
    for(uint16_t i = 0; i <= 100; i ++)                                                                         
    {
        // �� 10% ռ�ձ�ѭ��ǣ��     
        fast_foc_calculate(&motor_right_foc_driver, ENCODER_PRECISION * i / 100, 0.1, 0);     
        
        // ���ռ�ձȵ����
        motor_right_duty_set(motor_right_foc_driver.ouput_duty[0], motor_right_foc_driver.ouput_duty[1], motor_right_foc_driver.ouput_duty[2]);
        
        // ����ǣ�����Ϊ��Ĭ��5ms�� 
        system_delay_ms(5);                                                                                     
        
        // ��ȡ��ǰ�ű�������ֵ
        menc15a_get_absolute_data((menc15a_module_enum)RIGHT_MOTOR);                                                            
        
        // �ۼƵ���ǣ������ת����
        if(menc15a_absolute_offset_data[RIGHT_MOTOR] > 0)                                                                 
        {
            rotation_direction ++;
        }
        else if(menc15a_absolute_offset_data[RIGHT_MOTOR] < 0)
        {
            rotation_direction --;
        }
        
        // �ۻ�����ǣ������ת��ֵ
        encoder_data_integral += menc15a_absolute_offset_data[RIGHT_MOTOR];
    }                                                                              
    
    // ��ȡǣ������ʱ�Ĵű�������ֵ
    stop_encoder_data = menc15a_absolute_data[RIGHT_MOTOR];                            
    
    // �ر����
    motor_right_duty_set(0, 0, 0);                                                     
    
    // �ж��Ƿ���ȷ��ȡ���ű����� ����ǣ������С�� 1000 ����Ϊ���û����ת   ��������Ϊ11����ζ�ų��� 32 �Լ��ĵ���޷����
    if(func_abs(encoder_data_integral) < 1000)
    {
        // �����Ҳ�ű�����״̬��־
        motor_right.encoder_state = ENCODER_ERROR;
        
        // ����Ĭ�ϲ���
        motor_right.zero_location = 0;
        motor_right.rotation_direction = 1;
        motor_right.pole_pairs = 7;
        
        // ������Ϣ��ӡ�� ����
        printf("right motor magnetic encoder error!!\r\n");   
    }
    else
    {
        // �����Ҳ�ű�����״̬��־
        motor_right.encoder_state = ENCODER_NORMAL;
        // ��ת�����һ�� ��ת��Ϊ 1  ��ת��Ϊ -1
        motor_right.rotation_direction = rotation_direction / (rotation_direction > 0 ? rotation_direction : -rotation_direction);      
        
        // ��ת����Ҫ��ǣ�������ı�������ֵ����
        if(motor_right.rotation_direction == -1)                                                                     
        {
            stop_encoder_data = ENCODER_PRECISION - stop_encoder_data;
        }
        
        // ���㼫����  �ű����ֵ ���� ��Ȧ��ǶȻ���ֵ ��������
        motor_right.pole_pairs = (uint16)round(ENCODER_PRECISION / func_abs(encoder_data_integral));
        
        // �������λ��  ����λ�� ���� ��ǶȵĴű���ֵ��Χ ȡ��
        motor_right.zero_location = stop_encoder_data % (ENCODER_PRECISION / motor_right.pole_pairs);               
        
        // ���ռ�����������³�ʼ��fast_foc����
        fast_foc_init(&motor_right_foc_driver, ENCODER_PRECISION, OUTPUT_DUTY_MAX, motor_right.pole_pairs, motor_right.zero_location, motor_right.rotation_direction); 
        
        // ������Ϣ��ӡ�� ����
        printf("RIGHT MOTOR ZERO:%d, DIR:%s, POLE_PAIRS��%d\r\n", motor_right_foc_driver.motor_zero_location, 
                                                                  motor_right_foc_driver.motor_rotation_direction == 1 ? "forward" : "reverse", 
                                                                  motor_right.pole_pairs);     
    }

}

//-------------------------------------------------------------------------------------------------------------------
// �������     ˫�����㼰��ת����ͬʱ����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_both_zero_calibration();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_both_zero_calibration(void)
{        
    int16  rotation_direction[2] = {0}; 
    int32  encoder_data_integral[2] = {0};
    uint16 stop_encoder_data[2] = {0};    
    
    // �������ʱĬ�ϻָ������������״̬
    motor_left.motor_protect_state   = NORMAL_RUN_MODE;     
    motor_right.motor_protect_state  = NORMAL_RUN_MODE;     
    
    // ��ʼ��Ĭ�����ò���
    fast_foc_init(&motor_left_foc_driver,  ENCODER_PRECISION, OUTPUT_DUTY_MAX, 1, 0, 1);
    fast_foc_init(&motor_right_foc_driver, ENCODER_PRECISION, OUTPUT_DUTY_MAX, 1, 0, 1);    
    
    // ������λ 20% ռ�ձ�
    fast_foc_calculate(&motor_left_foc_driver,  0, 0.2, 0);
    fast_foc_calculate(&motor_right_foc_driver, 0, 0.2, 0);                            
    
    // ���ռ�ձȵ����
    motor_left_duty_set (motor_left_foc_driver.ouput_duty[0],  motor_left_foc_driver.ouput_duty[1],  motor_left_foc_driver.ouput_duty[2] );
    motor_right_duty_set(motor_right_foc_driver.ouput_duty[0], motor_right_foc_driver.ouput_duty[1], motor_right_foc_driver.ouput_duty[2]); 
    
    // ��ʱ 200ms �ȴ�����ص����
    system_delay_ms(200);                                                                                       
    
    // ��ȡ��ǰ�ű�����
    menc15a_get_absolute_data((menc15a_module_enum)LEFT_MOTOR); 
    menc15a_get_absolute_data((menc15a_module_enum)RIGHT_MOTOR);  
    
    // ����ǣ�� 100 �� 
    for(uint16_t i = 0; i <= 100; i ++)                                                                         
    {
        // �� 10% ռ�ձ�ѭ��ǣ��
        fast_foc_calculate(&motor_left_foc_driver,  ENCODER_PRECISION * i / 100, 0.1, 0);
        fast_foc_calculate(&motor_right_foc_driver, ENCODER_PRECISION * i / 100, 0.1, 0);     
        
        // ���ռ�ձȵ����
        motor_left_duty_set (motor_left_foc_driver.ouput_duty[0],  motor_left_foc_driver.ouput_duty[1],  motor_left_foc_driver.ouput_duty[2] );
        motor_right_duty_set(motor_right_foc_driver.ouput_duty[0], motor_right_foc_driver.ouput_duty[1], motor_right_foc_driver.ouput_duty[2]);
        
        // ����ǣ�����Ϊ��Ĭ��5ms�� 
        system_delay_ms(5);                                                                                     
        
        // ��ȡ��ǰ�ű�������ֵ
        menc15a_get_absolute_data((menc15a_module_enum)LEFT_MOTOR);
        menc15a_get_absolute_data((menc15a_module_enum)RIGHT_MOTOR);                                                            
        
        // �ۼƵ���ǣ������ת����
        if(menc15a_absolute_offset_data[LEFT_MOTOR] > 0)                                                                 
        {
            rotation_direction[LEFT_MOTOR] ++;
        }
        else if(menc15a_absolute_offset_data[LEFT_MOTOR] < 0)
        {
            rotation_direction[LEFT_MOTOR] --;
        }
        if(menc15a_absolute_offset_data[RIGHT_MOTOR] > 0)                                                                 
        {
            rotation_direction[RIGHT_MOTOR] ++;
        }
        else if(menc15a_absolute_offset_data[RIGHT_MOTOR] < 0)
        {
            rotation_direction[RIGHT_MOTOR] --;
        }
        
        // �ۻ�����ǣ������ת��ֵ
        encoder_data_integral[LEFT_MOTOR] += menc15a_absolute_offset_data[LEFT_MOTOR];
        encoder_data_integral[RIGHT_MOTOR] += menc15a_absolute_offset_data[RIGHT_MOTOR];
    }                                                                                      
    
    // ��ȡǣ������ʱ�Ĵű�������ֵ
    stop_encoder_data[LEFT_MOTOR] = menc15a_absolute_data[LEFT_MOTOR];
    stop_encoder_data[RIGHT_MOTOR] = menc15a_absolute_data[RIGHT_MOTOR];                    
    
    // �ر����
    motor_left_duty_set (0, 0, 0);    
    motor_right_duty_set(0, 0, 0);    
    
    // �ж��Ƿ���ȷ��ȡ���ű����� ����ǣ������С�� 1000 ����Ϊ���û����ת  ��������Ϊ11����ζ�ų��� 32 �Լ��ĵ���޷����
    if(func_abs(encoder_data_integral[LEFT_MOTOR]) < 1000)
    {
        // �������ű�����״̬��־
        motor_left.encoder_state = ENCODER_ERROR;
        
        // ����Ĭ�ϲ���
        motor_left.zero_location = 0;
        motor_left.rotation_direction = 1;
        motor_left.pole_pairs = 7;
        
        // ������Ϣ��ӡ�� ����
        printf("left motor magnetic encoder error!!\r\n");   
    }
    else
    {
        // �������ű�����״̬��־
        motor_left.encoder_state = ENCODER_NORMAL;
        
        // ��ת�����һ�� ��ת��Ϊ 1  ��ת��Ϊ -1
        motor_left.rotation_direction  = rotation_direction[LEFT_MOTOR]  / (rotation_direction[LEFT_MOTOR]  > 0 ? rotation_direction[LEFT_MOTOR]  : -rotation_direction[LEFT_MOTOR]) ;  

        // ��ת����Ҫ��ǣ�������ı�������ֵ����
        if(motor_left.rotation_direction == -1)                                                                     
        {
            stop_encoder_data[LEFT_MOTOR] = ENCODER_PRECISION - stop_encoder_data[LEFT_MOTOR];
        }
        
        // ���㼫����  �ű����ֵ ���� ��Ȧ��ǶȻ���ֵ ��������
        motor_left.pole_pairs  = (uint16)round((float)ENCODER_PRECISION / func_abs((float)encoder_data_integral[LEFT_MOTOR]));
 
        // �������λ��  ����λ�� ���� ��ǶȵĴű���ֵ��Χ ȡ��
        motor_left.zero_location  = stop_encoder_data[LEFT_MOTOR] % (ENCODER_PRECISION / motor_left.pole_pairs );

        // ���ռ�����������³�ʼ��fast_foc����
        fast_foc_init(&motor_left_foc_driver,  ENCODER_PRECISION, OUTPUT_DUTY_MAX, motor_left.pole_pairs,  motor_left.zero_location,  motor_left.rotation_direction );

        // ������Ϣ��ӡ�� ����
        printf("LEFT MOTOR ZERO:%d, DIR:%s, POLE_PAIRS��%d\r\n",  motor_left_foc_driver.motor_zero_location, 
                                                                  motor_left_foc_driver.motor_rotation_direction  == 1 ? "forward" : "reverse", 
                                                                  motor_left.pole_pairs);    
    }
    
    // �ж��Ƿ���ȷ��ȡ���ű����� ����ǣ������С�� 1000 ����Ϊ���û����ת ��������Ϊ11����ζ�ų��� 32 �Լ��ĵ���޷����
    if(func_abs(encoder_data_integral[RIGHT_MOTOR]) < 1000)
    {
        // �����Ҳ�ű�����״̬��־
        motor_right.encoder_state = ENCODER_ERROR;
        
        // ����Ĭ�ϲ���
        motor_right.zero_location = 0;
        motor_right.rotation_direction = 1;
        motor_right.pole_pairs = 7;
        
        // ������Ϣ��ӡ�� ����
        printf("right motor magnetic encoder error!!\r\n");   
    }
    else
    {
        // �����Ҳ�ű�����״̬��־
        motor_right.encoder_state = ENCODER_NORMAL;
        
        // ��ת�����һ�� ��ת��Ϊ 1  ��ת��Ϊ -1
        motor_right.rotation_direction = rotation_direction[RIGHT_MOTOR] / (rotation_direction[RIGHT_MOTOR] > 0 ? rotation_direction[RIGHT_MOTOR] : -rotation_direction[RIGHT_MOTOR]);   
        
        // ��ת����Ҫ��ǣ�������ı�������ֵ����
        if(motor_right.rotation_direction == -1)                                                                     
        {
            stop_encoder_data[RIGHT_MOTOR] = ENCODER_PRECISION - stop_encoder_data[RIGHT_MOTOR];
        }
        
        // ���㼫����  �ű����ֵ ���� ��Ȧ��ǶȻ���ֵ ��������
        motor_right.pole_pairs = (uint16)round((float)ENCODER_PRECISION / func_abs((float)encoder_data_integral[RIGHT_MOTOR]));
        
        // �������λ��  ����λ�� ���� ��ǶȵĴű���ֵ��Χ ȡ��
        motor_right.zero_location = stop_encoder_data[RIGHT_MOTOR] % (ENCODER_PRECISION / motor_right.pole_pairs);    
        
        // ���ռ�����������³�ʼ��fast_foc����
        fast_foc_init(&motor_right_foc_driver, ENCODER_PRECISION, OUTPUT_DUTY_MAX, motor_right.pole_pairs, motor_right.zero_location, motor_right.rotation_direction);       
        
        // ������Ϣ��ӡ�� ����
        printf("RIGHT MOTOR ZERO:%d, DIR:%s, POLE_PAIRS��%d\r\n", motor_right_foc_driver.motor_zero_location, 
                                                                  motor_right_foc_driver.motor_rotation_direction == 1 ? "forward" : "reverse", 
                                                                  motor_right.pole_pairs);    
    }
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ˫�����㼰��ת�������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_zero_calibration();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_zero_calibration(void)
{
    interrupt_global_disable();							// �ر�ȫ���ж�
  
    if(motor_left.motor_speed_filter != 0.0f || motor_right.motor_speed_filter != 0.0f)       // ������������ת ��ɲ��
    {
        motor_left_duty_set(0, 0, 0);                                           // �����ɲ��
        
        motor_right_duty_set(0, 0, 0);                                          // �Ҳ���ɲ��

        system_delay_ms(1000);                                                  // ɲ���ȴ�
    }
    
    motor_left_phase_check();                                                   // ������� MOS �� Ԥ�� ���ܼ�� ����û�м��������� �����Ҫ��Ϊ�ж��Ƿ�������
    
    motor_left_output_init(PWM_PRIOD_LOAD);                                     // ������� PWM ������³�ʼ��
        
    motor_right_phase_check();                                                  // �Ҳ����� MOS �� Ԥ�� ���ܼ�� ����û�м��������� �����Ҫ��Ϊ�ж��Ƿ�������
    
    motor_right_output_init(PWM_PRIOD_LOAD);                                    // �Ҳ����� PWM ������³�ʼ��

#if MOTOR_DRIVER_MODE == FAST_FOC_MODE                                          // ֻ���� FAST-FOC ģʽ�²���Ҫ�������

    motor_both_zero_calibration();                                              // ˫�����㼰��ת����ͬʱ����

    motor_flash_write();                                                        // �����������д��flash

#endif    

    interrupt_global_enable(0);							// ����ȫ���ж�
    
      
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ˫���FOC���Ƴ�ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_foc_control_init();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_foc_control_init(void)
{
    motor_left.motor_control_angle  = 90;       // FAST_FOC Ĭ��ǣ���Ƕ�Ϊ 90��        
    
    motor_left.motor_protect_state  = NORMAL_RUN_MODE;          // ��ʼ��Ĭ�ϵ��Ϊ��������ģʽ
    
    motor_left.encoder_state        = ENCODER_NORMAL;           // ��ʼ��Ĭ�ϴű�����Ϊ��������ģʽ
    
    motor_right.motor_control_angle = 90;       // FAST_FOC Ĭ��ǣ���Ƕ�Ϊ 90�� 
    
    motor_right.motor_protect_state = NORMAL_RUN_MODE;          // ��ʼ��Ĭ�ϵ��Ϊ��������ģʽ
    
    motor_right.encoder_state       = ENCODER_NORMAL;           // ��ʼ��Ĭ�ϴű�����Ϊ��������ģʽ    
    
    menc15a_init();                             // �ű�������ʼ��
    
    motor_flash_init();                         // FLASH��ʼ�� ��ȡ��㡢��ת���򡢼���������  
      
    fast_foc_init(&motor_left_foc_driver,  ENCODER_PRECISION, OUTPUT_DUTY_MAX, motor_left.pole_pairs,  motor_left.zero_location,  motor_left.rotation_direction );     // ����� FAST_FOC ���ܳ�ʼ��
    
    fast_foc_init(&motor_right_foc_driver, ENCODER_PRECISION, OUTPUT_DUTY_MAX, motor_right.pole_pairs, motor_right.zero_location, motor_right.rotation_direction);     // �Ҳ��� FAST_FOC ���ܳ�ʼ��
    
    motor_left_output_init(PWM_PRIOD_LOAD);     // ��������� PWM �����ʼ��
    
    motor_right_output_init(PWM_PRIOD_LOAD);    // �Ҳ������� PWM �����ʼ��
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ˫���BLDC���Ƴ�ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_bldc_control_init();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_bldc_control_init(void)
{  
    hall_gather_init();                         // �����ɼ���ʼ��
    
    motor_left.motor_protect_state  = NORMAL_RUN_MODE;          // ��ʼ��Ĭ�ϵ��Ϊ��������ģʽ
    
    motor_left.encoder_state        = ENCODER_NORMAL;           // ��ʼ��Ĭ�ϱ�����Ϊ��������ģʽ
  
    motor_left_output_init(PWM_PRIOD_LOAD);     // ��������� PWM �����ʼ��
    
    motor_right.motor_protect_state = NORMAL_RUN_MODE;          // ��ʼ��Ĭ�ϵ��Ϊ��������ģʽ
    
    motor_right.encoder_state       = ENCODER_NORMAL;           // ��ʼ��Ĭ�ϱ�����Ϊ��������ģʽ
                                                
    motor_right_output_init(PWM_PRIOD_LOAD);    // �Ҳ������� PWM �����ʼ��
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ˫������Ƴ�ʼ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     motor_control_init();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void motor_control_init(void)
{  
  
#if MOTOR_DRIVER_MODE == FAST_FOC_MODE
    
    motor_foc_control_init();                   // FAST_FOC ģʽ��ʼ��
    
#else
    
    motor_bldc_control_init();                  // ���� BLDC ģʽ��ʼ��
    
#endif
    
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ����ָ�ʱִ�� 
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     driver_cmd_forthwith();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void driver_cmd_forthwith(void)
{
    if(motor_value.refresh_flag == CMD_FORTHWITH)     // �ж��Ƿ���Ҫѭ��ִ��                          
    {
        switch(motor_value.immediate_command)   // �жϼ�ʱָ������
        {
            case SET_DUTY:                      // ����ռ�ձ�ָ��
            {
                motor_left.motor_duty  = func_limit_ab((float)(motor_value.receive_left_duty_data)  / 10000.0f, -0.9f, 0.9f);   // ���������ռ�ձ�
    
                motor_right.motor_duty = func_limit_ab((float)(motor_value.receive_right_duty_data) / 10000.0f, -0.9f, 0.9f);   // �����Ҳ���ռ�ձ�
    
            }break;
            
            default:break;
        }
        
        motor_value.immediate_command = NULL_CMD;// ���ָ��
      
        motor_value.refresh_flag = CMD_NULL;     // ˢ�±�־λ���
    }
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ����ָ����Ӧѭ��
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     driver_cmd_loop();
// ��ע��Ϣ       
//-------------------------------------------------------------------------------------------------------------------
void driver_cmd_loop(void)
{
    if(motor_value.refresh_flag == CMD_LOOP)     // �ж��Ƿ�ѭ��ָ��                          
    {
        switch(motor_value.immediate_command)   // �жϼ�ʱָ������
        {
            case NULL_CMD:break;                // ��ָ��ֱ���˳�
                       
            case SET_ZERO:                      // ������λ
            {
                motor_zero_calibration();       // ��У����λ
    
                printf("motor zero calibration is complete\r\n");               // ���������Ϣ
    
            }break;
                       
            case TEST_PHASE:                    // ���� BLDC ��λ
            {                   
                 
                
            }break;

            case SET_PHASE:                     // ���� BLDC ��λ
            {                   
                 
                
            }break;
            
            case ERROR_CMD:                     // ����ָ��
            {            
                 printf("error cmd\r\n");       // ���������Ϣ
    
            }break;
            
            default:break;
        }
        motor_value.immediate_command = NULL_CMD;// ���ָ��
      
        motor_value.refresh_flag = CMD_NULL;     // ˢ�±�־λ���
    }
    switch(motor_value.continue_command)        // �жϳ���ָ������
    {
        case GET_SPEED:                         // ��������ٶ���Ϣ
        {
            if(motor_value.cmd_type == STRING_TYPE)             // �ж��û�ͨѶ����
            {   
                printf("%d,%d\r\n", (int32)motor_left.motor_speed_filter, (int32)motor_right.motor_speed_filter);     // �ַ���ͨѶ��ֱ�Ӵ�ӡ�ַ���
            }
            else
            {
                motor_driver_send_speed(&motor_value, (int32)motor_left.motor_speed_filter, (int32)motor_right.motor_speed_filter);   // �ֽڰ�ͨѶ����Э�������
            }

        }break;
        
        case GET_PHASE_DUTY:                    // ���������λ��Ϣ
        {
            if(motor_value.select_motor == LEFT_MOTOR)          // �ж������һ��ĵ��
            {
                printf("%d,%d,%d\r\n", motor_left_foc_driver.ouput_duty[0], motor_left_foc_driver.ouput_duty[1], motor_left_foc_driver.ouput_duty[2]);
            }
            if(motor_value.select_motor == RIGHT_MOTOR)
            {
                printf("%d,%d,%d\r\n", motor_right_foc_driver.ouput_duty[0], motor_right_foc_driver.ouput_duty[1], motor_right_foc_driver.ouput_duty[2]);
            }

        }break;
        
        case GET_ENCODER:                       // �������������ԭʼ��ֵ
        {
            printf("%d,%d\r\n", menc15a_absolute_data[0], menc15a_absolute_data[1]);

        }break;
        
        case GET_ANGLE:                         // �����������������ת�Ƕ�����
        {
            printf("%.2f,%.2f\r\n", (float)menc15a_absolute_data[0] / ENCODER_PRECISION * 360.0f, (float)menc15a_absolute_data[1] / ENCODER_PRECISION * 360.0f);

        }break;
        
        case GET_VOLTAGE:                       // ���������ص�ѹ����
        {
            printf("voltage:%.2f\r\n", motor_left.battery_voltage);
  
        }break;
            
        default:break;
    }
}




