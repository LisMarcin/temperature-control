#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class Sensor
{

protected:
    std::string name;
    std::string type; //measurement unit e.g. celsius, degrees, percent
    std::string address;
    float value;

public:
    std::string r_name(){return name;}
    std::string r_type(){return type;}
    std::string r_address(){return address;}
    float r_value(){return value;}
    virtual float readvalue()=0;
    virtual ~Sensor(){};

};

#endif // SENSOR_H
