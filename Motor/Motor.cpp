/*
 * Motor.cpp
 *
 *  Created on: Apr 7, 2025
 *      Author: din.maimon
 */

#include "Motor.h"
#include <stdint.h>

uint32_t pwm_period = 0;
void Motor::motor_current_control_loop() {
	// current sampling
	motor_encoder->update();
	electrical_angle = motor_encoder->getAngle();
	_calculate_sin_and_cos_values_of_angle();
	//  ClarkeParke  for dq transformation

	ClarkeParke();

//	// current control loop
//	q_current_pid.update(0, inv_clarke_park.q, 0);
//	d_current_pid.update(0, inv_clarke_park.d, 0);
	//  ClarkeParke  for dq transformation
	InvClarkeParke();
	pwm->setPWM_Duty(inv_clarke_park.u, inv_clarke_park.v, inv_clarke_park.w);
}

void Motor::updateEncoder() {
	// Only needed for simulated encoders
	if (motor_encoder) {
		motor_encoder->update();
	}
}
Motor::~Motor() {
	// TODO Auto-generated destructor stub
}

