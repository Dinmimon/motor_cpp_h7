#ifndef AB_ENCODER_H_
#define AB_ENCODER_H_


#include "base_encoder.h"
#include "stm32h7xx_hal.h"
#include <cmath>
#include <cstdint>

class ABEncoder : public EncoderBase {
public:
    ABEncoder(int resolution, float timerFreqHz, TIM_HandleTypeDef& htim, int polePairs);

    void update() override;
    float getMechanicalAngle() const;
    float getElectricalAngle() const;
    float getVelocity() const;
    void reset() override;
    float getAngle() override;

private:
    int _resolution;
    float _timerFreqHz;
    TIM_HandleTypeDef& _htim;
    int _polePairs;

    int32_t _position;
    float _velocity;
    uint32_t _lastUpdateTime;

    float wrapTo2Pi(float angle) const;
};

#endif /* AB_ENCODER_H_ */
