/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "comp.h"
#include "dac.h"
#include "dma.h"
#include "fdcan.h"
#include "opamp.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "FOC_Model.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "foc_algorithm.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define PI					3.14159265358979f
#define PHASE_SHIFT_ANGLE (float)(220.0f/360.0f*2.0f*PI)

extern DMA_HandleTypeDef hdma_usart3_tx;
uint8_t DataB1[32] = "LED1 Toggle\r\n";
uint8_t DataB2[32] = "LED2 Toggle\r\n";
uint8_t DataB3[32] = "LED1 and LED2 Open\r\n";

#define RXBUFFERSIZE  256   
char RxBuffer[RXBUFFERSIZE];  
uint8_t aRxBuffer;			   
uint8_t Uart1_Rx_Cnt = 0;	

float load_data[5];
static uint8_t tempData[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x80,0x7F};

uint16_t DAC_temp = 0;
u8 speed_close_loop_flag;
float Vbus,Ia,Ib,Ic;
uint8_t Motor_state = 0;
uint16_t IA_Offset,IB_Offset,IC_Offset;
uint16_t adc1_in1, adc1_in2, adc1_in3, adc1_in4,Vpoten, adc_vbus;
uint8_t ADC_offset = 0;
uint16_t finalspeed = 0;
FDCAN_RxHeaderTypeDef RxHeader;
FDCAN_TxHeaderTypeDef TxHeader;
uint8_t RxData[8]={NULL};
uint8_t TxData[8] = {NULL};

float HallTemp = 0;
float HallThetaAdd = 0;
float HallTheta = 0;
float HallSpeed = 0;
float HallSpeedLast = 0;
float HallSpeedtest = 0;
float alpha = 0.3;
uint8_t HallReadTemp = 0;
static __IO uint32_t uwTimingDelay;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void FDCAN_Config(void);
/* USER CODE END PFP */
uint8_t hfi_to_flux_ob_flag = 0;
float aalpha = 0.3;
/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_OPAMP1_Init();
  MX_OPAMP2_Init();
  MX_OPAMP3_Init();
  MX_TIM1_Init();
  MX_COMP1_Init();
  MX_DAC1_Init();
  MX_DAC3_Init();
  MX_FDCAN1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	HAL_OPAMP_Start(&hopamp1);
	HAL_OPAMP_Start(&hopamp2);
	HAL_OPAMP_Start(&hopamp3);
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer, 1);
	HAL_ADCEx_Calibration_Start( &hadc1, ADC_SINGLE_ENDED);
	HAL_ADCEx_Calibration_Start( &hadc2, ADC_SINGLE_ENDED);
	__HAL_ADC_CLEAR_FLAG( &hadc1, ADC_FLAG_JEOC);
	__HAL_ADC_CLEAR_FLAG( &hadc1, ADC_FLAG_EOC);
	__HAL_ADC_CLEAR_FLAG( &hadc2, ADC_FLAG_JEOC);
	HAL_ADCEx_InjectedStart_IT(&hadc1);
	HAL_ADCEx_InjectedStart(&hadc2);
	TIM1->ARR = 8000 - 1;
	TIM1->CCR4 = 8000 - 2;
	HAL_TIM_Base_Start( &htim1);
	HAL_TIM_PWM_Start( &htim1, TIM_CHANNEL_4);
	HAL_DAC_SetValue(&hdac3,DAC_CHANNEL_1,DAC_ALIGN_12B_R,3000);
	HAL_DAC_Start(&hdac3,DAC_CHANNEL_1);
	HAL_DAC_Start(&hdac1,DAC_CHANNEL_1);
	HAL_COMP_Start (&hcomp1);
	HAL_TIMEx_HallSensor_Start_IT(&htim4);
	FDCAN_Config();
	foc_algorithm_initialize();
//	rtU.SpeedRef=1000;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_ADC_Start(&hadc1);
		HAL_ADC_Start(&hadc2);
		adc1_in4 = HAL_ADC_GetValue(&hadc1);
		adc_vbus = HAL_ADC_GetValue(&hadc2);
		rtU.v_bus = adc_vbus*3.3f/4096*26;
