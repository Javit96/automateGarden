#include <Arduino.h>
#include <drivers/dhtxx/DHT.h>
#include <board.h>
#include <init/_initboard.h>



void setup() {
  Serial.begin(9600);
  Serial.print("hello");

  pinMode(GPIO_PH4502, INPUT);
  pinMode(GPIO_PH_DOSIF_DOWN, OUTPUT);
  pinMode(GPIO_PH_DOSIF_UP, OUTPUT);
  pinMode(GPIO_PUMP, OUTPUT);
  


  xTaskCreatePinnedToCore(
    readDHtread,
    "dht reading",
    10000,
    NULL,//&dht,
    1,
    NULL,
    1
  );
  vTaskDelay(250 / portTICK_PERIOD_MS);
  // when this task starts, the reading goes infinite "nan"
  xTaskCreatePinnedToCore(
    readPHtread,
    "ph reading",
    10000,
    NULL,
    1,
    NULL,
    1
  );
  vTaskDelay(250 / portTICK_PERIOD_MS);

  xTaskCreatePinnedToCore(
    graphicsThread,
    "graphic",
    10000,
    NULL,
    1,
    NULL,
    1
  );
  vTaskDelay(250 / portTICK_PERIOD_MS);

  xTaskCreatePinnedToCore(
    gpioThread,
    "gpio thread",
    10000,
    NULL,//&dht,
    1,
    NULL,
    1
  );
  vTaskDelay(250 / portTICK_PERIOD_MS);
  

}





void loop() {
  vTaskDelete(NULL);
}