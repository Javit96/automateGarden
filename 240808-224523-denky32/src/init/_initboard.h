#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "drivers/dhtxx/DHT.h"

void readPHtread(void* param);
void readDHtread(void* param);
void graphicsThread(void* param);
void gpioThread(void* param);


float calculatePhValue();
void plotterFunc();
void checkPH();
void checkTemp();