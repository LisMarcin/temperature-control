#include "SensorManager.h"

void SensorManager::addsensors()
{
    std::vector <std::shared_ptr <Sensor>> tmp = dbase->readsensors();
    sensors.insert(sensors.end(),tmp.begin(),tmp.end());
}


void SensorManager::readsensors()
{
    for(unsigned int i=0; i<sensors.size(); ++i)
    {
    sensors[i]->readvalue();
    std::cout<<sensors[i]->r_name()<<" "<<sensors[i]->r_value()<<std::endl;
    }
}


void SensorManager::senddata()
{
    dbase->senddata(sensors);
}
