
// ABEncoder implementation and motor integration example
#include "ABEncoder.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Example: ABEncoder initialization and configuration for motor
#include "main.h" // For TIM_HandleTypeDef and other MCU definitions


// Example usage for ABEncoder initialization and configuration for motor:
// Place this in your motor initialization/configuration code:
//
// extern TIM_HandleTypeDef htim3;
// float timerFreqHz = HAL_RCC_GetPCLK1Freq() / Motor_PWM_toSet->Init.Period;
// ABEncoder abEncoder(4096, timerFreqHz, htim3, VSHEN_POLE_PAIRS);

// In your control loop:
// abEncoder.update();
// float mechAngle = abEncoder.getMechanicalAngle();
// float elecAngle = abEncoder.getElectricalAngle();
// float velocity = abEncoder.getVelocity();
//
// In your control loop:
// abEncoder.update();
// float mechAngle = abEncoder.getMechanicalAngle();
// float elecAngle = abEncoder.getElectricalAngle();
// float velocity = abEncoder.getVelocity();

ABEncoder::ABEncoder(int resolution, float timerFreqHz, TIM_HandleTypeDef& htim, int polePairs)
    : _resolution(resolution), _timerFreqHz(timerFreqHz), _htim(htim), _polePairs(polePairs), _position(0), _velocity(0.0f)
{
    _lastUpdateTime = __HAL_TIM_GET_COUNTER(&_htim);
}

void ABEncoder::update() {
    uint32_t nowTicks = __HAL_TIM_GET_COUNTER(&_htim);
    int32_t deltaTicks = static_cast<int32_t>(nowTicks - _lastUpdateTime);

    _position += deltaTicks;
    float dtSec = deltaTicks / _timerFreqHz;
    _velocity = dtSec != 0.0f ? deltaTicks / dtSec : 0.0f;

    _lastUpdateTime = nowTicks;
}

float ABEncoder::getMechanicalAngle() const {
    float mechanicalAngle = (2.0f * M_PI * _position) / _resolution;
    return wrapTo2Pi(mechanicalAngle);
}

float ABEncoder::getElectricalAngle() const {
    float mechanicalAngle = getMechanicalAngle();
    float electricalAngle = mechanicalAngle * _polePairs;
    return wrapTo2Pi(electricalAngle);
}

float ABEncoder::getVelocity() const {
    return _velocity;
}

void ABEncoder::reset() {
    _position = 0;
    _velocity = 0.0f;
    _lastUpdateTime = __HAL_TIM_GET_COUNTER(&_htim);
}

float ABEncoder::wrapTo2Pi(float angle) const {
    while (angle >= 2.0f * M_PI) {
        angle -= 2.0f * M_PI;
    }
    while (angle < 0.0f) {
        angle += 2.0f * M_PI;
    }
    return angle;
}

float ABEncoder::getAngle() {
    return getMechanicalAngle(); // or getElectricalAngle() if you want electrical angle
}
