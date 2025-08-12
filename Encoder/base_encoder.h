/*
 * base_encoder.h
 *
 *  Created on: Apr 29, 2025
 *      Author: din.maimon
 */

#ifndef BASE_ENCODER_H_
#define BASE_ENCODER_H_

class EncoderBase {
public:
	virtual float getAngle() = 0; // radians
	virtual void reset() = 0;
	virtual void update() = 0;
};

#endif /* BASE_ENCODER_H_ */
