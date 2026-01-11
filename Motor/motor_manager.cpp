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
Motor *MotorManager::motor[2] = {nullptr, nullptr};
TrajController MotorManager::trajectory;
FakeEncoderSim MotorManager::encoder{10000, 1};

void MotorManager::init()
{
    // Initialize trajectory and other motor-related variables
    motor[0] = nullptr;
    motor[1] = nullptr;
}

void MotorManager::setMotor(uint8_t index, Motor &motor)
{
    // protection against null pointers
    if (&motor == nullptr)
    {
        return;
    }

    if (index < 2)
    {
        MotorManager::motor[index] = &motor;
    }
}

void MotorManager::processADCCallback(ADC_HandleTypeDef *hadc)
{

    if (hadc->Instance == ADC1)
    {
        if (motor[1] != nullptr)
        {
            motor[1]->motor_current_control_loop();
        }
        // ADC1 conversion complete callback
        HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET);
    }
    else if (hadc->Instance == ADC2)
    {
        if (motor[0] != nullptr)
        {
            motor[0]->motor_current_control_loop();
        }
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

    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
}

// C wrapper function for HAL callback
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    MotorManager::processADCCallback(hadc);
}
