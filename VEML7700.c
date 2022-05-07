#include "VEML7700.h"

int write_to_file(float Lux)
{
    FILE *fptr;
    while(1)
    { 
        //opening the file
        fptr = fopen("/tmp/light_intensity","w");
        //check if file opened successfully
        if(fptr == NULL)
        {
                printf("Error opening the file /tmp/light_intensity");
                return -1;
        }

        // gain = 1 and integration time = 100ms multiplication factor = 0.0576
        //float Lux = (float)read_light_intensity() * 0.0576;
        
        
        //writing light intensity to file
        if(fprintf(fptr,"Light Intensity : %0.2f Lux\n",Lux )<0)
        {   
                printf("error writing temperature to file \n");     
        }

        fclose(fptr);
        sleep(10);
    }
    return 0;
}

int configure()
{
    //writing 0x0000 to the configuration register i.e 0x00 

    uint8_t reg_addr = CONF_REG;
    uint8_t reg_data[2];
    reg_data[0] = 0x00;
    reg_data[1] = 0x00;
    uint8_t n_bytes = 2;
    uint8_t ret_val = i2c_write(SLAVE_ADDR, reg_addr ,reg_data, n_bytes);
    if(ret_val < 0)
    {
        printf("Fail to configure light sensor \n");
        return -1;
    }
}

uint16_t read_light_intensity()
{
    //Read ALS_REG
    uint8_t reg_addr = ALS_REG;
    uint8_t n_bytes = 2;
    uint8_t * p_ret_val = i2c_read(SLAVE_ADDR, reg_addr,n_bytes);
    if(p_ret_val == NULL)
    {
        printf("Fail to read light intensity\n");
        return NULL;
    }
    return ((uint16_t)(*(p_ret_val+1)) << 8 | *p_ret_val);
    
}

