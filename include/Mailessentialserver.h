#ifndef MAILESSENTIALSERVER_H
#define MAILESSENTIALSERVER_H

#include <string>
#include <iostream>

class Mailessentialserver
{
    public:
        int sendmail(std::string,std::string,std::string); //address, title, text

};

#endif // MAILESSENTIALSERVER_H
