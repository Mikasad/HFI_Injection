/**********************************
             慧驱动
        视频教程详见QQ空间或B站
        其他事宜详见readme.txt
          QQ：1323279545
         微信：huiqudong
        官网：www.huiqudong.cn
**********************************/
#ifndef __ADC_H_
#define __ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_ADC1_Init(void);
void MX_ADC2_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif


#define ADC_REF_V                   (float)(3.3f)
#define VBUS_UP_RES                 (float)(95.3f) 
#define VBUS_DOWN_RES               (float)(4.99f) 
#define VBUS_CONVERSION_FACTOR      (float)(ADC_REF_V*(VBUS_UP_RES+VBUS_DOWN_RES)/VBUS_DOWN_RES/4095.0f)

#define SAMPLE_RES                  (float)(0.002f)
#define AMP_GAIN                    (float)(80.0f)
#define SAMPLE_CURR_CON_FACTOR      (float)(ADC_REF_V/4095.0f/AMP_GAIN/SAMPLE_RES)



extern uint8_t hfi_to_flux_ob_flag;
extern uint8_t get_offset_flag;
extern float angle;
extern float Iq_ref;
extern float EKF_Hz;
extern u8 speed_close_loop_flag;
extern uint16_t ADC1ConvertedValue[5];

#endif
