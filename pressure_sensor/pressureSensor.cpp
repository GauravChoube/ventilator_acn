#include <Arduino.h>
#include "pressureSensor.hpp"

const int HX_OUT_PIN = 4; //d2
const int HX_SCK_PIN = 5;  //d1


enum HX_MODE { NONE, DIFF_10Hz, TEMP_40Hz, DIFF_40Hz};
const byte HX_MODE = DIFF_40Hz;

int pressureSensorInit()
{ 
  //initiliased pressure sensor here. with library or direct code
  pinMode(HX_SCK_PIN, OUTPUT);
  pinMode(HX_OUT_PIN, INPUT);

  digitalWrite(HX_OUT_PIN,LOW);
Serial.begin(115200);
  return 0;
}

/// @brief 
/// @return 
long readHX() {

  // pulse clock line to start a reading
  for (char i = 0; i < HX_MODE; i++) {
    digitalWrite(HX_SCK_PIN, HIGH);
    digitalWrite(HX_SCK_PIN, LOW);
  }

  Serial.println("cp1");

  // wait for the reading to finish
  while (digitalRead(HX_OUT_PIN));

  // read the 24-bit pressure as 3 bytes using SPI
  byte data[3];
  for ( byte  j = 3; j>0;j--) {
    data[j] = shiftIn(HX_OUT_PIN, HX_SCK_PIN, MSBFIRST);
  }
  
Serial.println("cp2");

  data[2] ^= 0x80;  // see note

  // shift the 3 bytes into a large integer
  long result;
  result += (long)data[2] << 16;
  result += (long)data[1] << 8;
  result += (long)data[0];

    Serial.println("cp3");
 
  return result;
}

float getOutputPressureInPascal()
{
   return (200 * 0.00000029 * readHX()) + 500;
}


float getOutputPressure()
{
  float pressureH2o = 0;
 
  //get current raw value using library and convert into pascal,convert from pascal to cmH2o
        
        //1 cmh2o = 98.0665 pascal 
        //DO you calculation on calculated pascal.
        //pressureH2o=( 0.0000006071 * readHX()) + 5.1020;  // 200 * 0.00000029 * readHX() = 0.0000006071
        pressureH2o=readHX();


  return pressureH2o;

}