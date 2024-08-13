#include "Arduino.h"
#include "board.h"
#include "board_gpio.h"

void power_on_Pump(){
    digitalWrite(GPIO_PUMP, HIGH);
}

void power_off_Pump(){
    digitalWrite(GPIO_PUMP, LOW);
}

void setPHDown(){
    digitalWrite(GPIO_PH_DOSIF_DOWN, HIGH);
}

void setPHUp(){
    digitalWrite(GPIO_PH_DOSIF_UP, HIGH);
}

void power_on_Lights(){
    //digitalWrite(GPIO_PH_DOSIF_UP, HIGH);
}

void power_off_Lights(){
    //digitalWrite(GPIO_PH_DOSIF_UP, HIGH);
}