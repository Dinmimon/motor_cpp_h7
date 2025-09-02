/*
 * HAL_PWM.cpp
 *
 *  Created on: Aug 31, 2025
 *      Author: din.maimon
 */

#include "HAL_PWM.h"


HAL_PWM::HAL_PWM()
{
}

void HAL_PWM::init(volatile uint32_t *pwm_A, volatile uint32_t *pwm_B, volatile uint32_t *pwm_C, uint32_t period , TIM_HandleTypeDef *htim)
{
	pwm_A_ = pwm_A;
	pwm_B_ = pwm_B;
	pwm_C_ = pwm_C;
	Period_ = period;

	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(htim, TIM_CHANNEL_3);
}

void HAL_PWM::setPWM_Duty(float dutyA, float dutyB, float dutyC)
{
	*pwm_A_ =  Period_/2 + dutyA;
	*pwm_B_ =  Period_/2 + dutyB;
	*pwm_C_ =  Period_/2 + dutyC;

}
