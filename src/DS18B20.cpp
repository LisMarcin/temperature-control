#include "DS18B20.h"


DS18B20::DS18B20(std::string name,std::string address)
{
    type="°C";
    this->name=name;
    this->address=address;
    this->value=-105;
}


float DS18B20::readvalue()
{
    std::fstream file;
    file.open("/sys/bus/w1/devices/"+address+"/w1_slave", std::ios::in);

    if(!file.good())
    {
        //cannot open file
        file.close();
        value = -100;
        return -100;
    }

    std::string line;
    getline(file,line);

    if(line.length()<8 || line.substr(0,8)=="00 00 00")
    {
        file.close();
        value = -101;
        return -101;
    }

    if(line.length()<39 || !(line.substr(36,3)=="YES"))
    {
        file.close();
        value = -103;
        return -103;
    }

    getline(file,line);
    file.close();
    float temp=atof(line.substr(29,5).c_str())/1000;

    if(temp==85)//85 is default power-on reset value, usually wiring/pull-up problem
    {
        value = -102;
        return -102;
    }

    value=temp;
    return temp;
}
