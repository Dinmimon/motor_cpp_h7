/*
 * Baseadcsensor.h
 *
 *  Created on: Apr 10, 2025
 *      Author: din.maimon
 */

#ifndef BASEADCSENSOR_H_
#define BASEADCSENSOR_H_

#include <stdint.h>
#define ADC3_RESOLUTION 4096
#define ADC_REF_VOLTAGE 3.3

class Base_adc_sensor {
protected:
	volatile uint32_t *raw_val; // ADC channel for the sensor
	float factor ;
	float offset;
	int32_t value_in_volts;
	int32_t value_in_sensor_units;

public:
	Base_adc_sensor() {};
	void init_adc_sensor(volatile uint32_t *raw_val_ptr, float Factor, float Offset) {
		raw_val = raw_val_ptr;
		factor = Factor;
		offset = Offset;
		// Initialize the ADC sensor (if needed)
	}

	// Pure virtual function to read a raw ADC value in.
	// Derived classes must provide their implementation.
	uint32_t readRaw() {
		return (*raw_val);};

	// Pure virtual function to convert the raw ADC value into a useful measurement.
	float convertValue() { return ((float)((*raw_val * ADC_REF_VOLTAGE) / ADC3_RESOLUTION) * factor + offset); };
	float convertVoltValue() { return ((float)((*raw_val * ADC_REF_VOLTAGE) / ADC3_RESOLUTION)); };

	// Public method to read and return the processed sensor value.
	uint32_t getRawValue() {
		return (*raw_val);
	}
	uint32_t getValue() {
		return (convertValue());
	}
	uint32_t getVoltValue() {
		return convertVoltValue();
	}
};

#endif /* BASEADCSENSOR_H_ */
