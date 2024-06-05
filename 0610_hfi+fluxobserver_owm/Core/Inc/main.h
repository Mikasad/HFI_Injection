/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"
//#include "foc_define_parameter.h"
//#include "arm_math.h"
//#include "board_config.h"
//#include "oled_font.h"
//#include "oled.h"
//#include "drv8301.h"
//#include "exti.h"
#include "foc_algorithm.h"
#include "adc.h"
#include "low_task.h"
#include "speed_pid.h"
#include "flux_observer.h"
#include "high_frequency_injection.h"
#include "arm_math.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Button3_Pin GPIO_PIN_13
#define Button3_GPIO_Port GPIOC
#define Button3_EXTI_IRQn EXTI15_10_IRQn
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOC
#define Button1_Pin GPIO_PIN_10
#define Button1_GPIO_Port GPIOC
#define Button1_EXTI_IRQn EXTI15_10_IRQn
#define Button2_Pin GPIO_PIN_11
#define Button2_GPIO_Port GPIOC
#define Button2_EXTI_IRQn EXTI15_10_IRQn


/* USER CODE BEGIN Private defines */
typedef enum
{
  FALSE = 0, TRUE  = !FALSE
}
bool;
void TimingDelay_Decrement(void);
extern void Delay(__IO uint32_t nTime);
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
#define PWM_TIM             TIM1
#define PWM_TIM_FREQ        10000         //HZ
#define PWM_TIM_CLOCK       160000000
#define PWM_TIM_PULSE       (PWM_TIM_CLOCK/(2*PWM_TIM_FREQ))
#define PWM_TIM_PULSE_TPWM  (PWM_TIM_CLOCK/(PWM_TIM_FREQ))
/* USER CODE END Private defines */
void motor_run(void);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
