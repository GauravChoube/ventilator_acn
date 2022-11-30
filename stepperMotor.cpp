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

