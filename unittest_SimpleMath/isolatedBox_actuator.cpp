#include "isolatedBox_actuator.h"
#ifdef ISO_PRINT_DEBUG
#include "isolatedBox_printdebug.h"
#endif // ISO_PRINT_DEBUG
#include <cstdio>


IsoActuator::IsoActuator()
{
#ifdef ISO_PRINT_DEBUG
    ISO_printDebug::printDebug("Initializing PWM Controller");
#endif // ISO_PRINT_DEBUG
    m_pwmState = DISABLED;
    m_dutyCycle = 0;
    m_frequency = 0;
    m_intensity = 0;
}

IsoActuator::~IsoActuator() {}

bool IsoActuator::init()
{
    bool success = false;

    /// <summary>
    /// Pseudo Code
    /// Create s/w Driver for PWM device
    /// bool pwmCreate(PWM_IO _io, float _initValue, int _range);
    /// Apply defualt value for duty cycle and frequency
    /// </summary>
    /// <returns></returns>
    
    if ((setFrequency(ISO_PWM_FREQUENCY_DEF) == true) &&
        (setDutyCycle(ISO_PWM_DUTY_CYCLE_DEF) == true)) {
            m_pwmState = ENABLED;
            m_dutyCycle = 0;
            m_frequency = 0;
            m_intensity = 0;
            /// bool pwmWrite(PWM_IO _io, float _intensity); /// m_intensity
            success = true;
    }
    
    return success;
}


void IsoActuator::operator!() { m_pwmState = DISABLED; }

void IsoActuator::operator++()
{
    if (m_intensity < ISO_PWM_INTENSITY_MAX_VALUE)
    {
        ++m_intensity;
        /// <summary>
        /// Apply intensity
        /// bool pwmWrite(PWM_IO _io, float _intensity); /// m_intensity
        /// </summary>
    }
}

void IsoActuator::operator+=(const uint8_t value)
{
    if (m_intensity + value <= ISO_PWM_INTENSITY_MAX_VALUE)
    {
        m_intensity += value;
        /// <summary>
        /// Apply intensity
        /// bool pwmWrite(PWM_IO _io, float _intensity); /// m_intensity
        /// </summary>
    }
}

void IsoActuator::operator--()
{
    if (m_intensity > 0)
    {
        --m_intensity;
        /// <summary>
        /// Apply intensity
        /// bool pwmWrite(PWM_IO _io, float _intensity); /// m_intensity
        /// </summary>
    }
}

void IsoActuator::operator-=(const uint8_t value)
{
    if (m_intensity > 0)
    {
        m_intensity -= value;
        /// <summary>
        /// Apply intensity
        /// bool pwmWrite(PWM_IO _io, float _intensity); /// m_intensity
        /// </summary>
    }
}

bool IsoActuator::setIntensity(const uint8_t value)
{
    if (value <= ISO_PWM_INTENSITY_MAX_VALUE && value >= 0)
    {
        m_intensity = value;
        /// <summary>
         /// Apply intensity
         /// bool pwmWrite(PWM_IO _io, float _intensity); /// m_intensity
         /// </summary>
         /// return true;
    }
    else return false;
}

uint8_t IsoActuator::getIntensity() const { return m_intensity; }

bool IsoActuator::setFrequency(const uint32_t value)
{
    if (value <  ISO_PWM_FREQUENCY_MAX && value > ISO_PWM_FREQUENCY_MIN)
    {
        m_frequency = value;
        return true;
    } 
    else
    {
        return false;
    }
}

uint32_t IsoActuator::getFrequency() const { return m_frequency; }

bool IsoActuator::setDutyCycle(const uint8_t value)
{
    if (value <  ISO_PWM_DUTY_CYCLE_MAX && value >  ISO_PWM_DUTY_CYCLE_MIN)
    {
        m_dutyCycle = value;
        return true;
    }
    else {
        return false;
    }
}

uint8_t IsoActuator::getDutyCycle() const { return m_dutyCycle; }

EquipmentState IsoActuator::getPwmState()
{
    return m_pwmState;
}