//		finalspeed = (adc1_in4>>4) * 15;
//		if(finalspeed >=0 && finalspeed <300)
//		{
//			finalspeed = 300;
//		}
//		if(finalspeed > 1200)
//		{
//			finalspeed = 1200;
//		}
//		rtU.Speed_ref = finalspeed;
		HAL_Delay(10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void Delay(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;
  
  while(uwTimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV3;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_ADC12
                              |RCC_PERIPHCLK_FDCAN;
  PeriphClkInit.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInit.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(GPIO_Pin);
if(Button3_Pin == GPIO_Pin)
	{
		Motor_state = ~Motor_state;
		if(0 == Motor_state)
		{
			motor_start_stop=0;
			rtU.Motor_OnOff = 0;
			d_direction_flag=0;
			HAL_TIM_PWM_Stop( &htim1, TIM_CHANNEL_1);
			HAL_TIM_PWM_Stop( &htim1, TIM_CHANNEL_2);
			HAL_TIM_PWM_Stop( &htim1, TIM_CHANNEL_3);
			HAL_TIMEx_PWMN_Stop( &htim1, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Stop( &htim1, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Stop( &htim1, TIM_CHANNEL_3);
		}
		else
		{
			motor_start_stop = 1;
			rtU.Motor_OnOff = 1;
			d_direction_ok=0;
			HAL_TIM_PWM_Start( &htim1, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start( &htim1, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start( &htim1, TIM_CHANNEL_3);
			HAL_TIMEx_PWMN_Start( &htim1, TIM_CHANNEL_1);
			HAL_TIMEx_PWMN_Start( &htim1, TIM_CHANNEL_2);
			HAL_TIMEx_PWMN_Start( &htim1, TIM_CHANNEL_3);
		}
	}
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
	if(Uart1_Rx_Cnt >= 255)
	{
		Uart1_Rx_Cnt = 0;
		memset(RxBuffer,0x00,sizeof(RxBuffer));
		HAL_UART_Transmit(&huart3, (uint8_t *)"????", 10,0xFFFF); 	        
	}
	else
	{
		RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;
//		Uart1_Rx_Cnt = 0;
//		memset(RxBuffer,0x00,sizeof(RxBuffer));
	}
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&aRxBuffer, 1);
  /* NOTE: This function should not be modified, when the callback is needed,
           the HAL_UART_TxHalfCpltCallback can be implemented in the user file.
   */
}

int fputc(int ch, FILE *f)
{
 while ((USART3->ISR & 0X40) == 0); 
 USART3->TDR = (uint8_t)ch; 
 return ch;
}
//extern float q_current_bpf;
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	static uint8_t cnt;
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hadc);
	if(hadc == &hadc1)
	{
        if(ADC_offset == 0)
		{
			cnt++;
			adc1_in1 = hadc1.Instance->JDR1;
			adc1_in2 = hadc2.Instance->JDR1;
			adc1_in3 = hadc1.Instance->JDR2;
			IA_Offset += adc1_in1;
			IB_Offset += adc1_in2;
			IC_Offset += adc1_in3;
			if(cnt >= 10)
			{
				ADC_offset = 1;
				IA_Offset = IA_Offset/10;
				IB_Offset = IB_Offset/10;
				IC_Offset = IC_Offset/10;
			}
		}
		else
		{
			FOC_Input.Udc = rtU.v_bus;
			HallTheta = HallTheta + HallThetaAdd;
			if(HallTheta<0.0f)
			{
				HallTheta += 2.0f*PI;
			}
			else if(HallTheta>(2.0f*PI))
			{
				HallTheta -= 2.0f*PI;
			}
//			FOC_Input.theta=HallTheta;
			
//			Speed_Fdk = HallSpeed;
//			HallSpeedtest = aalpha * HallSpeed + (1 - aalpha) * HallSpeedLast;
			
		
			adc1_in1 = hadc1.Instance->JDR1;
			adc1_in3 = hadc1.Instance->JDR2;
			adc1_in2 = hadc2.Instance->JDR1;
			rtU.ia = (adc1_in1 - IA_Offset)*0.01933593f;
			rtU.ib = (adc1_in2 - IB_Offset)*0.01933593f;
			rtU.ic = (adc1_in3 - IC_Offset)*0.01933593f;
//			FOC_Model_step();
			motor_run();
//			TIM1->CCR1 = rtY.Tcmp1;
//			TIM1->CCR2 = rtY.Tcmp2;
//			TIM1->CCR3 = rtY.Tcmp3;
			load_data[0] = Speed_Ref;   //i
			load_data[1] = Speed_Fdk;   //IIR滤波之后得到的波形(低通滤波)
			load_data[2] =  FOC_Input.Iq_ref;//Flux_Observer.theta;//q_current_bpf;////     //IIR滤波之后得到的波形;（带通滤波）
			load_data[3] =  Current_Lpf_Idq.Iq; //0.04;//Current_Idq.Iq;    //rtU.Speed_ref;
			load_data[4] = rtU.ic;//-0.04;//HFI_Par.hfi_inj_volt;    
			memcpy(tempData, (uint8_t *)&load_data, sizeof(load_data));
			HAL_UART_Transmit_DMA(&huart3,(uint8_t *)tempData,6*4);
		}
	}

  /* NOTE : This function should not be modified. When the callback is needed,
            function HAL_ADCEx_InjectedConvCpltCallback must be implemented in the user file.
  */
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);
		if(htim == &htim4)
	{
		HallTemp = HAL_TIM_ReadCapturedValue(&htim4,TIM_CHANNEL_1);;
		HallThetaAdd = (PI/3)/(HallTemp/10000000)/10000;
		HallSpeed = (PI/3)/(HallTemp/10000000)*30/(2*PI);
		HallReadTemp = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8);
		HallReadTemp |= HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)<<1;
		HallReadTemp |= HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6)<<2;
		if(HallReadTemp==0x05)
    {
      HallTheta = 0.0f+PHASE_SHIFT_ANGLE;
    }
    else if(HallReadTemp==0x04)
    {
      HallTheta = (PI/3.0f)+PHASE_SHIFT_ANGLE;
    }
    else if(HallReadTemp==0x06)
    {
      HallTheta = (PI*2.0f/3.0f)+PHASE_SHIFT_ANGLE;
    }
    else if(HallReadTemp==0x02)
    {
      HallTheta = PI+PHASE_SHIFT_ANGLE;
    }
    else if(HallReadTemp==0x03)
    {
      HallTheta = (PI*4.0f/3.0f)+PHASE_SHIFT_ANGLE;
    }
    else if(HallReadTemp==0x01)
    {
      HallTheta = (PI*5.0f/3.0f)+PHASE_SHIFT_ANGLE;
    }
    if(HallTheta<0.0f)
    {
      HallTheta += 2.0f*PI;
    }
    else if(HallTheta>(2.0f*PI))
    {
      HallTheta -= 2.0f*PI;
    }
	}

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_TIM_IC_CaptureCallback could be implemented in the user file
   */
}

