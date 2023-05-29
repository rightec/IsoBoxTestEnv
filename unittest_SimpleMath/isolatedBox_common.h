/*****************************************************************//**
 * \file   isolatedBox_common.h
 * \brief: Common types, define and class to be used
 * in the ISOBOX component
 *
 * \author F.Morani
 * \date   May 2023
***********************************************************************/
#ifndef _ISO_COMMON_H_
#define _ISO_COMMON_H_

#include <chrono>
#include <cstdint>
#include <ctime>
#include <list>
#include <string>
#include <utility>


// Add Here any GPIO BASE ADDRESS
// Add here offsets of GPIO registers
// 
// Add here  the timeout for the event loop. 
#define ISO_SCAN_RATE 5 // milliseconds

// Maximum and minimum temperatures are in celsius
#define ISO_TEMP_MAX_SP 100
#define ISO_TEMP_MIN_SP 20
#define ISO_TEMP_SP_DEFAULT 20


/******************************************************************************
 * SOME TYPEDEF                                                    
 *****************************************************************************/
typedef float temp_t;

typedef std::chrono::milliseconds timeProcess_t;

typedef uint32_t freq_t;


enum EquipmentState
{
    DISABLED,
    ENABLED
};

/***********************************************
 *  A structure for holding a single data point *
 *  of temperature in degrees celsius, as well  *
 *  as the temp probe ID and a time stamp.      *
 ************************************************/

struct TempStruct
{
    time_t ts;
    std::string id;
    float temp;
};

enum TScale_E
{
    CELSIUS,
    FARENHEIT,
    KELVIN,
    MAX_VALUE_TSCALE
};

#define ISO_DEFAULT_TEMP_SCALE FARENHEIT

enum InputMode_E
{
    SETPOINT,
    SET_SCALE,
    LOAD_PROFILE,
    PID_TUNE,
    INPUT_MODE_MAX_VALUE
};

struct PidDataStruct
{
    std::string name;
    std::string description;
    float kP;
    float kI;
    float kD;
    float volume;
};

/**
 * @brief Used to define min/max/default values for a given parameter
 *
 */
class ParameterLimits
{
public:
    ParameterLimits(temp_t _min, temp_t _max, temp_t _defaultValue)
        : min(_min), max(_max), defaultValue(_defaultValue)
    {
    }

    temp_t validate(const temp_t _value)
    {
        temp_t returnValue = this->defaultValue;
        if (_value <= this->max && _value >= this->min)
            returnValue = _value;
        return returnValue;
    }

private:
    temp_t min;
    temp_t max;
    temp_t defaultValue;
};

#endif /* _ISO_COMMON_H_ */