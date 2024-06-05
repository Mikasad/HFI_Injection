/**********************************
慧驱动
视频教程详见QQ空间或B站
其他事宜详见readme.txt
QQ：1323279545
微信：huiqudong
官网：www.huiqudong.cn
**********************************/
#include "main.h"
#include "foc_algorithm.h"
#include "high_frequency_injection.h"

//real32_T D_PI_I = 1282.8F;
//real32_T D_PI_KB = 15.0F;
//real32_T D_PI_LOW_LIMIT = -24.0F;
//real32_T D_PI_P = 2.199F;
//real32_T D_PI_UP_LIMIT = 24.0F;
//real32_T Q_PI_I = 1282.8F;
//real32_T Q_PI_KB = 15.0F;
//real32_T Q_PI_LOW_LIMIT = -24.0F;
//real32_T Q_PI_P = 2.199F;
//real32_T Q_PI_UP_LIMIT = 24.0F;

real32_T D_PI_I = 800.8F;
real32_T D_PI_KB = 15.0F;
real32_T D_PI_LOW_LIMIT = -24.0F;
real32_T D_PI_P = 3.199F;
real32_T D_PI_UP_LIMIT = 24.0F;
real32_T Q_PI_I = 800.8F;
real32_T Q_PI_KB = 15.0F;
real32_T Q_PI_LOW_LIMIT = -24.0F;
real32_T Q_PI_P = 3.599F;
real32_T Q_PI_UP_LIMIT = 24.0F;

FOC_INTERFACE_STATES_DEF FOC_Interface_states;


FOC_INPUT_DEF FOC_Input;


FOC_OUTPUT_DEF FOC_Output;


//RT_MODEL rtM_;
//RT_MODEL *const rtM = &rtM_;

#ifdef __cplusplus

extern "C" {
  
#endif
  
  extern void stm32_ekf_Start_wrapper(real_T *xD);
  extern void stm32_ekf_Outputs_wrapper(const real32_T *u,
                                        real32_T *y,
                                        const real_T *xD);
  extern void stm32_ekf_Update_wrapper(const real32_T *u,
                                       real32_T *y,
                                       real_T *xD);
  extern void stm32_ekf_Terminate_wrapper(real_T *xD);
  
#ifdef __cplusplus
  
}
#endif

#ifdef __cplusplus

extern "C" {
  
#endif
  
  extern void L_identification_Start_wrapper(real_T *xD);
  extern void L_identification_Outputs_wrapper(const real32_T *u,
                                               real32_T *y,
                                               const real_T *xD);
  extern void L_identification_Update_wrapper(const real32_T *u,
                                              real32_T *y,
                                              real_T *xD);
  extern void L_identification_Terminate_wrapper(real_T *xD);
  
#ifdef __cplusplus
  
}
#endif

#ifdef __cplusplus

extern "C" {
  
#endif
  
  extern void R_flux_identification_Start_wrapper(real_T *xD);
  extern void R_flux_identification_Outputs_wrapper(const real32_T *u,
                                                    real32_T *y,
                                                    const real_T *xD);
  extern void R_flux_identification_Update_wrapper(const real32_T *u,
                                                   real32_T *y,
                                                   real_T *xD);
  extern void R_flux_identification_Terminate_wrapper(real_T *xD);
  
#ifdef __cplusplus
  
}
#endif

extern float float_test1;
extern float float_test2;

CURRENT_ABC_DEF Current_Iabc;
CURRENT_ALPHA_BETA_DEF Current_Ialpha_beta;
VOLTAGE_ALPHA_BETA_DEF Voltage_Alpha_Beta;
TRANSF_COS_SIN_DEF Transf_Cos_Sin;
CURRENT_DQ_DEF Current_Idq; 
CURRENT_DQ_DEF Current_Lpf_Idq;
VOLTAGE_DQ_DEF Voltage_DQ;
CURRENT_PID_DEF Current_D_PID;
CURRENT_PID_DEF Current_Q_PID;

