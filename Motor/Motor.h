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
#include "HAL_PWM.h"
class Motor: protected FOC {
public:

	Motor(){};
	virtual ~Motor();
	void motor_current_control_loop();
	void setEncoder(EncoderBase &enc) {motor_encoder = &enc;}
	void setPWMDriver(HAL_PWM &pwm_driver) {pwm = &pwm_driver;}
	void init_motor(Base_adc_sensor adc_currentA,Base_adc_sensor adc_currentB);
	void updateEncoder();
	void setCurrentSensors (Base_adc_sensor &sensorA , Base_adc_sensor &sensorB) {curr_a = &sensorA; curr_b = &sensorB; }

private:

	PID q_current_pid;
	PID d_current_pid;
	EncoderBase *motor_encoder;
	Base_adc_sensor *vbus;
	Base_adc_sensor *curr_a;
	Base_adc_sensor *curr_b;
	HAL_PWM *pwm;


};

#endif /* SRC_MOTOR_H_ */
