/*
 * motor_manager.cpp
 *
 *  Created on: Jul 22, 2025
 *      Author: din.maimon
 */

#include "motor_manager.h"
#include "main.h"
#include "Baseadcsensor.h"

// Static member definitions
Motor* MotorManager::motor[2] = {nullptr, nullptr};
TRAPEZ_trapezoidalTrajectory_t MotorManager::trg;
int MotorManager::traj_activate = 0;
FakeEncoderSim MotorManager::encoder{10000, 1};

void MotorManager::init()
{
    // Initialize trajectory and other motor-related variables
    traj_activate = 0;
    motor[0] = nullptr;
    motor[1] = nullptr;
}

void MotorManager::setMotors(Motor &motorR, Motor &motorL)
{
    motor[0] = &motorR;
    motor[1] = &motorL;
}

void MotorManager::processADCCallback(ADC_HandleTypeDef *hadc)
{
    // Trajectory processing (currently commented out from original)
    // if (traj_activate == 1) {
    //     trapez_trajectory_process(&trg, 0.001);
    // }
    // else
    // {
    //     trajectory_init(&trg, 500.0f, 500.0f, 500.0f, 2000.0f);
    // }

    if (hadc->Instance == ADC1)
    {
        // ADC1 conversion complete callback
        HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
    }
    else if (hadc->Instance == ADC2)
    {
        // ADC2 conversion complete callback
        HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET);
    }

    if (hadc->Instance == ADC1)
    {
        HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET);
    }
    else if (hadc->Instance == ADC2)
    {
        HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET);
    }

    // // Motor control processing
    // if (motor[0] != nullptr) {
    //     motor[0]->setEncoder(encoder);
    //     motor[0]->updateEncoder();
    //     motor[0]->motor_current_control_loop();
    // }
    
    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

// C wrapper function for HAL callback
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc) 
{
    MotorManager::processADCCallback(hadc);
}
