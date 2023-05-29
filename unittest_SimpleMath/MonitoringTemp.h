#ifndef MONITORINGTEMP_H
#define MONITORINGTEMP_H

#include "SharedQueue.h"

#include <sstream>
#include <vector>
#include <list>

typedef std::pair<std::string, std::string> MonitoringTemp;

template<typename T>
inline void insert(MonitoringTemp &o, const T &value, const std::string &unitOfMeasure)
{
    std::ostringstream oss;

    oss << value;
    o.push_front(std::pair<std::string, std::string>(oss.str(), unitOfMeasure));
}

template<>
inline void insert(MonitoringTemp &o, const std::string &value, const std::string &unitOfMeasure)
{
    o.first = value;
    o.second = unitOfMeasure;
//     o.push(std::pair<std::string, std::string>(value, unitOfMeasure));
}


typedef SharedQueue<MonitoringTemp> MonitoringDataQueue;

#endif // MONITORINGTEMP_H
