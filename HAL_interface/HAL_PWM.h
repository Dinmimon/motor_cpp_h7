/*
 * HAL_PWM.h
 *
 *  Created on: Aug 31, 2025
 *      Author: din.maimon
 */

#ifndef HAL_PWM_H_
#define HAL_PWM_H_
#include <stdint.h>

class HAL_PWM {
public:
	HAL_PWM();
	void init(volatile uint32_t *pwm_A, volatile uint32_t *pwm_B, volatile uint32_t *pwm_C, uint32_t period);
private:
	volatile uint32_t *pwm_A_;
	volatile uint32_t *pwm_B_;
	volatile uint32_t *pwm_C_;
	uint32_t Period_;
};

#endif /* HAL_PWM_H_ */
