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
        

    bool getInitDone() { return m_initDone; };

    temp_t getSetPoint(int _point) { return m_pidActuator.getSetPoint(_point); }


    temp_t setTargetPoint(uint8_t _point) { return m_pidActuator.setTargetPoint(_point); }

    /**
    * @brief Returns the value of the target point
    * @return temp_t
    */
    temp_t getTargetPoint() { return m_pidActuator.m_targetSetPoint; }

    float applyCompensation(temp_t _temp);

    PID_SET_POINTS_t getDistancePoint(temp_t _temp);
   
private:
    temp_t m_max_interval_temp;
    temp_t m_min_interval_temp;
    temp_t m_treshold_cmp_temp;
    temp_t m_Box_temp;
    bool  m_initDone;
    
    PidController m_pidActuator;
};

};
#endif // !_ISO_BOX_CMAKE_H