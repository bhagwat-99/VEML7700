#!/bin/bash

#configuration register 0x00
#IT(ms)=100 ALS_GAIN =1 Resolution - 0.0576
i2cset -y 4 0x10 0x00 0x0000 w
multi_factor=0.0576 #resolution

reg_value=$(printf "%d\n" $(i2cget -y 4 0x10 0x04 w))

echo "$reg_value*$multi_factor" | bc
