#include "pressureSensor.hpp"

void setup() {
  // put your setup code here, to run once:
  pressureSensorInit();
  Serial.begin(115200);

  Serial.println("pressure sensor initialised");

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print("pressure sensor value :");
  Serial.println(getOutputPressure());

  delay(1000);


}
