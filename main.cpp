#include <iostream>
#include <memory>

#include "SensorManager.h"
#include "MySQLdb.h"
#include "TemperatureControl.h"

using namespace std;

int main()
{

    try
    {
    std::shared_ptr<MySQLdb> base (new MySQLdb);

    SensorManager manager(base);
        manager.addsensors();
        manager.readsensors();
        manager.senddata();

    TemperatureControl tcontrl(base);
        tcontrl.Download_cases();
        tcontrl.Download_sensors();
        tcontrl.control();
    }

    catch(...)
    {
    exit(-1);
    }

    return 0;
}
