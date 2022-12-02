#include "currentSensor.hpp"
#include "stepperMotor.hpp"
#include "flowSensor.hpp"
#include "input.hpp"
#include "iotApp.hpp"
#include "irSensor.hpp"
#include "pressureSensor.hpp"
#include "tftDisplay.hpp"
#include "ESP8266WiFi.h"


// WiFi parameters to be configured
const char* ssid = "admin"; // Write here your router's username
const char* password = "12345678"; // Write here your router's passward

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  
  Serial.print(F("Ventilator Debug is ready."));

  DisplayInit();
  Serial.print(F("TFT Display Initialised Successfully"));
  DisplayWelcomMsg();
  delay(2000);

}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
     Serial.println("No network detected");
  }
  
  else{
    Serial.println("");
    Serial.println("WiFi connected");
    // Turn the wifi status 'Online'
  }
  DisplayMainScreen(); //added here again because after clear screen it's gone otherwise
  DisplayDummyUpdate();
  delay(3000);
  
  DisplayCalibrationMsg();
  delay(3000);
  
  DisplayMainScreen(); //added here again because after clear screen it's gone otherwise
  DisplayDummyUpdate();
  delay(3000);
  
  DisplayErrorMsg("Pressure Sensor not found");
  delay(3000);
}