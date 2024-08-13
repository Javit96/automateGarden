#include "Arduino.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "_initboard.h"
#include "board.h"
#include "drivers/dhtxx/DHT.h"
#include "drivers/gpio/board_gpio.h"

volatile float temperature;
volatile float humi;
float phValue;
const int analogInPin = GPIO_PH4502;
const float phTrigger = 7.00;
int buf[10];
int temp = 0 ;
unsigned long int inValue;
DHT dht(GPIO_DHT,DHT22);



  
void readPHtread(void* param) {
  for(;;) {
    phValue = calculatePhValue();
  }
  
}

void readDHtread(void* param) {
  dht.begin();
  for(;;) {
    temperature = dht.readTemperature();
    humi = dht.readHumidity();
    
  }
}

void graphicsThread(void* param) {
  for(;;) {
   plotterFunc();
  }
  
}
void gpioThread(void* param){
  power_off_Lights();
  power_off_Pump();
  for(;;){
    checkPH();
    checkTemp();

  }
}

float calculatePhValue()
{
  float phValue = 0.0;
  for(int i=0; i<10; i++){
      buf[i]= analogRead(analogInPin);
      delay(10);
  }

  for(int i=0; i<9; i++)
  {
    for(int j=i+1; j<10;j++){
      temp = buf[i];
      buf[i]=buf[j];
      buf[j]=temp;
    }
  }
  inValue=0;
  for(int i=2; i<8; i++)
  {
    inValue= inValue + buf[i];
  }
  float PHVol= (float)inValue*100*3.3/4095.0/6;
  
  phValue = -0.0554*PHVol +22.236;;
  return phValue;
}

void checkTemp(){
  if(temp == 30)
  {
    power_on_Pump();
  }
}

void checkPH(){
  if(phValue == 12.00){
    setPHDown();
  }
  if(phValue==3.00){
    setPHUp();
  }
}
void plotterFunc(){
  Serial.print("PH:");

  Serial.print(phValue);

  Serial.print(",");

  Serial.print("Temperatura:");

  Serial.println(temperature);


}

