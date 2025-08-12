/*
 * Motor.h
 *
 *  Created on: Apr 7, 2025
 *      Author: din.maimon
 */

#ifndef SRC_MOTOR_H_
#define SRC_MOTOR_H_
#include "FOC.h"
#include "PID.h"
#include "Baseadcsensor.h"
#include "base_encoder.h"

class Motor: protected FOC {
public:

	Motor(){};
	virtual ~Motor();
	void motor_current_control_loop();
	void setEncoder(EncoderBase &enc) {motor_encoder = &enc;}

	void init_motor(Base_adc_sensor adc_currentA,Base_adc_sensor adc_currentB);
	void updateEncoder();
private:
	volatile uint32_t *pwm_a;
	volatile uint32_t *pwm_b;
	volatile uint32_t *pwm_c;
	PID q_current_pid;
	PID d_current_pid;
	EncoderBase *motor_encoder;
	Base_adc_sensor *vbus;
	Base_adc_sensor *curr_a;
	Base_adc_sensor *curr_b;
	void setCurrentSensors (Base_adc_sensor &sensorA , Base_adc_sensor &sensorB) {curr_a = &sensorA; curr_b = &sensorB; }
	void setPWM (volatile uint32_t &pwm_A , volatile uint32_t &pwm_B,volatile uint32_t &pwm_C) {pwm_a = &pwm_A; pwm_b = &pwm_B;  pwm_c = &pwm_C;}

};

#endif /* SRC_MOTOR_H_ */
