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
    struct i2c_msg msg[2];
    unsigned char num_byte = 2;
    unsigned char num_msg = 2;

 
    //transfer data buffer
    unsigned char transfer_buffer[2];
    transfer_buffer[0]=0x00;
    transfer_buffer[1]=0x00;

    //receive data buffer
    unsigned char receive_buffer[2];
    receive_buffer[0]=0x00;
    receive_buffer[1]=0x00;


    //transfer msg
    msg[0].addr = 0x00;
    msg[0].flags = 0; //flag 0 for write
    msg[0].len = num_byte;
    msg[0].buf = transfer_buffer;


    // receive msg
    msg[1].addr = 0x04;
    msg[1].flags = I2C_M_RD;
    msg[1].len = num_byte;
    msg[1].buf = receive_buffer;

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