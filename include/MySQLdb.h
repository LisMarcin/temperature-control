#ifndef MYSQLDB_H
#define MYSQLDB_H

#include <mysql/mysql.h>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "Database.h"
#include "data.h"
#include "DS18B20.h"
#include "Sensor.h"

class MySQLdb:public Database
{
    MYSQL mysql;
    MYSQL_RES *idquery;
    MYSQL_ROW  row;
public:
    std::vector <std::shared_ptr <Sensor>> readsensors() override; //read sensors from DB, and creates contener of sensors
    int senddata(std::vector <std::shared_ptr <Sensor>>) override; //0 == correct, send data from Sensors to DB
    std::vector <Case> Downloadcases() override; //return vector with cases that should be warned via email
    int how_many_exceed(std::string,int,std::string,float) override; // name,how many, > or <,temperature, return number where condition > or < for given name and number of last inserts
    MySQLdb();
    ~MySQLdb();

};

#endif // MYSQLDB_H
