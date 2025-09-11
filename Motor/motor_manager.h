/*
 * motor_manager.h
 *
 *  Created on: Jul 22, 2025
 *      Author: din.maimon
 */

#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include "Motor.h"
#include "fake_encoder.h"
#include "TrajController.h"
#include "stm32h7xx_hal.h"

class MotorManager {
public:
    static void init();
    static void setMotor(uint8_t index, Motor& motor);
    static void processADCCallback(ADC_HandleTypeDef *hadc);
    
private:
    static Motor *motor[2];
    static TrajController trajectory;
    static FakeEncoderSim encoder;
};

// C wrapper for HAL callback (still needs extern "C" for HAL compatibility)
#ifdef __cplusplus
extern "C" {
#endif
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);
#ifdef __cplusplus
}
#endif

#endif /* MOTOR_MANAGER_H */
