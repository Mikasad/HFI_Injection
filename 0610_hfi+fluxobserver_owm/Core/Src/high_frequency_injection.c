/**********************************
             慧驱动
        视频教程详见QQ空间或B站
        其他事宜详见readme.txt
          QQ：1323279545
         微信：huiqudong
        官网：www.huiqudong.cn
**********************************/
#include "main.h"
#include "high_frequency_injection.h"

IIR_BUTTERWORTH_DEF WE_IIR_LPF_Par;
IIR_BUTTERWORTH_DEF D_IIR_LPF_Par;
IIR_BUTTERWORTH_DEF Q_IIR_LPF_Par;
IIR_BUTTERWORTH_DEF Q_IIR_BPF_Par;
IIR_BUTTERWORTH_DEF ERR_IIR_LPF_Par;
HFI_DEF HFI_Par;
HFI_PID_DEF HFI_PID;

int hfi_cnt;
float HFI_inj_volt_amp;
float HFI_inj_volt_amp_temp;
float hfi_integrator;
uint8_t HFI_inj_volt_amp_ok;
uint16_t HFI_inj_volt_amp_ok_cnt;
uint8_t d_direction_ok;
uint8_t id_index;
float id_max;
float id_min;
uint16_t d_direction_ok_cnt1;
uint16_t d_direction_ok_cnt2;
uint8_t d_direction_flag;

u16 hfi_to_flux_cnt;
void IIR_Butterworth_Coefficient_Init(float temp[8],IIR_BUTTERWORTH_DEF* iir_butterworth_temp)
{
  iir_butterworth_temp->b0 = temp[0];
  iir_butterworth_temp->b1 = temp[1];
  iir_butterworth_temp->b2 = temp[2];
  iir_butterworth_temp->a0 = temp[3];
  iir_butterworth_temp->a1 = temp[4];
  iir_butterworth_temp->a2 = temp[5];
  iir_butterworth_temp->gain0 = temp[6];
  iir_butterworth_temp->gain1 = temp[7];
  iir_butterworth_temp->states0 = 0.0f;
  iir_butterworth_temp->states1 = 0.0f;
}

void IIR_Butterworth(float in,float* out,IIR_BUTTERWORTH_DEF* iir_butterworth_temp)
{
  float temp;
  temp =(iir_butterworth_temp->gain0 * in
         -iir_butterworth_temp->a1 * iir_butterworth_temp->states0)
    -iir_butterworth_temp->a2 * iir_butterworth_temp->states1;
  *out = ((iir_butterworth_temp->b0 * temp + iir_butterworth_temp->b1 * iir_butterworth_temp->states0) +
          iir_butterworth_temp->b2 * iir_butterworth_temp->states1)*iir_butterworth_temp->gain1;
  
  iir_butterworth_temp->states1 = iir_butterworth_temp->states0;
  iir_butterworth_temp->states0 = temp;
}

void HFI_Init(HFI_DEF* hfi_temp)
{
	float WE_IIR_LPF_Coeff[8]={1.0f,1.0f,0.0f,1.0f,-0.969067417193793301f,0.0f,0.0154662914031034,1.0f};   //低通滤波器，截止频率50hz，50hz以上的会被滤掉
  float D_IIR_LPF_Coeff[8]={1.0f,1.0f,0.0f,1.0f,-0.969067417193793301f,0.0f,0.0154662914031034,1.0f};
  float Q_IIR_LPF_Coeff[8]={1.0f,1.0f,0.0f,1.0f,-0.969067417193793301f,0.0f,0.0154662914031034,1.0f};
  float Q_IIR_BPF_Coeff[8]={1.0f,0.0f,-1.0f,1.0f,-1.867249996121f,0.96299405095f,0.018502974524892f,1.0f};  //带通滤波器，截止频率最低470，截止最高频率530，过滤出500hz
  float ERR_IIR_LPF_Coeff[8]={1.0f,1.0f,0.0f,1.0f,-0.969067417193793301f,0.0f,0.0154662914031034,1.0f};
	IIR_Butterworth_Coefficient_Init(WE_IIR_LPF_Coeff,&WE_IIR_LPF_Par);	
  IIR_Butterworth_Coefficient_Init(D_IIR_LPF_Coeff,&D_IIR_LPF_Par);	
  IIR_Butterworth_Coefficient_Init(Q_IIR_LPF_Coeff,&Q_IIR_LPF_Par);	
  IIR_Butterworth_Coefficient_Init(Q_IIR_BPF_Coeff,&Q_IIR_BPF_Par);	
  IIR_Butterworth_Coefficient_Init(ERR_IIR_LPF_Coeff,&ERR_IIR_LPF_Par);
  hfi_cnt = 0;
  HFI_inj_volt_amp = 10.0f;
  HFI_inj_volt_amp_temp = 0.0f;
  HFI_PID.P_Gain = 300.0f;   //50     210
  HFI_PID.I_Gain = 2500.0f;  //500    2500
  HFI_PID.I_Sum = 0.0f;
  hfi_temp->hfi_theta = 0.0f;
  hfi_integrator = 0.0f;
}


