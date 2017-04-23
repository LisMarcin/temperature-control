#ifndef DS18B20_H
#define DS18B20_H

#include <cstdlib> //atof
#include <fstream> //files

#include "Sensor.h"


class DS18B20:public Sensor
{

public:
    DS18B20(std::string,std::string);// name,address
    float readvalue() override; //read from the file, return temp or error(as code eg. -102), save value

    };

#endif // DS18B20_H
