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



void HAL_PWM::init(volatile uint32_t *pwm_A, volatile uint32_t *pwm_B, volatile uint32_t *pwm_C, uint32_t period)
{
	pwm_A_ = pwm_A;
	pwm_B_ = pwm_B;
	pwm_C_ = pwm_C;
	Period_ = period;

}