/***************************************
功能：Clark变换
形参：三相电流以及alpha_beta电流
说明：由三相互差120度变换到两相互差90度
***************************************/
void Clarke_Transf(CURRENT_ABC_DEF Current_abc_temp,CURRENT_ALPHA_BETA_DEF* Current_alpha_beta_temp)
{
  Current_alpha_beta_temp->Ialpha = (Current_abc_temp.Ia - (Current_abc_temp.Ib + Current_abc_temp.Ic) * 0.5F) * 2.0F / 3.0F;
  Current_alpha_beta_temp->Ibeta = (Current_abc_temp.Ib - Current_abc_temp.Ic) * 0.866025388F * 2.0F / 3.0F;
}
/***************************************
功能：SVPWM计算
形参：alpha_beta电压以及母线电压、定时器周期
说明：根据alpha_beta电压计算三相占空比
***************************************/
void SVPWM_Calc(VOLTAGE_ALPHA_BETA_DEF v_alpha_beta_temp,real32_T Udc_temp,real32_T Tpwm_temp)
{
  int32_T sector;
  real32_T Tcmp1,Tcmp2,Tcmp3,Tx,Ty,f_temp,Ta,Tb,Tc;
  sector = 0;
  Tcmp1 = 0.0F;
  Tcmp2 = 0.0F;
  Tcmp3 = 0.0F;
  if (v_alpha_beta_temp.Vbeta > 0.0F) {
    sector = 1;
  }
  
  if ((1.73205078F * v_alpha_beta_temp.Valpha - v_alpha_beta_temp.Vbeta) / 2.0F > 0.0F) {
    sector += 2;
  }
  
  if ((-1.73205078F * v_alpha_beta_temp.Valpha - v_alpha_beta_temp.Vbeta) / 2.0F > 0.0F) {
    sector += 4;
  }
  
  switch (sector) {
  case 1:
    Tx = (-1.5F * v_alpha_beta_temp.Valpha + 0.866025388F * v_alpha_beta_temp.Vbeta) * (Tpwm_temp / Udc_temp);
    Ty = (1.5F * v_alpha_beta_temp.Valpha + 0.866025388F * v_alpha_beta_temp.Vbeta) * (Tpwm_temp / Udc_temp);
    break;
    
  case 2:
    Tx = (1.5F * v_alpha_beta_temp.Valpha + 0.866025388F * v_alpha_beta_temp.Vbeta) * (Tpwm_temp / Udc_temp);
    Ty = -(1.73205078F * v_alpha_beta_temp.Vbeta * Tpwm_temp / Udc_temp);
    break;
    
  case 3:
    Tx = -((-1.5F * v_alpha_beta_temp.Valpha + 0.866025388F * v_alpha_beta_temp.Vbeta) * (Tpwm_temp / Udc_temp));
    Ty = 1.73205078F * v_alpha_beta_temp.Vbeta * Tpwm_temp / Udc_temp;
    break;
    
  case 4:
    Tx = -(1.73205078F * v_alpha_beta_temp.Vbeta * Tpwm_temp / Udc_temp);
    Ty = (-1.5F * v_alpha_beta_temp.Valpha + 0.866025388F * v_alpha_beta_temp.Vbeta) * (Tpwm_temp / Udc_temp);
    break;
    
  case 5:
    Tx = 1.73205078F * v_alpha_beta_temp.Vbeta * Tpwm_temp / Udc_temp;
    Ty = -((1.5F * v_alpha_beta_temp.Valpha + 0.866025388F * v_alpha_beta_temp.Vbeta) * (Tpwm_temp / Udc_temp));
    break;
    
  default:
    Tx = -((1.5F * v_alpha_beta_temp.Valpha + 0.866025388F * v_alpha_beta_temp.Vbeta) * (Tpwm_temp / Udc_temp));
    Ty = -((-1.5F * v_alpha_beta_temp.Valpha + 0.866025388F * v_alpha_beta_temp.Vbeta) * (Tpwm_temp / Udc_temp));
    break;
  }
  
  f_temp = Tx + Ty;
  if (f_temp > Tpwm_temp) {
    Tx = Tx/f_temp*Tpwm_temp;
    Ty = Ty/f_temp*Tpwm_temp;
  }
  
  Ta = (Tpwm_temp - (Tx + Ty)) / 4.0F;
  Tb = Tx / 2.0F + Ta;
  Tc = Ty / 2.0F + Tb;
  switch (sector) {
  case 1:
    Tcmp1 = Tb;
    Tcmp2 = Ta;
    Tcmp3 = Tc;
    break;
    
  case 2:
    Tcmp1 = Ta;
    Tcmp2 = Tc;
    Tcmp3 = Tb;
    break;
    
  case 3:
    Tcmp1 = Ta;
    Tcmp2 = Tb;
    Tcmp3 = Tc;
    break;
    
  case 4:
    Tcmp1 = Tc;
    Tcmp2 = Tb;
    Tcmp3 = Ta;
    break;
    
  case 5:
    Tcmp1 = Tc;
    Tcmp2 = Ta;
    Tcmp3 = Tb;
    break;
    
  case 6:
    Tcmp1 = Tb;
    Tcmp2 = Tc;
    Tcmp3 = Ta;
    break;
  }
  
  FOC_Output.Tcmp1 = Tcmp1;
  FOC_Output.Tcmp2 = Tcmp2;
  FOC_Output.Tcmp3 = Tcmp3;
}

