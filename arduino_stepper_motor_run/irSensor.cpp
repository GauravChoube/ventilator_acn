#include "irSensor.hpp"
#include <Arduino.h>

#define IR_PIN 6

int initIRsensor()
{
    pinMode(IR_PIN, INPUT);
    return 0;

}

bool getIRSensorValue()
{
    return digitalRead(IR_PIN);
}