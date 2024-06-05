/**********************************
             慧驱动
        视频教程详见QQ空间或B站
        其他事宜详见readme.txt
          QQ：1323279545
         微信：huiqudong
        官网：www.huiqudong.cn
**********************************/
#include "main.h"
#include "low_task.h"



u16 hz_100_cnt = 0;
uint8_t motor_start_stop = 0;
uint8_t motor_start_stop_pre = 1;
u8 key1_flag;
u8 key2_flag;
u8 key3_flag;
void motor_start(void)
{
//  GPIO_SetBits(GPIOC,GPIO_Pin_9);
//  foc_algorithm_initialize();
//  Speed_Ref=20.0F;
//  speed_close_loop_flag=0;
//  Iq_ref=0.0f;

////  hall_angle_add=0.0005f;
////  hall_speed = 0.0f;
//  TIM_CtrlPWMOutputs(PWM_TIM,ENABLE);
//  motor_run_display_flag = 1;
}
void motor_stop(void)
{
//  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
//  TIM_CtrlPWMOutputs(PWM_TIM,DISABLE);
//  //motor_start_stop_pre=motor_start_stop;
//  motor_run_display_flag = 0;
  /*
  if(rtY.EKF[2]<140.0f)
  {
  GPIO_ResetBits(GPIOC,GPIO_Pin_9);
  TIM_CtrlPWMOutputs(PWM_TIM,DISABLE);
  motor_start_stop_pre=motor_start_stop;
  motor_run_display_flag = 0;
  }
  else
  {
    rtspeed_ref=20.0F;
    if(motor_start_stop==1)
    {
    motor_start_stop_pre=0;
    }else
    {
    motor_start_stop_pre=1;
    }
  }
*/
}


void low_control_task(void)
{
//  if(get_offset_flag == 2)
//  {
//    if(motor_start_stop_pre!=motor_start_stop)
//    {
//      motor_start_stop_pre=motor_start_stop;
//      if(motor_start_stop == 1)
//      {
//        motor_start();
//      }
//      else
//      {
//        motor_stop();
//      }
//      
//    }
//  }
//  
//  if(key1_flag==1)
//  {
//    if(motor_start_stop==0)
//    {
//      motor_start_stop=1;
//    }
//    else
//    {
//      motor_start_stop=0;
//    }
//    key1_flag=0;
//  }
//  if(key2_flag==1)
//  {
//    if(display_flag==0)
//    {
//      display_flag=1;
//    }
//    else if(display_flag==1)
//    {
//      display_flag=2;
//    }
//    else if(display_flag==2)
//    {
//      display_flag=0;
//    }
//    key2_flag=0;
//  }
//  if(key3_flag==1)
//  {
//    Speed_Ref+=5.0f;
//    float_test1 +=0.2f;
//    key3_flag=0;
//  }
}





//void SysTick_Handler(void)
//{
//  //rtspeed_ref=20.0F;
////  if(drv8301_init_ok_flag==1)
////  {
////    drv8301_protection();
////  }
//  Speed_Pid_Calc(Speed_Ref,Speed_Fdk,&Speed_Pid_Out,&Speed_Pid);
//  hz_100_cnt++;
//  if(hz_100_cnt==10)
//  {
////    communication_handle();
//    low_control_task();
//    TimingDelay_Decrement();
//    hz_100_cnt=0; 
//  }
//  
//}
