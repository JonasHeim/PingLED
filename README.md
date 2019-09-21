Work in progress

# PingLED

Display the latency/delay to an internet node (e.g. Google) on a 7-segment display using a ESP8266 interfacing a TM1637.

Using the [ESP8266_NON_OS_SDK](https://github.com/espressif/ESP8266_NONOS_SDK)

## Compile application using make:
```
cd ./PingLED
make 
```
Change the variables
- COMPILE
- BOOT
- APP
- SPI_SPEED
- SPI_MODE

in ./PingLED/Makefile according to your configuration.
For additional information about the configuration see the [Expressif documentation](https://github.com/espressif/ESP8266_NONOS_SDK/tree/master/examples).

## Clean application:
```
cd ./PingLED
make clean
```

  ## Project structure:
  * ESP8266
    - Source code for the firmware on ESP8266
  * Documentation
    - Datasheets for TM1637
    - ESP8266 SDK documentation
