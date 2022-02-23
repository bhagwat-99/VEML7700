#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

//sensor i2c address is 0x44
#define SLAVE_ADDR 0x10

void main()
{
    // Create I2C bus
        int file;
        char *bus = "/dev/apalis-i2c1";
        if((file = open(bus, O_RDWR)) < 0) 
        {
                printf("Failed to open the bus. \n");
                exit(1);
        }
        // Get I2C device, VEML7700 I2C address is 0x10-7BIT
        ioctl(file, I2C_SLAVE, SLAVE_ADDR);

        //unsigned char reg[1] = {0};
        //unsigned char data[2] ;
        __uint16_t reg_data;

        //configuring the register 0x00
        char config[3] = {0};
        config[0] = 0x00;
        config[1] = 0x00;
        config[2] = 0x00;
        write(file,config,3);
        sleep(1);
        //reading the result register 0x04
        unsigned char reg[1] = {0x04};
        write(file, reg, 1);
        sleep(1);
        unsigned char data[2] = {0};
        if(read(file, data, 2) != 2)
        {
                printf("Erorr : Input/output Erorr \n");
                exit(1);
        }
        printf(" data[0] %x\n data[1] %x\n",data[0],data[1]);
        close(file);
}