/***************************************
功能：COS_SIN值计算
形参：角度以及COS_SIN结构体
说明：COS_SIN值计算
***************************************/
void Angle_To_Cos_Sin(real32_T angle_temp,TRANSF_COS_SIN_DEF* cos_sin_temp)
{
  cos_sin_temp->Cos = arm_cos_f32(angle_temp);
  cos_sin_temp->Sin = arm_sin_f32(angle_temp);
}
/***************************************
功能：PARK变换
形参：alpha_beta电流、COS_SIN值、DQ轴电流
说明：交流变直流
***************************************/
void Park_Transf(CURRENT_ALPHA_BETA_DEF current_alpha_beta_temp,TRANSF_COS_SIN_DEF cos_sin_temp,CURRENT_DQ_DEF* current_dq_temp)
{
  current_dq_temp->Id = current_alpha_beta_temp.Ialpha * cos_sin_temp.Cos + current_alpha_beta_temp.Ibeta * cos_sin_temp.Sin;
  current_dq_temp->Iq = -current_alpha_beta_temp.Ialpha * cos_sin_temp.Sin + current_alpha_beta_temp.Ibeta * cos_sin_temp.Cos;
}
/***************************************
功能：反PARK变换
形参：DQ轴电压、COS_SIN值、alpha_beta电压
说明：直流变交流
***************************************/
void Rev_Park_Transf(VOLTAGE_DQ_DEF v_dq_temp,TRANSF_COS_SIN_DEF cos_sin_temp,VOLTAGE_ALPHA_BETA_DEF* v_alpha_beta_temp)
{
  v_alpha_beta_temp->Valpha = cos_sin_temp.Cos * v_dq_temp.Vd - cos_sin_temp.Sin * v_dq_temp.Vq;
  v_alpha_beta_temp->Vbeta  = cos_sin_temp.Sin * v_dq_temp.Vd + cos_sin_temp.Cos * v_dq_temp.Vq;
}

/***************************************
功能：电流环PID
形参：电流参考、电流反馈、电压输出、PID结构体
说明：根据电流误差去调节电流输出
***************************************/
void Current_PID_Calc(real32_T ref_temp,real32_T fdb_temp,real32_T* out_temp,CURRENT_PID_DEF* current_pid_temp)
{
  real32_T error;
  real32_T temp;
  error = ref_temp - fdb_temp;
  temp = current_pid_temp->P_Gain * error + current_pid_temp->I_Sum;
  if (temp > current_pid_temp->Max_Output) 
  {
    *out_temp = current_pid_temp->Max_Output;
  } 
  else if (temp < current_pid_temp->Min_Output) 
  {
    *out_temp = current_pid_temp->Min_Output;
  } 
  else 
  {
    *out_temp = temp;
  }
  current_pid_temp->I_Sum += ((*out_temp - temp) * current_pid_temp->B_Gain + current_pid_temp->I_Gain * error) *FOC_PERIOD;
}