//float q_current_bpf;
void HFI_Process(CURRENT_DQ_DEF current_dq_temp,CURRENT_DQ_DEF* current_dq_lpf,HFI_DEF* hfi_temp)
{
  float hfi_cos;
  float hfi_sin;
  float temp1;
  float temp2;
  float q_current_bpf;
  float hfi_pid_error;
  float hfi_pid_out;
  if(hfi_cnt >= HFI_CNT_FLAG)
  {
    hfi_cnt = 0;
  }
  temp1 = hfi_cnt;
  temp2 = HFI_CNT_FLAG;
  hfi_cos = arm_cos_f32((temp1/temp2)*2.0f*PI);
  hfi_sin = arm_sin_f32((temp1/temp2)*2.0f*PI);
  if(HFI_inj_volt_amp_ok == 0)
  {
    if(HFI_inj_volt_amp_temp<HFI_inj_volt_amp)
    {
      HFI_inj_volt_amp_temp += 0.001f;
    }
    else
    {
      if(HFI_inj_volt_amp_ok_cnt>1000)
      {
        HFI_inj_volt_amp_ok = 1;
      }
      HFI_inj_volt_amp_ok_cnt++;
    }
  }
//   hfi_temp->hfi_inj_volt = hfi_cos * HFI_inj_volt_amp;  //Vd注入8*cos500t
  hfi_temp->hfi_inj_volt = hfi_cos * HFI_inj_volt_amp_temp;
  hfi_cnt++;
  IIR_Butterworth(current_dq_temp.Id,&current_dq_lpf->Id,&D_IIR_LPF_Par);     
  IIR_Butterworth(current_dq_temp.Iq,&current_dq_lpf->Iq,&Q_IIR_LPF_Par);
  IIR_Butterworth(current_dq_temp.Iq,&q_current_bpf,&Q_IIR_BPF_Par);  //带通滤波器，截止频率470-530hz
  temp1 = q_current_bpf * hfi_sin;   //叠加频率为500的sin波
  IIR_Butterworth(temp1,&hfi_pid_error,&ERR_IIR_LPF_Par);
//  
  hfi_pid_out = HFI_PID.P_Gain * hfi_pid_error + HFI_PID.I_Sum;
//  
//  
  hfi_temp->hfi_theta = hfi_integrator;   //先赋值角度，要不然会有一个角度差
  hfi_temp->hfi_we = hfi_pid_out;         //PID出来的就是角速度
  hfi_integrator += FOC_PERIOD * hfi_pid_out;  //对角速度进行积分得到角度
  
  if(hfi_integrator < 0.0f)
  {
    hfi_integrator += 2.0f*PI;
  }
  else if(hfi_integrator > (2.0f*PI))
  {
    hfi_integrator -= 2.0f*PI;
  }
  HFI_PID.I_Sum += (HFI_PID.I_Gain * hfi_pid_error) * FOC_PERIOD;   //Pi积分项输出
}

float id_max_1=0.0;
float id_min_1=0.0;
void d_direction_process(float in_temp,uint8_t* out_temp)
{
  if(HFI_inj_volt_amp_ok == 1)
  {
    if(d_direction_ok == 0)
    {
      if(id_index<20)   //500hz对应一个周期20个点
      {
        if(in_temp>id_max)
        {
          id_max = in_temp;
        }
        if(in_temp<id_min)
        {
          id_min = in_temp;
        }
        id_index++;
      }
      else
      {
		  id_max_1=id_max;
		  id_min_1=id_min;
        if(id_max>(-id_min))
        {
          *out_temp = 1;
          if(d_direction_ok_cnt1>10)
          {
            d_direction_ok = 1;
          }
          d_direction_ok_cnt1++;
        }
        else
        {
          if(d_direction_ok_cnt2>200)
          {
            hfi_integrator = hfi_integrator - PI;
            d_direction_ok_cnt2 = 0;
          }
          d_direction_ok_cnt2++;
          *out_temp = 2;
        }
        id_max = 0.0f;
        id_min = 0.0f;
        id_index = 0;
      }
    }
  }
}



