#include "isolatedBox_PID.h"

#ifdef ISO_PRINT_DEBUG
#include "isolatedBox_printdebug.h"
#endif // ISO_PRINT_DEBUG


 PidController::PidController()
     : m_parameterLimits(ISO_TEMP_MIN_SP, ISO_TEMP_MAX_SP, ISO_TEMP_SP_DEFAULT),
     m_setPointLimits(ISO_TEMP_MIN_SP, ISO_TEMP_MAX_SP, ISO_TEMP_SP_DEFAULT)
{
#ifdef ISO_PRINT_DEBUG
    ISO_printDebug::printDebug("InitializingP ID Controller");
#endif
    m_setPoint[PID_MIN_SET_POINT] = PID_SET_POINT_UNAVAILABLE;
    m_setPoint[PID_MAX_SET_POINT] = PID_SET_POINT_UNAVAILABLE;
    m_targetSetPoint = PID_SET_POINT_UNAVAILABLE;
    m_kp = 0.0;
    m_ki = 0.0;
    m_kd = 0.0;
    m_currentError = 0.0;

    init();
}


PidController::~PidController()
{
}

bool PidController::setPoints(temp_t _min, temp_t _max)
{
    bool lRetVal = false;
    if (testSetPoint(_min) == _min)
        if (testSetPoint(_max) == _max) {
            lRetVal = true;
            /// <summary>
            /// Test points are valid - We can set both
            /// The target set point by default is the Minimum one
            /// </summary>
            /// <param name="_min"></param>
            /// <param name="_max"></param>
            /// <returns></returns>
            setSetPoint(PID_MIN_SET_POINT, _min);
            setSetPoint(PID_MAX_SET_POINT, _max);
            m_targetSetPoint = getSetPoint(PID_MIN_SET_POINT);
            m_setPointLimits = ParameterLimits(_min, _max, _min);
        }
        else
        {
            /// <summary>
            /// In case of faillure we set both target points
            /// unavaialble
            /// </summary>
            /// <param name="_min"></param>
            /// <param name="_max"></param>
            /// <returns></returns>
            setSetPoint(PID_MIN_SET_POINT, PID_SET_POINT_UNAVAILABLE);
            setSetPoint(PID_MAX_SET_POINT, PID_SET_POINT_UNAVAILABLE);
            m_targetSetPoint = getSetPoint(PID_MIN_SET_POINT);
            m_setPointLimits = m_parameterLimits;
            lRetVal = false;
        }
    return lRetVal;
}

bool PidController::init()
{
    bool l_retVal = false;

    l_retVal = m_pwmActuator.init();

    /// <other_init>
    /// if needed we can set
    /// m_pwmActuator.setDutyCycle(...);
    /// m_pwmActuator.setFrequency(...);
    /// m_pwmActuator.setIntensity(...);
    /// </other_init>
    return l_retVal;
}

timeProcess_t PidController::Process(const temp_t _current) {
    // TO DO

    /// <summary>
    /// This is a dummy function
    /// Once the target has been changed we restart the
    /// PID compensation process by uisng this function
    /// </summary>
    /// <param name="_current"></param>
    /// <returns></returns>
    timeProcess_t lret{};
    
    // TO IMPLEMENT

    return lret;
}

temp_t PidController::testCurrentTemp(temp_t _curTemp)
{
    return m_setPointLimits.validate(_curTemp);
}


temp_t PidController::testSetPoint(const temp_t _input)
{
    return  m_parameterLimits.validate(_input);
}

temp_t PidController::getSetPoint(uint8_t _point) const
{ 
    if (-1 < _point < PID_MAX_NUM_POINTS) {
        return m_setPoint[_point];
    }
    else {
        return PID_SET_POINT_UNAVAILABLE;
    }
     
}

temp_t PidController::setTargetPoint(uint8_t _point)
{
    if (_point < PID_MAX_NUM_POINTS) {
        m_targetSetPoint = m_setPoint[_point];
        return m_targetSetPoint;
    }
    else {
        return PID_SET_POINT_UNAVAILABLE;
    }
}

temp_t PidController::setSetPoint(int _point, temp_t _setPoint)
{
    if ((-1 < _point) && (_point < PID_MAX_NUM_POINTS)) {
        m_setPoint[_point] = _setPoint;
        return _setPoint;
    }
    else {
        return PID_SET_POINT_UNAVAILABLE;
    }

}

void PidController::setKp(const temp_t _input)
{
    m_kp = m_parameterLimits.validate(_input);
}

temp_t PidController::getKp() const 
{ 
    return m_kp; 
}

void PidController::setKi(const temp_t _input)
{
    m_ki = m_parameterLimits.validate(_input);
}

temp_t PidController::getKi() const { return m_ki; }

void PidController::setKd(const temp_t _input)
{
    m_kd = m_parameterLimits.validate(_input);
}

temp_t PidController::getKd() const { return m_kd; }

temp_t PidController::getError(const temp_t _current)
{
    return m_currentError;
}

temp_t PidController::getProportional(const temp_t error)
{
    temp_t lret = m_kp;

    return lret;
}

temp_t PidController::getIntegral(const temp_t _error) {
    temp_t lret{};

    // TO IMPLEMENT

    return lret;
}

temp_t PidController::getDerivative(const temp_t error) {
    temp_t lret{};

    // TO IMPLEMENT

    return lret;
}

timeProcess_t PidController::getTransferFnctn(const temp_t pTemp, const temp_t iTemp,
    const temp_t dTemp)
{
    timeProcess_t lret{};

    // TO IMPLEMENT

    return lret;

}
