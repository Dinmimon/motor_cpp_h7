/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
     PA8   ------> RCC_MCO_1
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, MOTOR_ENABLE_Pin|MODE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, TEST1_Pin|P24V_EN_Pin|P5V_EN_Pin|LED_YELLOW_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DRV1_CS_Pin|DRV2_CS_Pin|ENC_ABn1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED_GREEN_Pin|CAN_S_Pin|MTRL_INLA_Pin|MTRL_INLB_Pin
                          |MTRL_INLC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENC_DIR1_Pin|ENC_ABn2_Pin|ENC_DIR2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EXT_OUT_GPIO_Port, EXT_OUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, MTRR_INLA_Pin|MTRR_INLB_Pin|MTRR_INLC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MTRL_HALL_A_Pin MTRL_HALL_B_Pin MTRR_HALL_A_Pin MTRR_HALL_B_Pin
                           MTRR_HALL_C_Pin P24V_PG_Pin P3V3_PG_Pin */
  GPIO_InitStruct.Pin = MTRL_HALL_A_Pin|MTRL_HALL_B_Pin|MTRR_HALL_A_Pin|MTRR_HALL_B_Pin
                          |MTRR_HALL_C_Pin|P24V_PG_Pin|P3V3_PG_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : EXT_IN_Pin */
  GPIO_InitStruct.Pin = EXT_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(EXT_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MTRL_HALL_C_Pin */
  GPIO_InitStruct.Pin = MTRL_HALL_C_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MTRL_HALL_C_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MOTOR_ENABLE_Pin MODE_Pin */
  GPIO_InitStruct.Pin = MOTOR_ENABLE_Pin|MODE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : SW11_Pin SW12_Pin SW13_Pin SW14_Pin
                           SW21_Pin SW22_Pin nFAULT1_Pin nFAULT2_Pin
                           SENSOR1_Pin SENSOR2_Pin STO_Pin */
  GPIO_InitStruct.Pin = SW11_Pin|SW12_Pin|SW13_Pin|SW14_Pin
                          |SW21_Pin|SW22_Pin|nFAULT1_Pin|nFAULT2_Pin
                          |SENSOR1_Pin|SENSOR2_Pin|STO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : TEST1_Pin P24V_EN_Pin P5V_EN_Pin LED_YELLOW_Pin */
  GPIO_InitStruct.Pin = TEST1_Pin|P24V_EN_Pin|P5V_EN_Pin|LED_YELLOW_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : DRV1_CS_Pin DRV2_CS_Pin ENC_ABn1_Pin */
  GPIO_InitStruct.Pin = DRV1_CS_Pin|DRV2_CS_Pin|ENC_ABn1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_GREEN_Pin LED_RED_Pin CAN_S_Pin MTRL_INLA_Pin
                           MTRL_INLB_Pin MTRL_INLC_Pin */
  GPIO_InitStruct.Pin = LED_GREEN_Pin|LED_RED_Pin|CAN_S_Pin|MTRL_INLA_Pin
                          |MTRL_INLB_Pin|MTRL_INLC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ENC_DIR1_Pin ENC_ABn2_Pin ENC_DIR2_Pin */
  GPIO_InitStruct.Pin = ENC_DIR1_Pin|ENC_ABn2_Pin|ENC_DIR2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : EXT_OUT_Pin */
  GPIO_InitStruct.Pin = EXT_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EXT_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MTRR_INLA_Pin MTRR_INLB_Pin MTRR_INLC_Pin */
  GPIO_InitStruct.Pin = MTRR_INLA_Pin|MTRR_INLB_Pin|MTRR_INLC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
