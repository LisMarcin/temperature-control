#ifndef TEMPERATURECONTROL_H
#define TEMPERATURECONTROL_H

#include <iostream>
#include <vector>
#include <memory>

#include "Case.h"
#include "Database.h"
#include "Mailessentialserver.h"

class TemperatureControl
{
    Mailessentialserver smail;
    std::shared_ptr <Database> dbase;
    std::vector <Case> cases;
    std::vector <std::shared_ptr <Sensor>> sensors;

public:
    TemperatureControl(std::shared_ptr<Database> db){dbase = db;}
    void Download_cases(); //take cases from DB and put into vector cases
    void Download_sensors(); //download sensors from DB into vector sensors
    void control(); //check if case is true, then send mail using smail and execute command

};

#endif // TEMPERATURECONTROL_H