void FDCAN_Config(void)
{
  FDCAN_FilterTypeDef sFilterConfig;
  
  HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
  
  sFilterConfig.IdType = FDCAN_EXTENDED_ID;  
  sFilterConfig.FilterIndex = 0;             
  sFilterConfig.FilterType = FDCAN_FILTER_RANGE;  
  sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  sFilterConfig.FilterID1 = 0x00000000;
  sFilterConfig.FilterID2 = 0x01ffffff;       
  HAL_FDCAN_ConfigFilter(&hfdcan1, &sFilterConfig);
  
  TxHeader.Identifier = 0x1B;
  TxHeader.IdType = FDCAN_EXTENDED_ID;
  TxHeader.TxFrameType = FDCAN_DATA_FRAME;
  TxHeader.DataLength = FDCAN_DLC_BYTES_8;
  TxHeader.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
  TxHeader.BitRateSwitch = FDCAN_BRS_OFF;
  TxHeader.FDFormat = FDCAN_CLASSIC_CAN;
  TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
  TxHeader.MessageMarker = 0x52;

  HAL_FDCAN_Start(&hfdcan1);
}

float theta_add1=0;
int obsever=0;
void motor_run(void)
{
  float vbus_temp;
  float ia_temp,ib_temp;
//  vbus_temp = (float)(ADC1->JDR1);                                //得到母线电压 adc转换值
//  ia_temp = (float)((int16_t)A_offset - (int16_t)ADC1->JDR2);   //得到A相电流 adc转换值
//  ib_temp = (float)((int16_t)B_offset - (int16_t)ADC1->JDR3);   //得到B相电流 adc转换值
//  Vbus = vbus_temp*VBUS_CONVERSION_FACTOR;                        //通过电压转换因子（通过分压电阻得到）把adc转换值 转化为 真实电压
  Ia = rtU.ia;//ia_temp*SAMPLE_CURR_CON_FACTOR;                            //通过电流转换因子（通过采样电阻和运算放大倍数得到）把adc采样值转化为真实电流值
  Ib = rtU.ib;//ib_temp*SAMPLE_CURR_CON_FACTOR;                            //通过电流转换因子（通过采样电阻和运算放大倍数得到）把adc采样值转化为真实电流值
  Ic = rtU.ic;//-Ia-Ib;                                                    //基于基尔霍夫电流定律，根据AB相电流去计算C相电流
//  
//  Encoder_Process();
  
  
  //FOC运行函数需要用到的输入信息
  //
//  	FOC_Input.Iq_ref = 0.0f;
//	FOC_Input.Id_ref = 0.0f;
//			if(d_direction_flag==1)
//			{
//				FOC_Input.Iq_ref = 0.05f;
//			}
  if(hfi_to_flux_ob_flag == 0)
  {
	   obsever=1;
    FOC_Input.theta = HFI_Par.hfi_theta;
    if(d_direction_ok == 1)
    {	
      FOC_Input.Iq_ref = 0.05f;
      if((HFI_Par.hfi_we > HFI_TO_FLUX_DOWN_FLAG)&&(HFI_Par.hfi_we < HFI_TO_FLUX_UP_FLAG))
      {
        if(hfi_to_flux_cnt>100)
        {
          hfi_to_flux_cnt = 0;
          hfi_to_flux_ob_flag = 1;
        }
        hfi_to_flux_cnt++;
      }
			
    }
  }
  else
  {
    if(speed_close_loop_flag == 1)
    {
      FOC_Input.Id_ref = 0.0f;
      Speed_Fdk = Flux_Observer.lpf_we;
      FOC_Input.Iq_ref = Speed_Pid_Out;
//      int_test1 = 5;
    }
    else
    {
      FOC_Input.Id_ref = 0.0f;
      FOC_Input.Iq_ref = 0.08f;
      Speed_Pid.I_Sum = 0.08f;
      if(Flux_Observer.lpf_we > SPEED_CLOSE_FLAG)
      {
        speed_close_loop_flag = 1;
      }
    }
    FOC_Input.theta = Flux_Observer.theta;
	  obsever=2;
  }
  //int_test1 = hfi_to_flux_ob_flag;
  //float_test1 = 6.28318548f * Speed_Ref;
//  float_test3 = Ia;
//  FOC_Input.Udc = Vbus;
//  FOC_Input.theta=HFI_Par.hfi_theta ;//  HallTheta;;  //角度为高频注入得到的角度
  FOC_Input.ia = Ia;
  FOC_Input.ib = Ib;
  FOC_Input.ic = Ic;    
  
  
  
  if(motor_start_stop==1)
  {
	foc_algorithm_step();       //整个FOC运行函数（包括无感状态观测器，电流环，SVPWM，坐标变换，电机参数识别）
    PWM_TIM->CCR1 = (u16)(FOC_Output.Tcmp1);     //通过SVPWM得到的占空比赋值给定时器的寄存器
    PWM_TIM->CCR2 = (u16)(FOC_Output.Tcmp2);
    PWM_TIM->CCR3 = (u16)(FOC_Output.Tcmp3);
  }
  else
  {
    PWM_TIM->CCR1 = PWM_TIM_PULSE>>1;
    PWM_TIM->CCR2 = PWM_TIM_PULSE>>1;
    PWM_TIM->CCR3 = PWM_TIM_PULSE>>1;
  }
  
  
  
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
