#include <stdio.h>
#include "VEML7700.h"


const char *i2c_bus = "/dev/apalis-i2c1";

int main()
{
	//i2c initialize
    i2c_init(i2c_bus);

	configure();

	// float Lux = (float)read_light_intensity() * 0.0576;
	// printf("Lux : %.2f\n",Lux);

	//write Lux value to ram file
    write_to_file();
    
	// close the i2c bus
    i2c_close(i2c_bus);
    return 0;
}
