/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef HAL_PWM_H
#define HAL_PWM_H

#include "stm32h7xx_hal.h"

void HAL_PWM_Init(TIM_HandleTypeDef *timer_pwm_pionet);

void HAL_PWM_Write(uint32_t channel ,uint32_t duty);


uint32_t HAL_PWM_Get_Prd(void);

#endif

/* [] END OF FILE */
