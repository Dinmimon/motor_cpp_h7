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

#include "stm32h7xx_hal.h"
#include "HAL_PWM.h"
static TIM_HandleTypeDef *timer_pwm_obj;

void HAL_PWM_Init(TIM_HandleTypeDef &htim) {
	timer_pwm_obj = &htim;
}

void HAL_PWM_Write(uint32_t channel ,uint32_t duty) {
	switch (channel) {
	case TIM_CHANNEL_1:
		timer_pwm_obj->Instance->CCR1 = (timer_pwm_obj->Init.Period / 2) + duty;
		break;
	case TIM_CHANNEL_2:
		timer_pwm_obj->Instance->CCR2 = (timer_pwm_obj->Init.Period / 2) + duty;
		break;
	case TIM_CHANNEL_3:
		timer_pwm_obj->Instance->CCR3 = (timer_pwm_obj->Init.Period / 2) + duty;
		break;
	case TIM_CHANNEL_4:
		timer_pwm_obj->Instance->CCR4 = duty;
		break;
	default:
		break;
	}
}

/* [] END OF FILE */
