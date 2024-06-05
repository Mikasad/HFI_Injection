/**********************************
             慧驱动
        视频教程详见QQ空间或B站
        其他事宜详见readme.txt
          QQ：1323279545
         微信：huiqudong
        官网：www.huiqudong.cn
**********************************/
#include "speed_pid.h"


#define SPEED_PID_PERIOD 0.001F

//real32_T SPEED_PI_I = 0.01F;
//real32_T SPEED_PI_KB = 0.015F;
//real32_T SPEED_PI_LOW_LIMIT = -5.0F;
//real32_T SPEED_PI_P = 0.001F;
//real32_T SPEED_PI_UP_LIMIT = 5.0F;

real32_T SPEED_PI_I = 0.06F;
real32_T SPEED_PI_KB = 0.015F;
real32_T SPEED_PI_LOW_LIMIT = -5.0F;
real32_T SPEED_PI_P = 0.005F;
real32_T SPEED_PI_UP_LIMIT = 5.0F;

//real32_T SPEED_PI_I = 10.01F;
//real32_T SPEED_PI_KB = 10.015F;
//real32_T SPEED_PI_LOW_LIMIT = -15.0F;
//real32_T SPEED_PI_P = 10.001F;
//real32_T SPEED_PI_UP_LIMIT = 15.0F;



real32_T Speed_Ref;       //速度参考          
real32_T Speed_Fdk;        //速度反馈          
real32_T Speed_Pid_Out;    //速度PID输出，也就是Q轴电流环的参考             

SPEED_PID_DEF Speed_Pid;

void Speed_Pid_Calc(real32_T ref_temp,real32_T fdb_temp,real32_T* out_temp,SPEED_PID_DEF* current_pid_temp)
{

  real32_T error;
  real32_T temp;

  error = ref_temp - fdb_temp; //6.28318548F * ref_temp - fdb_temp;             //2*pi的作用是 单位转换   Hz转换为rad/s

  temp = error * current_pid_temp->P_Gain + current_pid_temp->I_Sum;

 
  if (temp > current_pid_temp->Max_Output) {
    *out_temp = current_pid_temp->Max_Output;
  } else if (temp < current_pid_temp->Min_Output) {
    *out_temp = current_pid_temp->Min_Output;
  } else {
    *out_temp = temp;
  }
  current_pid_temp->I_Sum += ((*out_temp - temp) * current_pid_temp->B_Gain + current_pid_temp->I_Gain* error) * SPEED_PID_PERIOD;
}


void speed_pid_initialize(void)
{
  Speed_Pid.P_Gain = SPEED_PI_P;
  Speed_Pid.I_Gain = SPEED_PI_I;
  Speed_Pid.B_Gain = SPEED_PI_KB;
  Speed_Pid.Max_Output = SPEED_PI_UP_LIMIT;
  Speed_Pid.Min_Output = SPEED_PI_LOW_LIMIT;
  Speed_Pid.I_Sum = 0.0f;
}


