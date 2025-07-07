/*
 * HallSensor_encoder.h
 *
 *  Created on: May 4, 2025
 *      Author: din.maimon
 */

#ifndef HALLSENSOR_ENCODER_H_
#define HALLSENSOR_ENCODER_H_


#include "base_encoder.h"

#include <cmath>

class HallEncoder : public EncoderBase {
public:
    HallEncoder(int polePairs, float timerFreqHz, TIM_HandleTypeDef& htim)
        : _polePairs(polePairs), _timerFreqHz(timerFreqHz), _htim(htim)
    {
        _lastTransitionTime = __HAL_TIM_GET_COUNTER(&_htim);
        _lastUpdateTime = _lastTransitionTime;
        _electricalAngle = 0.0f;
        _mechanicalAngle = 0.0f;
        _velocity = 0.0f;
    }

    void handleTransition(uint32_t currentTimeTicks, uint8_t hallState) {
        float newElectrical = hallStateToAngle(hallState);

        float delta = newElectrical - _electricalAngle;
        if (delta > 3.0f) _turns--;
        else if (delta < -3.0f) _turns++;

        _electricalAngle = newElectrical;
        _mechanicalAngle = (_turns * 2 * M_PI) + (_electricalAngle / _polePairs);

        uint32_t dtTicks = currentTimeTicks - _lastTransitionTime;
        if (dtTicks > 0) {
            float dtSec = dtTicks / _timerFreqHz;
            _velocity = (2 * M_PI / 6.0f / _polePairs) / dtSec;
            if (delta < 0) _velocity = -_velocity;
        }

        _lastTransitionTime = currentTimeTicks;
        _lastUpdateTime = currentTimeTicks;
    }

    void update() override {
        uint32_t nowTicks = __HAL_TIM_GET_COUNTER(&_htim);
        uint32_t dtTicks = nowTicks - _lastUpdateTime;
        _lastUpdateTime = nowTicks;

        // Zero velocity if no transition for 100ms
        uint32_t sinceLastTransition = nowTicks - _lastTransitionTime;
        float timeoutTicks = _timerFreqHz * 0.1f;
        if (sinceLastTransition > timeoutTicks) {
            _velocity = 0.0f;
        }

        // Interpolation
        float dtSec = dtTicks / _timerFreqHz;
        _mechanicalAngle += _velocity * dtSec;
    }

    float getMechanicalAngle() const override {
        return _mechanicalAngle;
    }

    float getElectricalAngle() const override {
        return _electricalAngle;
    }

    float getVelocity() const {
        return _velocity;
    }

    void reset() override {
        _turns = 0;
        _mechanicalAngle = 0.0f;
        _electricalAngle = 0.0f;
        _velocity = 0.0f;
        _lastTransitionTime = __HAL_TIM_GET_COUNTER(&_htim);
        _lastUpdateTime = _lastTransitionTime;
    }

private:
    int _polePairs;
    float _timerFreqHz;
    TIM_HandleTypeDef& _htim;

    float _electricalAngle = 0.0f;
    float _mechanicalAngle = 0.0f;
    float _velocity = 0.0f;
    int _turns = 0;
    uint32_t _lastTransitionTime = 0;
    uint32_t _lastUpdateTime = 0;

    float hallStateToAngle(uint8_t state) {
        switch (state) {
            case 0b001: return 0.0f;
            case 0b101: return M_PI / 3.0f;
            case 0b100: return 2 * M_PI / 3.0f;
            case 0b110: return M_PI;
            case 0b010: return 4 * M_PI / 3.0f;
            case 0b011: return 5 * M_PI / 3.0f;
            default: return _electricalAngle; // fallback
        }
    }
};


#endif /* HALLSENSOR_ENCODER_H_ */
