#include "BMP280.h"


BMP280::BMP280(std::string name,std::string address)
{
    type="hPa";
    this->name=name;
    this->address=address;
    this->value=-105;
}

float BMP280::readvalue()
{
	using namespace std;
	
	//i2c init
	char *filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0)
	{
		cout<<"Failed to open the i2c bus";
		return -106;
	}

	if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
	{
		cout<<"Failed to acquire bus access and/or talk to slave.\n";
		return -106;
	}

	//setup 0xf4 data
	buffer[0]=0xF4;
	buffer[1]=f4;
	length = 2;
	if (write(file_i2c, buffer, length) != length)          
        {
			cout<<"Failed to write to the i2c bus.\n";
			return -106;
        }
	//setup 0xf5 data
	buffer[0]=0xF5;
	buffer[1]=f5;
	length = 2;
	if (write(file_i2c, buffer, length) != length)          
        {
			cout<<"Failed to write to the i2c bus.\n";
			return -106;
        }

	//read calibration
	buffer[0] = 0x88;
    length = 1 ;                    
    if (write(file_i2c, buffer, length) != length)          
    {
		cout<<"Failed to write to the i2c bus.\n";
		return -106;
    }
	length = 24; // in 8 bit addresses
	if (read(file_i2c, buffer16, length) != length)           
    {
		cout<<"Failed to read from the i2c bus.\n";
		return -106;
    }
    else
    {
    cal_T[0]=static_cast<uint16_t>(buffer16[0]); //table 17 datasheet, this value is unsigned
	cal_T[1]=buffer16[1];
	cal_T[2]=buffer16[2];	
	cal_P[0]=static_cast<uint16_t>(buffer16[3]); //table 17 datasheet, this value is unsigned
	cal_P[1]=buffer16[4];
	cal_P[2]=buffer16[5];
	cal_P[3]=buffer16[6];
	cal_P[4]=buffer16[7];
	cal_P[5]=buffer16[8];
	cal_P[6]=buffer16[9];
	cal_P[7]=buffer16[10];
	cal_P[8]=buffer16[11];
    }

	//read ADC
    buffer[0] = 0xf7;
    length = 1 ;                    
    if (write(file_i2c, buffer, length) != length)          
    {
		cout<<"Failed to write to the i2c bus.\n";
		return -106;
    }

	length = 6;			
	if (read(file_i2c, buffer, length) != length)	
	{
		cout<<"Failed to read from the i2c bus.\n";
		return -106;
	}
	else
	{
	adc_T=((int)buffer[5]>>4)+((int)buffer[4]<<4)+((int)buffer[3]<<12);
	adc_P=((int)buffer[2]>>4)+((int)buffer[1]<<4)+((int)buffer[0]<<12);
	}
		
	//temp
	double var1 = (((double)adc_T)/16384.0-((double)cal_T[0])/1024.0)*((double)cal_T[1]);
	double var2 = ((((double)adc_T)/131072.0-((double)cal_T[0])/8192.0)*(((double)adc_T)/131072.0-((double)cal_T[0])/8192.0))*((double)cal_T[2]);
	float tfine=var1+var2;

	//pressure
	var1 = ((double)tfine/2.0)-64000.0;
	var2 = var1*var1*((double)cal_P[5])/32768.0;
	var2 = var2+var1*((double)cal_P[4])*2.0;
	var2 = (var2/4.0)+(((double)cal_P[3])*65536.0);
	var1 = (((double)cal_P[2])*var1*var1/524288.0+((double)cal_P[1])*var1)/524288.0;
	var1 = (1.0+var1/32768.0)*((double)cal_P[0]);
	double p = 1048576.0 -(double)adc_P;
	p = (p-(var2/4096.0))*6250.0/var1;
	var1 = ((double)cal_P[8])*p*p/2147483648.0;
	var2 = p*((double)cal_P[7])/32768.0;
	p = p+(var1+var2+((double)cal_P[6]))/16.0;

	cout<<"Press: "<<p/100.0<<" hPa"<<endl;
	cout<<"Temp: "<<tfine/5120.0<<" C"<<endl;

	//pressure is Pa!!! displayed in hPa
	
	value=p/100.0;
	return p/100.0;
	
	
	
	
	
	
}