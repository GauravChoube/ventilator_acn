#include "currentSensor.hpp"
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;




int initPowerSensor()
{
    return ina219.begin();
}

float getCurrent()
{

  return ina219.getCurrent_mA();

}

float getVoltage()
{
    float shuntvoltage = 0;
  float busvoltage = 0;
  float loadvoltage = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  loadvoltage = busvoltage + (shuntvoltage / 1000);

  return loadvoltage;
}