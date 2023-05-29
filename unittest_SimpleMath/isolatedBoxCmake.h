/*****************************************************************//**
 * \file   isolatedBoxCmake.h
 * \brief: Main API class to manage a temperature controller
 * on a target device called "Box"
 *
 * \author F.Morani
 * \date   May 2023
***********************************************************************/
#ifndef  _ISO_BOX_CMAKE_H
#define  _ISO_BOX_CMAKE_H

#include <iostream>
#include "isolatedBox_PID.h"  // include class to manage actuation

constexpr auto ISO_DEF_UNDEF_TEMP = 65535;
constexpr auto ISO_DEF_TRSH__CMP_TEMP = 0.1;

using namespace std;

namespace isoBoxApi {

class isoBox {
public:

    /**
    * @brief Constructor: Member initialization
    */
    isoBox(); 
    
    /**
    * @brief Destructor
    */
    ~isoBox() {};

    /**
     * @brief Initialization of the monitoring device system
     * @param: temp_t _min - Minimum temperarure treshold request
     * @param: temp_t _max - Maximum temperarure treshold request
     * @return true if the init is OK
     */
    bool init(temp_t _min, temp_t _max); 
        
    /**
     * @brief: just return the value of the initialization process
     * @return boolean
     */
    bool getInitDone() { return m_initDone; };

    /**
     * @brief: Get one of the set point of the PID controller
     * @param: int _point: Index of the arry 
     * @return The value (temperature) of the requested set point
     */
    temp_t getSetPoint(int _point) { return m_pidActuator.getSetPoint(_point); }

    /**
     * @brief: Set the target set point for the PID controller
     * selected from the set point array
     * @param: int _point: Index of the array  (see PID_SET_POINTS)
     * @return The value (temperature) of the set set point
     * if not set return PID_SET_POINT_UNAVAILABLE
     */
    temp_t setTargetPoint(uint8_t _point) { return m_pidActuator.setTargetPoint(_point); }

    /**
    * @brief Returns the value of the current target point
    * @return temp_t
    */
    temp_t getTargetPoint() { return m_pidActuator.m_targetSetPoint; }

    /**
    * @brief Restart the compensation process if the 
    * temperature measured in ouside the range
    * @return the target point set (temperature value) or 
    * ISO_DEF_UNDEF_TEMP if the compensation is not possible
    */
    temp_t applyCompensation(temp_t _temp);

   
private:
    temp_t m_Box_temp;
    bool  m_initDone;
    
    PidController m_pidActuator;

    /**
    * @brief Calculate the suitable target point to select
    * from a given temperature as input
    * @return the array index of target set point array
    */
    PID_SET_POINTS_t getDistancePoint(temp_t _temp);
};

};
#endif // !_ISO_BOX_CMAKE_H