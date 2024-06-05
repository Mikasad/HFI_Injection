/**********************************
������
��Ƶ�̳����QQ�ռ��Bվ
�����������readme.txt
QQ��1323279545
΢�ţ�huiqudong
������www.huiqudong.cn
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
���ܣ�Clark�任
�βΣ���������Լ�alpha_beta����
˵���������໥��120�ȱ任�����໥��90��
***************************************/
void Clarke_Transf(CURRENT_ABC_DEF Current_abc_temp,CURRENT_ALPHA_BETA_DEF* Current_alpha_beta_temp)
{
  Current_alpha_beta_temp->Ialpha = (Current_abc_temp.Ia - (Current_abc_temp.Ib + Current_abc_temp.Ic) * 0.5F) * 2.0F / 3.0F;
  Current_alpha_beta_temp->Ibeta = (Current_abc_temp.Ib - Current_abc_temp.Ic) * 0.866025388F * 2.0F / 3.0F;
}
/***************************************
���ܣ�SVPWM����
�βΣ�alpha_beta��ѹ�Լ�ĸ�ߵ�ѹ����ʱ������
˵��������alpha_beta��ѹ��������ռ�ձ�
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
���ܣ�COS_SINֵ����
�βΣ��Ƕ��Լ�COS_SIN�ṹ��
˵����COS_SINֵ����
***************************************/
void Angle_To_Cos_Sin(real32_T angle_temp,TRANSF_COS_SIN_DEF* cos_sin_temp)
{
  cos_sin_temp->Cos = arm_cos_f32(angle_temp);
  cos_sin_temp->Sin = arm_sin_f32(angle_temp);
}
/***************************************
���ܣ�PARK�任
�βΣ�alpha_beta������COS_SINֵ��DQ�����
˵����������ֱ��
***************************************/
void Park_Transf(CURRENT_ALPHA_BETA_DEF current_alpha_beta_temp,TRANSF_COS_SIN_DEF cos_sin_temp,CURRENT_DQ_DEF* current_dq_temp)
{
  current_dq_temp->Id = current_alpha_beta_temp.Ialpha * cos_sin_temp.Cos + current_alpha_beta_temp.Ibeta * cos_sin_temp.Sin;
  current_dq_temp->Iq = -current_alpha_beta_temp.Ialpha * cos_sin_temp.Sin + current_alpha_beta_temp.Ibeta * cos_sin_temp.Cos;
}
/***************************************
���ܣ���PARK�任
�βΣ�DQ���ѹ��COS_SINֵ��alpha_beta��ѹ
˵����ֱ���佻��
***************************************/
void Rev_Park_Transf(VOLTAGE_DQ_DEF v_dq_temp,TRANSF_COS_SIN_DEF cos_sin_temp,VOLTAGE_ALPHA_BETA_DEF* v_alpha_beta_temp)
{
  v_alpha_beta_temp->Valpha = cos_sin_temp.Cos * v_dq_temp.Vd - cos_sin_temp.Sin * v_dq_temp.Vq;
  v_alpha_beta_temp->Vbeta  = cos_sin_temp.Sin * v_dq_temp.Vd + cos_sin_temp.Cos * v_dq_temp.Vq;
}

/***************************************
���ܣ�������PID
�βΣ������ο���������������ѹ�����PID�ṹ��
˵�������ݵ������ȥ���ڵ������
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
  
  Current_Iabc.Ia = FOC_Input.ia;         //���������ֵ
  Current_Iabc.Ib = FOC_Input.ib;
  Current_Iabc.Ic = FOC_Input.ic;
//  FOC_Input.Iq_ref=40;
  
  Clarke_Transf(Current_Iabc,&Current_Ialpha_beta);        //CLARK �任
  Angle_To_Cos_Sin(FOC_Input.theta,&Transf_Cos_Sin);     //�ɽǶȼ��� park�任�� ��park�任�� COS SINֵ
  Park_Transf(Current_Ialpha_beta,Transf_Cos_Sin,&Current_Idq);  //Park�任����Ialpha Ibeta ��Ƕ���Ϣ��ȥ����Id Iq  // �ɽ�����Ϣת��Ϊֱ����Ϣ������PID���� 
  
  if(hfi_to_flux_ob_flag == 0)
  {
    HFI_Process(Current_Idq,&Current_Lpf_Idq,&HFI_Par);
    d_direction_process(Current_Idq.Id,&d_direction_flag);
    Current_PID_Calc(FOC_Input.Id_ref,Current_Lpf_Idq.Id,&Voltage_DQ.Vd,&Current_D_PID);     //D�������PID  ���ݵ����ο����������ȥ���� �����ѹ
    Current_PID_Calc(FOC_Input.Iq_ref,Current_Lpf_Idq.Iq,&Voltage_DQ.Vq,&Current_Q_PID);     //Q�������PID  ���ݵ����ο����������ȥ���� �����ѹ
    Voltage_DQ.Vd += HFI_Par.hfi_inj_volt;
  }
  else
  {
    Current_PID_Calc(FOC_Input.Id_ref,Current_Idq.Id,&Voltage_DQ.Vd,&Current_D_PID);     //D�������PID  ���ݵ����ο����������ȥ���� �����ѹ
    Current_PID_Calc(FOC_Input.Iq_ref,Current_Idq.Iq,&Voltage_DQ.Vq,&Current_Q_PID);     //Q�������PID  ���ݵ����ο����������ȥ���� �����ѹ
  }
  Rev_Park_Transf(Voltage_DQ,Transf_Cos_Sin,&Voltage_Alpha_Beta);                //��park�任  ͨ���������õ���dq���ѹ��Ϣ��ϽǶ���Ϣ��ȥ��ֱ����Ϣת��Ϊ������Ϣ����SVPWM������
  
  flux_observer_Outputs_wrapper(Current_Ialpha_beta,Voltage_Alpha_Beta,&Flux_Observer);
  IIR_Butterworth(Flux_Observer.we,&Flux_Observer.lpf_we,&WE_IIR_LPF_Par);
  
  SVPWM_Calc(Voltage_Alpha_Beta,FOC_Input.Udc,FOC_Input.Tpwm);       //SVPWM ����ģ��
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
  //������PID ���� ��ʼ��
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
  
  speed_pid_initialize();  //�ٶȻ�PID ���� ��ʼ��
  
  
  
  
  
  HFI_Init(&HFI_Par); 
  Flux_Observer_Init(&Flux_Observer);
  
//  L_identification_Start_wrapper(&FOC_Interface_states.L_Ident_States);//�����в���ʶ���㷨 ������ʼ��
//  
//  R_flux_identification_Start_wrapper(&FOC_Interface_states.R_flux_Ident_States);//����������������ʶ���㷨 ������ʼ��
  
  //״̬������ʼ��
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

