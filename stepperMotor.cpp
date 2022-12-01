#include<AccelStepper.h>

AccelStepper stepper;


const int stepPin = 3; 
const int dirPin = 4;

int p=400; //ml
int q=15;  //bpm 

float r = ((75 * p)/1350); //% of ambu bag compression

float s = ((r * 180)/75 ); //degrees for the rotation of stepper motor

float t = ((s * 200)/360); //steps for stepper motor
//float t;
float u = ((60/q) * 10000) - 10000;// time
int stepperMotorInit()
{

}

int stepperMotorSetStep(unsigned int stepValue)
{
    
}
unsigned int stepperMotorGetStep()
{
    digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  
    for(int x = 0; x < t; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(1000); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(1000); 
    }
    delay(1000);// One second delay
  
    digitalWrite(dirPin,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  
    for(int x = 0; x < t; x++) {
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(u);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(u);
    }
    delay(1000);

}

int stepperMotorSetSpeed(unsigned int speedValue)
{
  stepper.setSpeed(speedValue);
  Serial.println("Set Speed");
}

unsigned int stepperMotorGetSpeed( )
{  
  stepper.runSpeed();
  Serial.println("Get speed");
}

void stepperMotorStart()
{
  stepper.enableOutputs ();
}
void stepperMotorStop()
{
  stepper.disableOutputs ();
}
int stepperMotorReset()
{

}
int stepperMotorGetTorque()
{

}
int stepperMotorSetTorque()
{

}

int stepperMotorGetCurrentConsumption()
{

}

int stepperMotorGetCurrentVoltage()
{

}

void setup() {
 // stepperMotorSetSpeed();
  //stepperMotorGetSpeed();
  //stepperMotorGetStep();

  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

}

