/*
 * HAL_PWM.h
 *
 *  Created on: Aug 31, 2025
 *      Author: din.maimon
 */

#ifndef HAL_PWM_H_
#define HAL_PWM_H_
#include <stdint.h>
#include "tim.h"
#include "stm32h7xx_hal.h"
class HAL_PWM
{
public:
	HAL_PWM();
	void setPWM_Duty(float dutyA, float dutyB, float dutyC); // 0.0 to 1.0
	void init(volatile uint32_t *pwm_A, volatile uint32_t *pwm_B, volatile uint32_t *pwm_C, uint32_t period, TIM_HandleTypeDef *htim);

private:
	volatile uint32_t *pwm_A_;
	volatile uint32_t *pwm_B_;
	volatile uint32_t *pwm_C_;
	uint32_t Period_;

private:
};

#endif /* HAL_PWM_H_ */
