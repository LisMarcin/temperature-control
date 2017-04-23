#include "Mailessentialserver.h"

int Mailessentialserver::sendmail(std::string address,std::string title,std::string text)
{
    std::string mailcommand = "echo \""+text+"\" | mailx -s \""+title+"\" "+address;

    system(mailcommand.c_str());

    std::cout << mailcommand << std::endl;


return 0;
}
