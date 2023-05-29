#ifndef _ISO_ACTUATOR_H_
#define _ISO_ACTUATOR_H_

/**
*	Various include to host the HW relevant 
*   s/w resources - GPIO - PWM IO etc
*/
#include <cstdint>
#include "isolatedBox_common.h"


constexpr auto ISO_PWM_FREQUENCY_MAX = 12345;
constexpr auto ISO_PWM_FREQUENCY_MIN = 0;
constexpr auto ISO_PWM_FREQUENCY_DEF = 100;

constexpr auto ISO_PWM_DUTY_CYCLE_MAX = 100;
constexpr auto ISO_PWM_DUTY_CYCLE_MIN = 0;
constexpr auto ISO_PWM_DUTY_CYCLE_DEF = 0;

constexpr auto ISO_PWM_INTENSITY_MAX_VALUE = 100;

class IsoActuator
{

public:
	IsoActuator();

	~IsoActuator();

	bool init();

	void operator!();

	void operator++();

	void operator+=(const uint8_t value);

	void operator--();

	void operator-=(const uint8_t value);

	bool setIntensity(const uint8_t value);

	uint8_t getIntensity() const;

	bool setFrequency(const uint32_t value);

	uint32_t getFrequency() const;

	bool setDutyCycle(const uint8_t value);

	uint8_t getDutyCycle() const;

	EquipmentState getPwmState();

private:
	EquipmentState m_pwmState;

	uint8_t m_intensity;

	uint32_t m_frequency;

	uint8_t m_dutyCycle;
};

#endif /* _ISO_ACTUATOR_H_ */