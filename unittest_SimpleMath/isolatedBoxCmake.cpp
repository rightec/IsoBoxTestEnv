/*****************************************************************//**
 * \file   isolatedBoxCmake.cpp
 * \brief: Main API class to manage a temperature controller
 * on a target device called "Box"
 *
 * \author F.Morani
 * \date   May 2023
***********************************************************************/

#include "isolatedBoxCmake.h"

using namespace isoBoxApi;


isoBox::isoBox()
{
    m_max_interval_temp = ISO_DEF_UNDEF_TEMP;
    m_min_interval_temp = ISO_DEF_UNDEF_TEMP;
    m_treshold_cmp_temp = ISO_DEF_TRSH__CMP_TEMP;
    m_Box_temp = ISO_DEF_UNDEF_TEMP;
    m_initDone = false;
}


bool isoBox::init(temp_t _min, temp_t _max)
{
    bool l_retVal = false;
    if (_max > _min) {
        /// <summary>
        /// PID has 2 set points. One for max and on for min
        /// </summary>
        /// <param name="_min"></param>
        /// <param name="_max"></param>
        /// <returns></returns>
        l_retVal = m_pidActuator.setPoints(_min, _max);   // init();
        m_initDone = l_retVal;
        return l_retVal;
    }
    else
        return l_retVal;
}
PID_SET_POINTS_t isoBoxApi::isoBox::getDistancePoint(temp_t _temp)
{
    PID_SET_POINTS_t lretVal = PID_MAX_NUM_POINTS;
    int lFirst = _temp - getSetPoint(PID_MIN_SET_POINT);
    int lSecond = _temp - getSetPoint(PID_MAX_SET_POINT);
    uint32_t labsFirst = abs(lFirst);
    uint32_t labsSecond = abs(lSecond);
    
    if (labsFirst < labsSecond) {
        // We choose the first
        lretVal = PID_MIN_SET_POINT;
    }
    else {
        if (labsFirst > labsSecond) {
            // We choose the second
            lretVal = PID_MAX_SET_POINT;
        }
        else {
            // Distance is the same. We do not have to change the target point
            lretVal = PID_MAX_NUM_POINTS;
        }
    }
    return lretVal;
}
temp_t isoBoxApi::isoBox::applyCompensation(temp_t _temp)
{   
    /// If it is out of range we should apply compensentaion
    
    temp_t lRetVal = ISO_DEF_UNDEF_TEMP;
    /// <summary>
    /// Here cames the measured temperature
    /// First we set the m_Box_temp to store the measured value
    /// </summary>
    /// <param name="_temp"></param>
    /// <returns></returns>
    m_Box_temp = _temp;

    if (m_initDone == true) {
        if (_temp == m_pidActuator.testCurrentTemp(_temp)) {
            /// <summary>
            /// We do not apply compensation because the temperature 
            /// is in the range
            /// </summary>
            /// <param name="_temp"></param>
            /// <returns></returns>
            lRetVal = ISO_DEF_UNDEF_TEMP;
        }
        else {
            /// <summary>
            /// We apply the compensation for temperature _temp
            /// we have to choose if we want to min or max 
            /// we calculate the distance
            /// </summary>
            /// <param name="_temp"></param>
            /// <returns></returns>
            PID_SET_POINTS_t lpointToSet = getDistancePoint(_temp);
            if (lpointToSet != PID_MAX_NUM_POINTS) {
                /// <summary>
                /// Set a new target point
                /// </summary>
                /// <param name="_temp"></param>
                /// <returns></returns>
                m_pidActuator.setTargetPoint(lpointToSet);                
            }
            lRetVal = m_pidActuator.m_targetSetPoint;
            m_pidActuator.Process(m_Box_temp);
            
        }
    }
    else {
        /// <summary>
        /// Could not apply compensation because
        /// set points are not set
        /// </summary>
        /// <param name="_temp"></param>
        /// <returns></returns>
        lRetVal = ISO_DEF_UNDEF_TEMP;
    }
    
    return lRetVal;  
}


