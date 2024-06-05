/**********************************
             慧驱动
        视频教程详见QQ空间或B站
        其他事宜详见readme.txt
          QQ：1323279545
         微信：huiqudong
        官网：www.huiqudong.cn
**********************************/
#ifndef __HIGH_FREQUENCY_INJECTION_H_
#define __HIGH_FREQUENCY_INJECTION_H_
#define FOC_PERIOD          0.0001F
#define FOC_FREQ            PWM_TIM_FREQ
#define HFI_INJ_FREQ 500
#define HFI_CNT_FLAG FOC_FREQ/HFI_INJ_FREQ

#define HFI_TO_FLUX_UP_HZ       15.0f
#define HFI_TO_FLUX_DOWN_HZ     12.0f
#define HFI_TO_FLUX_UP_FLAG     HFI_TO_FLUX_UP_HZ*2.0f*PI
#define HFI_TO_FLUX_DOWN_FLAG   HFI_TO_FLUX_DOWN_HZ*2.0f*PI
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef struct
{
	float states0;
	float states1;
	float b0;
	float b1;
	float b2;
	float a0;
	float a1;
	float a2;
	float gain0;
	float gain1;
}IIR_BUTTERWORTH_DEF;

typedef struct
{
	float hfi_theta;
	float hfi_we;
	float hfi_inj_volt;
}HFI_DEF;

typedef struct
{
  float P_Gain;
  float I_Gain;
  float D_Gain;
  float Max_Output;
  float Min_Output;
  float I_Sum;
}HFI_PID_DEF;
extern uint8_t d_direction_ok;
extern uint8_t d_direction_flag;
extern HFI_DEF HFI_Par;
extern u16 hfi_to_flux_cnt;
extern void HFI_Init(HFI_DEF* hfi_temp);
extern void IIR_Butterworth(float in,float* out,IIR_BUTTERWORTH_DEF* iir_butterworth_temp);
extern void HFI_Process(CURRENT_DQ_DEF current_dq_temp,CURRENT_DQ_DEF* current_dq_lpf,HFI_DEF* hfi_temp);
extern void d_direction_process(float in_temp,uint8_t* out_temp);
extern IIR_BUTTERWORTH_DEF D_IIR_LPF_Par;
extern IIR_BUTTERWORTH_DEF Q_IIR_BPF_Par;
extern IIR_BUTTERWORTH_DEF WE_IIR_LPF_Par;
#endif
