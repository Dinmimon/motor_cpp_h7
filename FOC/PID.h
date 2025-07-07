/*
 * PID.h
 *
 *  Created on: Apr 28, 2025
 *      Author: din.maimon
 */

#ifndef PID_H_
#define PID_H_


class PID
{

    void setGains(float kp, float ki, float kd)
    {
        kp_ = kp;
        ki_ = ki;
        kd_ = kd;
    }

    void setOutputLimits(float min_val, float max_val)
    {
        output_min_ = min_val;
        output_max_ = max_val;
    }

    void setIntegralLimits(float min_val, float max_val)
    {
        integral_min_ = min_val;
        integral_max_ = max_val;
    }

    void reset()
    {
        integral_ = 0.0f;
        prev_error_ = 0.0f;
        output = 0.0f;
        p_term = 0.0f;
    }

    float update(float setpoint, float measurement, float feedforward = 0.0f)
    {
        float error = setpoint - measurement;

        // Proportional
         p_term = kp_ * error;

        // Only integrate if output is not saturated or if error is driving output towards unsaturation
        output = p_term + (ki_ * integral_) + feedforward;
        bool output_saturated = (output >= output_max_) || (output <= output_min_);

        if (!output_saturated || (output > output_max_ && error < 0) || (output < output_min_ && error > 0))
        {
            integral_ += error;
            // Clamp integral
            if (integral_ > integral_max_)
                integral_ = integral_max_;
            else if (integral_ < integral_min_)
                integral_ = integral_min_;
        }

        // Derivative (based on error)
        float derivative = error - prev_error_;
        prev_error_ = error;

        output = p_term + (ki_ * integral_) + (kd_ * derivative) + feedforward;

        // Apply output limits
        if (output > output_max_)
            output = output_max_;
        else if (output < output_min_)
            output = output_min_;

        return output;
    }

protected:
    float kp_, ki_, kd_;
    float output_min_, output_max_;
    float integral_min_, integral_max_;
    float integral_;
    float prev_error_;
    float output;
    float p_term;
};




#endif /* PID_H_ */