extern uint8_t hfi_to_flux_ob_flag;
u16 temp1=0;
u16 temp2=0;
float angle_20hz;
float angle_500hz;
float sin_20hz;
float sin_500hz;
float sin_20_500hz;
float lpf_out;
float bpf_out;
void foc_algorithm_step(void)
{
  
  Current_Iabc.Ia = FOC_Input.ia;         //三相电流赋值
  Current_Iabc.Ib = FOC_Input.ib;
  Current_Iabc.Ic = FOC_Input.ic;
//  FOC_Input.Iq_ref=40;
  
  Clarke_Transf(Current_Iabc,&Current_Ialpha_beta);        //CLARK 变换
  Angle_To_Cos_Sin(FOC_Input.theta,&Transf_Cos_Sin);     //由角度计算 park变换和 反park变换的 COS SIN值
  Park_Transf(Current_Ialpha_beta,Transf_Cos_Sin,&Current_Idq);  //Park变换，由Ialpha Ibeta 与角度信息，去计算Id Iq  // 由交流信息转化为直流信息，方便PID控制 
  
  if(hfi_to_flux_ob_flag == 0)
  {
    HFI_Process(Current_Idq,&Current_Lpf_Idq,&HFI_Par);
    d_direction_process(Current_Idq.Id,&d_direction_flag);
    Current_PID_Calc(FOC_Input.Id_ref,Current_Lpf_Idq.Id,&Voltage_DQ.Vd,&Current_D_PID);     //D轴电流环PID  根据电流参考与电流反馈去计算 输出电压
    Current_PID_Calc(FOC_Input.Iq_ref,Current_Lpf_Idq.Iq,&Voltage_DQ.Vq,&Current_Q_PID);     //Q轴电流环PID  根据电流参考与电流反馈去计算 输出电压
    Voltage_DQ.Vd += HFI_Par.hfi_inj_volt;
  }
  else
  {
    Current_PID_Calc(FOC_Input.Id_ref,Current_Idq.Id,&Voltage_DQ.Vd,&Current_D_PID);     //D轴电流环PID  根据电流参考与电流反馈去计算 输出电压
    Current_PID_Calc(FOC_Input.Iq_ref,Current_Idq.Iq,&Voltage_DQ.Vq,&Current_Q_PID);     //Q轴电流环PID  根据电流参考与电流反馈去计算 输出电压
  }
  Rev_Park_Transf(Voltage_DQ,Transf_Cos_Sin,&Voltage_Alpha_Beta);                //反park变换  通过电流环得到的dq轴电压信息结合角度信息，去把直流信息转化为交流信息用于SVPWM的输入
  
  flux_observer_Outputs_wrapper(Current_Ialpha_beta,Voltage_Alpha_Beta,&Flux_Observer);
  IIR_Butterworth(Flux_Observer.we,&Flux_Observer.lpf_we,&WE_IIR_LPF_Par);
  
  SVPWM_Calc(Voltage_Alpha_Beta,FOC_Input.Udc,FOC_Input.Tpwm);       //SVPWM 计算模块
//  temp1++;
//  temp2++;
//  if(temp1 >=10000/20)
//  {
//	  temp1=0;
//  }
//  angle_20hz =(float)(temp1)/(500.0f)*2.0*PI;
//  if(temp2 >=10000/500)
//  {
//	  temp2=0;
//  }
//  angle_500hz =(float)(temp1)/(20.0f)*2.0*PI;
//  
//  sin_20hz=arm_sin_f32(angle_20hz);
//  sin_500hz=arm_sin_f32(angle_500hz);
//  sin_20_500hz=sin_20hz+sin_500hz;
//  IIR_Butterworth(sin_20_500hz,&lpf_out,&D_IIR_LPF_Par);
//  IIR_Butterworth(sin_20_500hz,&bpf_out,&Q_IIR_BPF_Par);
  
}


void foc_algorithm_initialize(void)
{
  //电流环PID 参数 初始化
  {
    Current_D_PID.P_Gain = D_PI_P;
    Current_D_PID.I_Gain = D_PI_I;
    Current_D_PID.B_Gain = D_PI_KB;
    Current_D_PID.Max_Output = D_PI_UP_LIMIT;
    Current_D_PID.Min_Output = D_PI_LOW_LIMIT;
    Current_D_PID.I_Sum = 0.0f;
    
    Current_Q_PID.P_Gain = Q_PI_P;
    Current_Q_PID.I_Gain = Q_PI_I;
    Current_Q_PID.B_Gain = Q_PI_KB;
    Current_Q_PID.Max_Output = Q_PI_UP_LIMIT;
    Current_Q_PID.Min_Output = Q_PI_LOW_LIMIT;
    Current_Q_PID.I_Sum = 0.0f;
  }
  FOC_Input.Tpwm = PWM_TIM_PULSE_TPWM;
  
  speed_pid_initialize();  //速度环PID 参数 初始化
  
  
  
  
  
  HFI_Init(&HFI_Par); 
  Flux_Observer_Init(&Flux_Observer);
  
//  L_identification_Start_wrapper(&FOC_Interface_states.L_Ident_States);//电机电感参数识别算法 参数初始化
//  
//  R_flux_identification_Start_wrapper(&FOC_Interface_states.R_flux_Ident_States);//电机电阻与磁链参数识别算法 参数初始化
  
  //状态变量初始化
  {
    real_T initVector[4] = { 0, 0, 0, 0 };
    
    {
      int_T i1;
      real_T *dw_DSTATE = &FOC_Interface_states.EKF_States[0];
      for (i1=0; i1 < 4; i1++) {
        dw_DSTATE[i1] = initVector[i1];
      }
    }
  }
  
  {
    real_T initVector[1] = { 0 };
    
    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        FOC_Interface_states.L_Ident_States = initVector[0];
      }
    }
  }
  
  
  {
    real_T initVector[1] = { 0 };
    
    {
      int_T i1;
      for (i1=0; i1 < 1; i1++) {
        FOC_Interface_states.R_flux_Ident_States = initVector[0];
      }
    }
  }
  
  
}

