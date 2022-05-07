#include <stdio.h>
#include "VEML7700.h"


const char *i2c_bus = "/dev/apalis-i2c1";

int main()
{
	//i2c initialize
	if(i2c_init(i2c_bus) < 0)
	{
		return -1;
	}

	if(configure()<0)
	{
		return -1;
	}

	// float Lux = (float)read_light_intensity() * 0.0576;
	// printf("Lux : %.2f\n",Lux);

	// read light intensity
	float Lux = (float)read_light_intensity() * 0.0576;

	//write Lux value to ram file
    write_to_file(Lux);
    
	// close the i2c bus
    if(i2c_close(i2c_bus)<0)
	{
		return -1;
	}
    return 0;
}
