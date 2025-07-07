/*
 * fake_encoder.h
 *
 *  Created on: Apr 30, 2025
 *      Author: din.maimon
 */

#ifndef FAKE_ENCODER_H_
#define FAKE_ENCODER_H_
#include "base_encoder.h"
#include <cmath>

class FakeEncoderSim : public EncoderBase {
private:
    float electrical_angle;         // Current simulated angle [rad]
    float update_frequency_hz;      // How often update() is called
    float target_frequency_hz;      // Desired simulated frequency (Hz)
    float angle_increment_per_call; // Δθ per update call

public:
    FakeEncoderSim(float update_freq_hz, float target_freq_hz)
        : electrical_angle(0.0f),
          update_frequency_hz(update_freq_hz),
          target_frequency_hz(target_freq_hz)
    {
        computeIncrement();
    }

    void setFrequency(float freq_hz) {
        target_frequency_hz = freq_hz;
        computeIncrement();
    }

    void setUpdateRate(float update_rate_hz) {
        update_frequency_hz = update_rate_hz;
        computeIncrement();
    }

    void computeIncrement() {
        angle_increment_per_call = (2.0f * 3.1415926f * target_frequency_hz) / update_frequency_hz;
    }

    // Call this on every loop/update tick
    void update() {
        electrical_angle += angle_increment_per_call;

        // Wrap between [0, 2π]
        if (electrical_angle >= 2.0f * 3.1415926f)
            electrical_angle -= 2.0f * 3.1415926f;
    }

    float getAngle() override {
        return electrical_angle;
    }

    void reset() override {
        electrical_angle = 0.0f;
    }
};

#endif /* FAKE_ENCODER_H_ */
