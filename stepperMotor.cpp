#include<AccelStepper.h>

AccelStepper stepper;

int speedValue;

const int stepPin = 3; 
const int dirPin = 4;

int p=400; //ml
int q=15;  //bpm 

float r = ((75 * p)/1350); //% of ambu bag compression

float s = ((r * 180)/75 ); //degrees for the rotation of stepper motor

float t = ((s * 200)/360); //steps for stepper motor
//float t;
float u = ((60/q) * 10000) - 10000;// time

void stepperMotorSetSpeed()
{
  stepper.setSpeed(1000);
  Serial.println("Set Speed");
}

void stepperMotorGetSpeed()
{  
  stepper.runSpeed();
  Serial.println("Get speed");
}

unsigned int stepperMotorGetStep()
{

  
}
void stepperMotorStart()
{
  stepper.enableOutputs ()
}
void stepperMotorStop()
{
  stepper.disableOutputs ()
}


int stepperMotorStop()

void setup() {
  stepperMotorSetSpeed();
  stepperMotorGetSpeed();
  stepperMotorGetStep();

  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

}

