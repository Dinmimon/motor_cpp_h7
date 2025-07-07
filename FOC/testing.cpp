/*
 * testing.c
 *
 *  Created on: Apr 15, 2025
 *      Author: din.maimon
 */

#include "main.h"
#include "Motor.h"
#include "fake_encoder.h"
#include "trap_traj.h"
#include "Baseadcsensor.h"
Motor *motor[2];

TRAPEZ_trapezoidalTrajectory_t trg;
int  traj_ativate;



void init_motor(Motor &motorR,Motor &motorL)
{
	motor[0] = &motorR;
	motor[1] = &motorL;
}
FakeEncoderSim encoder { 10000, 1 };
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc) {
//	if (traj_ativate == 1) {
//		trapez_trajectory_process(&trg, 0.001);
//
//	}
//	else
//	{
//		trajectory_init(&trg, 500.0f, 500.0f, 500.0f, 2000.0f);
//	}

	if (hadc->Instance == ADC1)
	{
		// ADC1 conversion complete callback
		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin,GPIO_PIN_SET);
	}
	else if (hadc->Instance == ADC2)
	{
		// ADC2 conversion complete callback
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin,GPIO_PIN_SET);

	}


	if (hadc->Instance == ADC1)
	{
		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin,GPIO_PIN_RESET);
	}
	else if (hadc->Instance == ADC2)
	{
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
	}

	motor[0]->setEncoder(encoder);
	motor[0]->updateEncoder();
	motor[0]->motor_current_control_loop();
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);

}

void motor_init()
{

}

