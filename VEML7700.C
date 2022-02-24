#include <stdio.h> // printf()
#include <sys/types.h> // open()
#include <sys/stat.h> // open()
#include <fcntl.h> // open()
#include <sys/ioctl.h> // ioctl()
#include <errno.h> // errno
#include <string.h> // strerror()
#include <unistd.h> // close()
#include <linux/i2c-dev.h> // struct i2c_msg
#include <linux/i2c.h> // struct i2c_rdwr_ioctl_data

int main()
{
    struct i2c_msg msg[1];
    unsigned char num_byte = 2;
    unsigned char num_msg = 1;

    //data buffer
    unsigned char buffer[2];
    buffer[0]=0xf0;
    buffer[1]=0xff;

    //transfer msg
    msg[0].addr = 0x00;
    msg[0].flags = 0; //flag 0 for write
    msg[0].len = num_byte;
    msg[0].buf = buffer;

    struct i2c_rdwr_ioctl_data tranfer_data;
    tranfer_data.msgs = msg;
    tranfer_data.nmsgs = num_msg;
    

     // Open file descriptor to I2C bus
    int file = open("/dev/apalis-i2c1",O_RDWR);
    if(file<0) {
    printf("Failed to open apalis-i2c1.");
    return -1;
    }
    // With our file descriptor, perform I2C message transfers
    int result = ioctl(file,I2C_RDWR,&tranfer_data);
    if(result < 0)
    {
    printf("ioctl error: %s\n", strerror(errno));
    return -1;
    }
    
    close(file);

    return 0;
} 