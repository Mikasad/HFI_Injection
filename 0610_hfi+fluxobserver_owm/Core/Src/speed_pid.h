/**********************************
             慧驱动
        视频教程详见QQ空间或B站
        其他事宜详见readme.txt
          QQ：1323279545
         微信：huiqudong
        官网：www.huiqudong.cn
**********************************/
#ifndef RTW_HEADER_speed_pid_h_
#define RTW_HEADER_speed_pid_h_
#include <stddef.h>
#ifndef speed_pid_COMMON_INCLUDES_
# define speed_pid_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                               

#include "MW_target_hardware_resources.h"


#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#define speed_pid_M                    (rtM)



extern real32_T Speed_Ref;                 
extern real32_T Speed_Fdk;                 
extern real32_T Speed_Pid_Out;             

typedef struct
{
  real32_T P_Gain;
  real32_T I_Gain;
  real32_T D_Gain;
  real32_T B_Gain;
  real32_T Max_Output;
  real32_T Min_Output;
  real32_T I_Sum;
}SPEED_PID_DEF;

extern SPEED_PID_DEF Speed_Pid;

extern void speed_pid_initialize(void);
extern void Speed_Pid_Calc(real32_T ref_temp,real32_T fdb_temp,real32_T* out_temp,SPEED_PID_DEF* current_pid_temp);

extern real32_T SPEED_PI_I;
extern real32_T SPEED_PI_KB;
extern real32_T SPEED_PI_LOW_LIMIT;
extern real32_T SPEED_PI_P;
extern real32_T SPEED_PI_UP_LIMIT;


#endif                            
