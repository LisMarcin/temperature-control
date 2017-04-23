#include "Case.h"

Case::Case(std::string email,std::string sensor,float tempmin,float tempmax,int howoften,std::string title,std::string content,std::string command)
{
    this->email=email;
    this->sensor=sensor;
    this->tempmin=tempmin;
    this->tempmax=tempmax;
    this->howoften=howoften;
    this->title=title;
    this->content=content;
    this->command=command;
}
