#!/usr/bin/env bash

source .setupenv

sudo apt install st-util -yq

# Install ARM GCC
if [ ! -d $ARM_INSTALL ];
then 
    LINK=https://developer.arm.com/-/media/Files/downloads/gnu/11.3.rel1/binrel/arm-gnu-toolchain-11.3.rel1-x86_64-arm-none-eabi.tar.xz 
    mkdir -p $ARM_INSTALL && wget -q -O- $LINK | tar --strip-components=1 -C $ARM_INSTALL -Jxvf-
fi

