/*****************************************************************//**
 * \file   isolatedBox_PID.h
 * \brief: Class to manage a generic PID using 
 *  PWM modulation as actuation
 *
 * \author F.Morani
 * \date   May 2023
***********************************************************************/
#ifndef _ISOLATED_PID_H
#define _ISOLATED_PID_H

#include "isolatedBox_common.h"
#include "isolatedBox_actuator.h"

/// <summary>
/// PID could manage PID_MAX_NUM_POINTS set points
/// </summary>
typedef enum PID_SET_POINTS {
    PID_MIN_SET_POINT,
    PID_MAX_SET_POINT,
    PID_MAX_NUM_POINTS
}PID_SET_POINTS_t;

#define PID_SET_POINT_UNAVAILABLE       65535
/**
 * @brief Pid Processor 
 */
class PidController
{

public:
    /**
     * @brief Construct a new Pid Processor object
     */
    PidController();

    /**
     * @brief Destroy the Pid Processor object
     */
     ~PidController();

     /**
     * @brief PID controller initialization
     * @return: the result of initialization
     */
     bool init();

     /**
     * @brief Set APPLICATION set point
     * PID controller has 2 set point. We have to set both
     * @return true if the application set point are
     * both compatible with the Pysical set point. False if not
     */
     bool setPoints(temp_t _min, temp_t _max);

    /**
     * @brief restart the compensation process from the given 
     * temparature in input.
     * A real PID controller SHOULD BE IMPLEMENTED (TO DO)
     * @param current: given temperature
     * @return timeProcess_t
     */
     timeProcess_t Process(const temp_t current);

     /**
    * @brief Test if a temparature in input is in the
    * proper application range (use m_setPointLimits)
    * @param temp_t _curTemp: temperature to test
    * @return the same temperature to test if it is OK (in the range)
    */
     temp_t testCurrentTemp(temp_t _curTemp);

    /**
     * @brief Verify if the temperature is allowed in degrees ºC
     * Min/Max. Use m_parameterLimits.
     * This is relevant to the Physical limit of the PID controller
     * @param temp_t _setpoint: temperature to test
     * @return the same temperature to test if it is OK (in the range)
     */
     temp_t testSetPoint(const temp_t _setpoint);

    /**
     * @brief Get the process temperature set point
     * @param int _point - Index of the set point array
     * @return temp_t
     */
     temp_t getSetPoint(uint8_t _point) const;

     /**
     * @brief Set the target temperature to start
     * compensation process between the possible target set points
     * @param int _point - Index of the set point array
     * @return temp_t
     */
     temp_t setTargetPoint(uint8_t _point);


     /**
    * @brief Set the process temperature set point
    * @param int _point - Index of the set point array
    * #param temp_t _setPoint - Temperature to set
    * @return temp_t
    */
     temp_t setSetPoint(int _point, temp_t _setPoint);

    /**
     * @brief Set the proportional gain
     * Min/Max:
     * NOT USED
     */
     void setKp(const temp_t _k);

    /**
     * @brief Get the proportional gain
     * NOT USED
     * @return temp_t
     */
     temp_t getKp() const;

    /**
     * @brief Set the integral gain
     * Min/Max:
     * NOT USED
     */
     void setKi(const temp_t);

    /**
     * @brief Get the integral gain
     * NOT USED
     * @return temp_t
     */
     temp_t getKi() const;

    /**
     * @brief Set the derivative gain
     * Min/Max:
     * NOT USED
     */
     void setKd(const temp_t);

    /**
     * @brief Get the derivative gain
     * NOT USED
     * @return temp_t
     */
     temp_t getKd() const;

     /**
     * @brief The target set point of the device is one of the
       m_setPoint array
     */
     temp_t m_targetSetPoint;

private:
    /**
    * @brief The PWM class that manages actuation
    */
    IsoActuator m_pwmActuator;

    /**
     * @brief The set point is the desired process value.
     */
    temp_t m_setPoint[PID_MAX_NUM_POINTS];

    /**
     * @brief Proportional gain
     * Min / Max: 20ºC / 100ºC
     */
    temp_t m_kp;

    /**
     * @brief Integral gain
     * Min / Max: 20ºC / 100ºC
     */
    temp_t m_ki;

    /**
     * @brief Derivative gain
     * Min / Max: 20ºC / 100ºC
     */
    temp_t m_kd;

    /**
     * @brief Current temperature deviation from the set point
     */
    temp_t m_currentError;

    /// <summary>
    /// m_parameterLimits store the pyhisical temperature interval
    /// m_setPointLimits store the application temperature interval
    /// </summary>
    ParameterLimits m_parameterLimits;
    ParameterLimits m_setPointLimits;

    /**
     * @brief Get temperature error
     * NOT USED
     * @param current - current temperature 
     * @return temp_t - temperature error e(t)
     */
    temp_t getError(const temp_t _current);

    /**
     * @brief Get the proportional adjustment
     * NOT USED
     * @param error - temperature error e(t)
     * @return temp_t - Proportional temperature adjustment
     */
    temp_t getProportional(const temp_t _error);

    /**
     * @brief Get the integral adjustment
     * NOT USED
     * @param error - temperature error e(t)
     * @return temp_t - Integral temperature adjustment
     */
    temp_t getIntegral(const temp_t _error);

    /**
     * @brief Get the Derivative object
     * NOT USED
     * @param error - temperature error e(t)
     * @return temp_t - Derivative temperature adjustment
     */
    temp_t getDerivative(const temp_t _error);

    /**
     * @brief Get the transfer function result
     * NOT USED
     * @param pTemp - Proportional adjustment
     * @param iTemp - Integral adjustment
     * @param dTemp - Derivative adjustment
     * @return timeProcess_t
     */
    timeProcess_t getTransferFnctn(const temp_t _pTemp, const temp_t _iTemp,
       const temp_t _dTemp);
};


#endif // _ISOLATED_PID_H