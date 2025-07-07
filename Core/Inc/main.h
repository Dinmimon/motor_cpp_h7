/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32h7xx_hal.h"

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
#define MTRL_HALL_A_Pin GPIO_PIN_2
#define MTRL_HALL_A_GPIO_Port GPIOE
#define MTRL_HALL_B_Pin GPIO_PIN_3
#define MTRL_HALL_B_GPIO_Port GPIOE
#define MTRR_HALL_A_Pin GPIO_PIN_4
#define MTRR_HALL_A_GPIO_Port GPIOE
#define MTRR_HALL_B_Pin GPIO_PIN_5
#define MTRR_HALL_B_GPIO_Port GPIOE
#define MTRR_HALL_C_Pin GPIO_PIN_6
#define MTRR_HALL_C_GPIO_Port GPIOE
#define EXT_IN_Pin GPIO_PIN_13
#define EXT_IN_GPIO_Port GPIOC
#define MTRL_HALL_C_Pin GPIO_PIN_0
#define MTRL_HALL_C_GPIO_Port GPIOF
#define MOTOR_ENABLE_Pin GPIO_PIN_1
#define MOTOR_ENABLE_GPIO_Port GPIOF
#define MODE_Pin GPIO_PIN_2
#define MODE_GPIO_Port GPIOF
#define MTRA2_HB_TMPR_Pin GPIO_PIN_3
#define MTRA2_HB_TMPR_GPIO_Port GPIOF
#define VOLT_5_Pin GPIO_PIN_4
#define VOLT_5_GPIO_Port GPIOF
#define MTRA1_HB_TEMP_Pin GPIO_PIN_5
#define MTRA1_HB_TEMP_GPIO_Port GPIOF
#define VOLT_24_Pin GPIO_PIN_6
#define VOLT_24_GPIO_Port GPIOF
#define MRTA1_TMPR_Pin GPIO_PIN_7
#define MRTA1_TMPR_GPIO_Port GPIOF
#define V_BUS_Pin GPIO_PIN_8
#define V_BUS_GPIO_Port GPIOF
#define MTRA2_TEMPR_Pin GPIO_PIN_10
#define MTRA2_TEMPR_GPIO_Port GPIOF
#define V_BRAKE_Pin GPIO_PIN_1
#define V_BRAKE_GPIO_Port GPIOC
#define SSI_MOSI2_Pin GPIO_PIN_3
#define SSI_MOSI2_GPIO_Port GPIOC
#define MTRR_PH_C_Pin GPIO_PIN_1
#define MTRR_PH_C_GPIO_Port GPIOA
#define MTRL_PH_C_Pin GPIO_PIN_3
#define MTRL_PH_C_GPIO_Port GPIOA
#define SSI_CLK1_Pin GPIO_PIN_5
#define SSI_CLK1_GPIO_Port GPIOA
#define MTRR_ENC_A_Pin GPIO_PIN_6
#define MTRR_ENC_A_GPIO_Port GPIOA
#define SSI_MOSI1_Pin GPIO_PIN_7
#define SSI_MOSI1_GPIO_Port GPIOA
#define MTRL_PH_A_Pin GPIO_PIN_4
#define MTRL_PH_A_GPIO_Port GPIOC
#define MTRR_PH_B_Pin GPIO_PIN_1
#define MTRR_PH_B_GPIO_Port GPIOB
#define DRV_MOSI_Pin GPIO_PIN_2
#define DRV_MOSI_GPIO_Port GPIOB
#define MTRR_PH_A_Pin GPIO_PIN_11
#define MTRR_PH_A_GPIO_Port GPIOF
#define MTRL_PH_B_Pin GPIO_PIN_13
#define MTRL_PH_B_GPIO_Port GPIOF
#define SW11_Pin GPIO_PIN_0
#define SW11_GPIO_Port GPIOG
#define SW12_Pin GPIO_PIN_1
#define SW12_GPIO_Port GPIOG
#define P24V_PG_Pin GPIO_PIN_7
#define P24V_PG_GPIO_Port GPIOE
#define TEST1_Pin GPIO_PIN_8
#define TEST1_GPIO_Port GPIOE
#define MTRR_PWM_A_Pin GPIO_PIN_9
#define MTRR_PWM_A_GPIO_Port GPIOE
#define P3V3_PG_Pin GPIO_PIN_10
#define P3V3_PG_GPIO_Port GPIOE
#define P24V_EN_Pin GPIO_PIN_12
#define P24V_EN_GPIO_Port GPIOE
#define MTRR_PWM_C_Pin GPIO_PIN_13
#define MTRR_PWM_C_GPIO_Port GPIOE
#define P5V_EN_Pin GPIO_PIN_14
#define P5V_EN_GPIO_Port GPIOE
#define SSI_CLK2_Pin GPIO_PIN_10
#define SSI_CLK2_GPIO_Port GPIOB
#define DRV1_CS_Pin GPIO_PIN_12
#define DRV1_CS_GPIO_Port GPIOB
#define DRV2_CS_Pin GPIO_PIN_13
#define DRV2_CS_GPIO_Port GPIOB
#define ENC_ABn1_Pin GPIO_PIN_15
#define ENC_ABn1_GPIO_Port GPIOB
#define MTRL_ENC_A_Pin GPIO_PIN_12
#define MTRL_ENC_A_GPIO_Port GPIOD
#define MTRL_ENC_B_Pin GPIO_PIN_13
#define MTRL_ENC_B_GPIO_Port GPIOD
#define LED_GREEN_Pin GPIO_PIN_14
#define LED_GREEN_GPIO_Port GPIOD
#define LED_RED_Pin GPIO_PIN_15
#define LED_RED_GPIO_Port GPIOD
#define SW13_Pin GPIO_PIN_3
#define SW13_GPIO_Port GPIOG
#define SW14_Pin GPIO_PIN_4
#define SW14_GPIO_Port GPIOG
#define SW21_Pin GPIO_PIN_5
#define SW21_GPIO_Port GPIOG
#define SW22_Pin GPIO_PIN_6
#define SW22_GPIO_Port GPIOG
#define nFAULT1_Pin GPIO_PIN_7
#define nFAULT1_GPIO_Port GPIOG
#define nFAULT2_Pin GPIO_PIN_8
#define nFAULT2_GPIO_Port GPIOG
#define MTRL_PWM_A_Pin GPIO_PIN_6
#define MTRL_PWM_A_GPIO_Port GPIOC
#define MTRL_PWM_B_Pin GPIO_PIN_7
#define MTRL_PWM_B_GPIO_Port GPIOC
#define MTRL_PWM_C_Pin GPIO_PIN_8
#define MTRL_PWM_C_GPIO_Port GPIOC
#define MTRR_PWM_B_Pin GPIO_PIN_9
#define MTRR_PWM_B_GPIO_Port GPIOA
#define ENC_DIR1_Pin GPIO_PIN_10
#define ENC_DIR1_GPIO_Port GPIOA
#define ENC_ABn2_Pin GPIO_PIN_11
#define ENC_ABn2_GPIO_Port GPIOA
#define ENC_DIR2_Pin GPIO_PIN_12
#define ENC_DIR2_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define DRV_SCK_Pin GPIO_PIN_10
#define DRV_SCK_GPIO_Port GPIOC
#define DRV_MISO_Pin GPIO_PIN_11
#define DRV_MISO_GPIO_Port GPIOC
#define EXT_OUT_Pin GPIO_PIN_12
#define EXT_OUT_GPIO_Port GPIOC
#define CAN_S_Pin GPIO_PIN_2
#define CAN_S_GPIO_Port GPIOD
#define MTRL_INLA_Pin GPIO_PIN_3
#define MTRL_INLA_GPIO_Port GPIOD
#define MTRL_INLB_Pin GPIO_PIN_4
#define MTRL_INLB_GPIO_Port GPIOD
#define MTRL_INLC_Pin GPIO_PIN_5
#define MTRL_INLC_GPIO_Port GPIOD
#define SENSOR1_Pin GPIO_PIN_10
#define SENSOR1_GPIO_Port GPIOG
#define SENSOR2_Pin GPIO_PIN_11
#define SENSOR2_GPIO_Port GPIOG
#define MTRR_INLA_Pin GPIO_PIN_12
#define MTRR_INLA_GPIO_Port GPIOG
#define MTRR_INLB_Pin GPIO_PIN_13
#define MTRR_INLB_GPIO_Port GPIOG
#define MTRR_INLC_Pin GPIO_PIN_14
#define MTRR_INLC_GPIO_Port GPIOG
#define STO_Pin GPIO_PIN_15
#define STO_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define MTRR_ENC_B_Pin GPIO_PIN_5
#define MTRR_ENC_B_GPIO_Port GPIOB
#define VCP_TX_Pin GPIO_PIN_6
#define VCP_TX_GPIO_Port GPIOB
#define VCP_RX_Pin GPIO_PIN_7
#define VCP_RX_GPIO_Port GPIOB
#define LED_YELLOW_Pin GPIO_PIN_1
#define LED_YELLOW_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
