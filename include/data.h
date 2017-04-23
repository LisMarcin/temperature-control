#ifndef DATA_H
#define DATA_H

#define mysqluser "root"
#define mysqladdress "127.0.0.1"
#define mysqlpassword "password to MySQL"
#define mysqldb "rpi_temp_database"

#define tabsensors "sensors"
#define tabsensors_type "type"

#define tabdata "stored_temperatures"
#define tabdata_counter "counter"
#define tabdata_name "name"
#define tabdata_date "date"
#define tabdata_temp "temp"

#define tabcontrol "temp_control"


/*
[pi_base]

tabsensors[id,address,name,type]
tabcontrol[email,name,tempmin,tempmax,howoften //minutes//,title,content,command]
tabdata[counter,name,date,temperature]



error codes temp:
-100 cannot open file
-101 error 00 00 00
-102 initialization ds 85 or possibly wrong pull-up value
-103 error CRC
-104 //free(?)
-105 unread
*/



#endif // DATA_H

