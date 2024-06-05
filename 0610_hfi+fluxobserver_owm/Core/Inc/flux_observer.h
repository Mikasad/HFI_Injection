/**********************************
             慧驱动
        视频教程详见QQ空间或B站
        其他事宜详见readme.txt
          QQ：1323279545
         微信：huiqudong
        官网：www.huiqudong.cn
**********************************/
#ifndef __FLUX_OBSERVER_H_
#define __FLUX_OBSERVER_H_

#define SPEED_CLOSE_HZ     50.0f
#define SPEED_CLOSE_FLAG   SPEED_CLOSE_HZ*2.0f*PI

typedef struct
{
  float theta;
  float we;
  float lpf_we;
}FLUX_OBSERVER_DEF;

extern FLUX_OBSERVER_DEF Flux_Observer;
extern void Flux_Observer_Init(FLUX_OBSERVER_DEF* flux_observer);
extern void flux_observer_Outputs_wrapper(CURRENT_ALPHA_BETA_DEF Current_alpha_beta
                                   ,VOLTAGE_ALPHA_BETA_DEF v_alpha_beta
                                     ,FLUX_OBSERVER_DEF* flux_observer);

typedef struct 
{
  real32_T PLLKI;                     /* Referenced by: '<S52>/Integral Gain' */
  real32_T PLLKP;                 /* Referenced by: '<S60>/Proportional Gain' */
} FLUX_PLL_type;
#endif
