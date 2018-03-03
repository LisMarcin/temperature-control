#ifndef BMP280_H
#define BMP280_H

#include <unistd.h>			//I2C
#include <fcntl.h>			//I2C
#include <sys/ioctl.h>		//I2C
#include <linux/i2c-dev.h>	//I2C
#include <iostream>			//cout

#include "Sensor.h"


class BMP280:public Sensor
{

public:
    BMP280(std::string,std::string);// name,address
    float readvalue() override; //read from the file, return temp or error(as code eg. -102), save value

private:
	uint8_t addr = 0x76; //address
	int file_i2c;
	int length;
	uint8_t buffer[60];	
	int16_t buffer16[30];	
	uint8_t f4 = 0x4f; //010 011 11, temperature oversampling x2,pressure oversampling x4, mode normal
	uint8_t f5 = 0x80; //100  standby time 500ms  
	
	int adc_T = 0;
	int adc_P = 0;
	int cal_T[3];
	int cal_P[9];
	
	
    };

#endif // BMP280_H
