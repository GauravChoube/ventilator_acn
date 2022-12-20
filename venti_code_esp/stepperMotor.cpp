#include<AccelStepper.h>

int maximumStepOfMotor=200;
const int stepPin = 2; 
const int dirPin = 12;


#define motorInterfaceType 1
AccelStepper stepper(motorInterfaceType, stepPin, dirPin);


// int p=400; //ml
// int q=15;  //bpm 

// float r = ((75 * p)/1350); //% of ambu bag compression

// float s = ((r * 180)/75 ); //degrees for the rotation of stepper motor

// float t = ((s * 200)/360); //steps for stepper motor
// //float t;
// float u = ((60/q) * 10000) - 10000;// time

int stepperMotorInit()
{

}

int stepperMotorSetStep(int stepValue)
{
   stepper.moveTo(stepValue);
   return 0;
}


int stepperMotorGetStep()
{
   return stepper.currentPosition();
}

int stepperMotordistanceToGo()
{
   return stepper.distanceToGo();
}

int stepperMotorSetSpeed(unsigned int speedValue)
{
  stepper.setSpeed(speedValue);
  return 0;
}

int stepperMotorSetAcceleration(unsigned int accel)
{
    stepper.setAcceleration(accel);
    return 0;
}

unsigned int stepperMotorGetSpeed( )
{  
  return stepper.speed();

}

void stepperMotorStart()
{
  stepper.enableOutputs ();
}

void stepperMotorStop()
{

  stepper.disableOutputs ();
}

int stepperMotorRun()
{
  return stepper.run();
}

int stepperMotorReturnInitialPosition()
{
  
  return 0;

}

int stepperMotorReset()
{
  
  return 0;

}
int stepperMotorGetTorque()
{

  return 0;

}
int stepperMotorSetTorque()
{

  return 0;
}

int stepperMotorGetCurrentConsumption()
{

  return 0;

}

int stepperMotorGetCurrentVoltage()
{
  return 0;
}

