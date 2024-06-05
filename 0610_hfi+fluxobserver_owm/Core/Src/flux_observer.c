/**********************************
             慧驱动
        视频教程详见QQ空间或B站
        其他事宜详见readme.txt
          QQ：1323279545
         微信：huiqudong
        官网：www.huiqudong.cn
**********************************/
#include "main.h"
#include "flux_observer.h"



//#include <math.h>


#define Rs 6.97F
#define Ld 0.00535F
#define Motor_Flux 0.008442F
#define Flux_Gramma  10000
FLUX_OBSERVER_DEF Flux_Observer;
FLUX_PLL_type FLUX_PLL = {
  /* PLLKI */
  640000.0F,

  /* PLLKP */
  1131.0F
};


//float Vbeta;

//float Ibeta;
float pre_theta;
float theta_error;
float pre_theta_error;


float alpha_temp;
float beta_temp;
float alpha_int;
float beta_int;
float Beta_psi;
float Beta_psi_pre;
float Alpha_psi;
float Alpha_psi_pre;



float Y1;
float Y2;
float eta_x1;
float eta_x2;
float X1_k;
float X2_k;
float X1_k_1;
float X2_k_1;
void Flux_Observer_Init(FLUX_OBSERVER_DEF* flux_observer)
{
  
  alpha_temp = 0.0f;
  beta_temp = 0.0f;
  alpha_int = 0.0f;
  beta_int = 0.0f;
  Beta_psi_pre = 0.0f;
  Alpha_psi_pre = 0.0f;
  flux_observer->theta = 0.0f;
  pre_theta = 0.0f;
  theta_error = 0.0f;
  flux_observer->we = 0.0f;
  flux_observer->lpf_we = 0.0f;
  pre_theta_error = 0.0f;
  
	
	Y1= 0.0f;
	Y2= 0.0f;
	eta_x1= 0.0f;
	eta_x2= 0.0f;
	X1_k= 0.0f;
	X2_k= 0.0f;
	X1_k_1= 0.0f;
	X2_k_1= 0.0f;
}

//void flux_observer_Outputs_wrapper(CURRENT_ALPHA_BETA_DEF i_alpha_beta
//                                   ,VOLTAGE_ALPHA_BETA_DEF v_alpha_beta
//                                     ,FLUX_OBSERVER_DEF* flux_observer)
//{
//  
//  alpha_int += (v_alpha_beta.Valpha - i_alpha_beta.Ialpha * Rs)*0.0001f;    //
//  alpha_temp = alpha_int - i_alpha_beta.Ialpha * Ld;
//  Alpha_psi = alpha_temp*0.001f + (1.0f - 0.001f)*Alpha_psi_pre;
//  Alpha_psi_pre = Alpha_psi;
//  
//  beta_int += (v_alpha_beta.Vbeta - i_alpha_beta.Ibeta * Rs)*0.0001f;
//  beta_temp = beta_int - i_alpha_beta.Ibeta * Ld;
//  Beta_psi = beta_temp*0.001f + (1.0f - 0.001f)*Beta_psi_pre;
//  Beta_psi_pre = Beta_psi;
//  
//  flux_observer->theta = atan2f(beta_temp - Beta_psi,alpha_temp - Alpha_psi);
//  if(flux_observer->theta<0.0f)
//  {
//    flux_observer->theta+=6.2831853f;  
//  }
//  theta_error = flux_observer->theta - pre_theta;
//  pre_theta = flux_observer->theta;
//  if((theta_error<-1.0f)||(theta_error>1.0f))
//  {
//    theta_error = pre_theta_error;
//  }
//  flux_observer->we = theta_error/0.0001f;
//  pre_theta_error = theta_error;
//  
//}


float fluxpll_integrator;
void flux_observer_Outputs_wrapper(CURRENT_ALPHA_BETA_DEF i_alpha_beta
                                   ,VOLTAGE_ALPHA_BETA_DEF v_alpha_beta
                                     ,FLUX_OBSERVER_DEF* flux_observer)
{
	 real32_T rtb_Plus9;
	 real32_T rtb_Cos_e;
	 real32_T rtb_SignPreIntegrator_j;
	 real32_T flux_pid_error;
	 real32_T rtb_Sum_l;
	 real32_T flux_pid_out;
	  Y1= v_alpha_beta.Valpha - i_alpha_beta.Ialpha * Rs; 
	  Y2= v_alpha_beta.Vbeta - i_alpha_beta.Ibeta * Rs; 
	  eta_x1= X1_k_1-Ld*i_alpha_beta.Ialpha;
	  eta_x2= X2_k_1-Ld*i_alpha_beta.Ibeta;
	  rtb_Plus9 = Motor_Flux * Motor_Flux - (eta_x1*eta_x1 + eta_x2 * eta_x2);                     //flux平方-eta(x)平方    eta(x)平方=eta(x1)平方+eta(x2)平方
	  X1_k = (Y1 + Flux_Gramma * eta_x1 * rtb_Plus9) * 0.0001F +  X1_k_1;                                  //x1(k)=Ts(y1(k-1)+flux*etax1(k-1)*flux平方-eta1(x)平方)+x1(k-1)     y1(k-1)=Ualpha-Rs*iaplha
	  X1_k_1 = X1_k;
	  X2_k = (Y2 + Flux_Gramma * eta_x2 * rtb_Plus9) * 0.0001F +  X2_k_1;         //x2(k)=Ts(y2(k-1)+flux*etax2(k-1)*flux平方-eta2(x)平方)+x2(k-1)    y2(k-1)=Ubta-Rs*ibeta
	  X2_k_1 = X2_k;
	  flux_pid_error = (X2_k - Ld*i_alpha_beta.Ibeta) * (1.0F / Motor_Flux) *cosf(flux_observer->theta) - (X1_k -  Ld*i_alpha_beta.Ialpha) * (1.0F / Motor_Flux) * sinf(flux_observer->theta);  
	   flux_pid_out = FLUX_PLL.PLLKP * flux_pid_error + rtb_Sum_l; 
	  flux_observer->theta = fluxpll_integrator;   //先赋值角度，要不然会有一个角度差
	  flux_observer->we = flux_pid_out;         //PID出来的就是角速度
	  fluxpll_integrator += FOC_PERIOD * flux_pid_out;  //对角速度进行积分得到角度
	  
	  if(fluxpll_integrator < 0.0f)
	  {
		fluxpll_integrator += 2.0f*PI;
	  }
	  else if(fluxpll_integrator > (2.0f*PI))
	  {
		fluxpll_integrator -= 2.0f*PI;
	  }
	  rtb_Sum_l += (FLUX_PLL.PLLKP * flux_pid_error) * FOC_PERIOD;   //Pi积分项输出
	
	
}