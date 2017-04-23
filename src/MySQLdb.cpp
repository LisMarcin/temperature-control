#include "MySQLdb.h"


MySQLdb::MySQLdb()
{
    mysql_init(&mysql);

    if(mysql_real_connect(&mysql,mysqladdress,mysqluser,mysqlpassword,mysqldb,0,NULL,0))
        connected = 1;
    else
        throw 1; //without base you cannot proceed
}


std::vector <std::shared_ptr <Sensor>> MySQLdb::readsensors()
{
    if(sensors.empty())
    {
    std::string query = std::string("SELECT * FROM ") + tabsensors + " where `" + tabsensors_type + "`='DS1820'";

    mysql_query(&mysql,query.c_str() );

    idquery = mysql_store_result(&mysql);
    while((row = mysql_fetch_row(idquery)) != NULL)
        sensors.push_back(std::make_shared<DS18B20>(row[2],row[1]));
    }

return sensors;
}


int MySQLdb::senddata(std::vector <std::shared_ptr <Sensor>> sensors)
{
    std::cout<<"These data will be sent"<<std::endl;
    for(unsigned int i=0; i<sensors.size(); ++i)
    {
        std::string query = std::string("INSERT INTO `")
        +tabdata
        +"`(`"+tabdata_counter+"`, `"+tabdata_name+"`, `"+tabdata_date+"`, `"+tabdata_temp

        +"`) VALUES (NULL,'"
        +sensors[i]->r_name()
        +"',NOW(),"
        +std::to_string(sensors[i]->r_value())
        +")";

        mysql_query(&mysql, query.c_str() );
        std::cout<<sensors[i]->r_name()<<" "<<sensors[i]->r_value()<<std::endl;
    }
    std::cout<<"Sent MySQL data"<<std::endl;
    return 0;
}

std::vector <Case> MySQLdb::Downloadcases()
{
    std::vector <Case> tmp;

    mysql_query(&mysql, (std::string("SELECT * FROM ")+tabcontrol).c_str() );

    idquery = mysql_store_result(&mysql);
    while((row = mysql_fetch_row(idquery)) != NULL)
        //0 - email 1 - sensor 2 - tempmin 3 - tempmax 4 - howoften 5 - title 6 - content 7 - command
        tmp.push_back(Case(row[0],row[1],atof(row[2]),atof(row[3]),atof(row[4]),row[5],row[6],row[7]));

    return tmp;
}

int MySQLdb::how_many_exceed(std::string name,int howoften,std::string sign,float temp)
{

    std::string query = std::string("SELECT count(*) FROM ( SELECT * FROM `")
    +tabdata+"` where `"+tabdata_name+"`='"+name+"' AND `"+tabdata_date+"` > DATE_SUB(NOW(), INTERVAL "+std::to_string(howoften)+" MINUTE) ORDER BY `"+tabdata_counter+"` DESC LIMIT 200000) AS sub where `"+tabdata_temp+"`"+sign+std::to_string(temp);

    mysql_query(&mysql,query.c_str() );

    idquery = mysql_store_result(&mysql);
    row = mysql_fetch_row(idquery);
    std::cout<<std::endl<<"How often:"<<row[0]<<std::endl;

    return atoi(row[0]);
}


MySQLdb::~MySQLdb()
{
    mysql_close(&mysql);
}
