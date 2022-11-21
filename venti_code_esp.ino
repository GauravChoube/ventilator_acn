#include "currentSensor.hpp"
#include "stepperMotor.hpp"
#include "flowSensor.hpp"
#include "input.hpp"
#include "iotApp.hpp"
#include "irSensor.hpp"
#include "pressureSensor.hpp"
#include "tftDisplay.hpp"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print(F("Ventilator Debug is ready."));

  DisplayInit();
  Serial.print(F("TFT Display Initialised Successfully"));
  DisplayWelcomMsg();
  delay(2000);

  //display main page
  DisplayMainScreen();
}

void loop() {
  // put your main code here, to run repeatedly:
  // DisplayWelcomMsg();
  // DisplayMainScreen();
  DisplayDummyUpdate();
  delay(1000);

}
