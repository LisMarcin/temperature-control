#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <vector>
#include <memory>
#include <iostream>

#include "Sensor.h"
#include "Database.h"

class SensorManager
{

    std::shared_ptr <Database> dbase;
    std::vector <std::shared_ptr <Sensor>> sensors;

public:
    void addsensors(); //add from base to vector
    void readsensors(); //read data from sensors
    void senddata(); //send data to DB
    SensorManager(std::shared_ptr<Database> db){dbase = db;}
    ~SensorManager(){}

};

#endif // SENSORMANAGER_H
