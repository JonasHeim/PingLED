#!/bin/bash

export SDK_PATH=$(pwd)"/../ESP8266_RTOS_SDK-2.0.0/"
export BIN_PATH=$(pwd)"/bin/"

echo $SDK_PATH
echo $BIN_PATH

#variables, that are normally exported by gen_misc.sh
BOOT=none
APP=0
SPI_SPEED=40
SPI_MODE=QIO
SPI_SIZE_MAP=2

make clean

make BOOT=$boot APP=$app SPI_SPEED=$spi_speed SPI_MODE=$spi_mode SPI_SIZE_MAP=$spi_size_map
