#include "TemperatureControl.h"

void TemperatureControl::Download_cases()
{
    std::vector <Case> tmp = dbase->Downloadcases();
    cases.insert(cases.end(),tmp.begin(),tmp.end());
}

void TemperatureControl::Download_sensors()
{
    std::vector <std::shared_ptr <Sensor>> tmp = dbase->readsensors();
    sensors.insert(sensors.end(),tmp.begin(),tmp.end());
}


void TemperatureControl::control()
{

    float tempmin,tempmax,current_temp;
    std::string name;

for(unsigned int i=0; cases.size()>i; ++i)
{
    name=cases[i].r_sensor();
    tempmin=cases[i].r_tempmin();
    tempmax=cases[i].r_tempmax();

    for(unsigned int j=0; sensors.size()>j; ++j)
    {
        current_temp=sensors[j]->r_value();
        if(name==sensors[j]->r_name() && (tempmax < current_temp || (tempmin > current_temp && current_temp > -99) ))//under -100 error codes
        {
            if (tempmax < current_temp && dbase->how_many_exceed(name,cases[i].r_howoften(),">",tempmax)==1)
            {
                smail.sendmail(cases[i].r_mail(),cases[i].r_title(),cases[i].r_content()+"\n Current temp: "+std::to_string(current_temp)+"\n Condition temp: "+std::to_string(tempmax));
                if(cases[i].r_command()!="")
                system(cases[i].r_command().c_str());
            }

            if (tempmin > current_temp && dbase->how_many_exceed(name,cases[i].r_howoften(),"<",tempmin)==1)
            {
                smail.sendmail(cases[i].r_mail(),cases[i].r_title(),cases[i].r_content()+"\n Current temp: "+std::to_string(current_temp)+"\n Condition temp: "+std::to_string(tempmin));
                if(cases[i].r_command()!="")
                system(cases[i].r_command().c_str());
            }

        }

    }

}


}


