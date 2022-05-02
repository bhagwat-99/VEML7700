#ifndef VEML7700_H
#define VEML7700_H

#include <stdio.h>
#include "I2C.h"

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define SLAVE_ADDR      0x10
#define ALS_REG         0x04;

#define CONF_REG 0x00

void configure();
int write_to_file();
uint16_t read_light_intensity();

 

#endif