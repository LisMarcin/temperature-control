#ifndef CASE_H
#define CASE_H

#include <string>

class Case
{
    std::string email;
    std::string sensor;
    float tempmin;
    float tempmax;
    int howoften;
    std::string title; // to mail
    std::string content; // to mail
    std::string command;

public:
    Case(std::string,std::string,float,float,int,std::string,std::string,std::string); //email,sensor,min,max,howoften,title,content,command
    std::string r_mail(){return email;}
    std::string r_sensor(){return sensor;}
    float r_tempmin(){return tempmin;}
    float r_tempmax(){return tempmax;}
    int r_howoften(){return howoften;}
    std::string r_title(){return title;}
    std::string r_content(){return content;}
    std::string r_command(){return command;}

};

#endif // CASE_H
