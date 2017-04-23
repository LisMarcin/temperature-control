# Temperature-control

Program is reading temperatures from DS1820 inserts into MySQL database, and if needed sending email with notification that temperature exceeded value.

Example database `rpi_temp_database`

## Getting started

To run this code you will need:

* Raspberry pi
* enabled 1-Wire (enabled in raspi-config and 2 entries in /etc/modules w1-gpio and w1-therm)
* MySQL database (see mysql_create for example base)
* g++-4.9
* configured mailx (on account that will run program, if mail is used)
* packet libmysqlclient-dev



### Contact
marcinlis1995@gmail.com