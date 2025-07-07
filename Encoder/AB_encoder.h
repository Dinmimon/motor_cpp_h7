/*
 * AB_encoder.h
 *
 *  Created on: May 2, 2025
 *      Author: din.maimon
 */

#ifndef AB_ENCODER_H_
#define AB_ENCODER_H_

#include "base_encoder.h"
#include <stdint.h>

class AB_encoder:public EncoderBase {
private:
    volatile uint32_t* counter_reg;         // Pointer to TIMx->CNT
    float counts_per_electrical_rev;        // Counts per 2π electrical radians

public:
    AB_encoder(volatile uint32_t* reg_ptr, float counts_per_elec_rev)
        : counter_reg(reg_ptr), counts_per_electrical_rev(counts_per_elec_rev) {}

    float getAngle() override {
        // Convert count to electrical radians
        return (2.0f * 3.1415926f * static_cast<float>(*counter_reg)) / counts_per_electrical_rev;
    }

    void reset() override {
        *counter_reg = 0;
    }

};

#endif /* AB_ENCODER_H_ */
