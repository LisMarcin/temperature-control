#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <memory>

#include "Sensor.h"
#include "Case.h"

class Database
{
protected:
    std::vector <std::shared_ptr <Sensor>> sensors;
    bool connected=0;
public:
    virtual std::vector <std::shared_ptr <Sensor>> readsensors()=0; //read sensors from DB, and creates contener of sensors
    virtual int senddata(std::vector <std::shared_ptr <Sensor>>)=0; //return vector with cases that should be warned via email
    virtual std::vector <Case> Downloadcases()=0; //return vector with cases that should be warned via email
    virtual int how_many_exceed(std::string,int,std::string,float)=0; //name,how many, > or <,temperature, return number where condition > or < for given name and number of last inserts
    virtual ~Database(){};

};

#endif // DATABASE_H
