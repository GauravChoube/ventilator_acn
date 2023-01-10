#include<AccelStepper.h>

int maximumStepOfMotor=200;
const int stepPin = 2; 
const int dirPin = 12;


// #define motorInterfaceType 1
// AccelStepper stepper(motorInterfaceType, stepPin, dirPin);


// // ULN2003 Motor Driver Pins
// #define IN1 8
// #define IN2 9
// #define IN3 10
// #define IN4 11

// initialize the stepper library
// AccelStepper stepper(AccelStepper::HALF4WIRE, IN1, IN3, IN2, IN4);/

// int p=400; //ml
// int q=15;  //bpm 

// float r = ((75 * p)/1350); //% of ambu bag compression

// float s = ((r * 180)/75 ); //degrees for the rotation of stepper motor

// float t = ((s * 200)/360); //steps for stepper motor
// //float t;
// float u = ((60/q) * 10000) - 10000;// time

int currentStep=0;
int targetStep=0;
int delayAsSpeed=0;
int dir=0;

int stepperMotorInit()
{
  // stepper.setMaxSpeed(1020);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  return 0;
}

int stepperMotorSetStep(int stepValue)
{
  //  stepper.moveTo(stepValue);

  // Serial.begin(9600);

  if(stepValue <0)
  {
    dir=-1;
    // Serial.println(F("-ve direction:"));
    //anticlockwise direction
      digitalWrite(dirPin, LOW);
  }
  else
  {
    // Serial.println(F("+ve direction:"));
    //clokcwise direction
     digitalWrite(dirPin, HIGH);
     dir=1;
  }

  targetStep=abs(stepValue);
  currentStep=0;
   return 0;
}


int stepperMotorGetStep()
{
  //  return stepper.currentPosition();
  if(dir==1)
    return currentStep;
  else
    return -currentStep;
}

int stepperMotordistanceToGo()
{
  //  return stepper.distanceToGo();
  return (targetStep-currentStep);
}

int stepperMotorSetSpeed(unsigned int speedValue)
{
  // stepr per second
  // stepper.setSpeed(speedValue);

  //set delay between pin high and pin low on step pin
  delayAsSpeed=(speedValue)/2;
  return 0;
}

int stepperMotorSetDelayForStep(unsigned int delayinMicrosecond)
{
  // stepr per second
  // stepper.setSpeed(speedValue);

  //set delay between pin high and pin low on step pin
  delayAsSpeed=(delayinMicrosecond)/2;
  return 0;
}

int stepperMotorSetAcceleration(unsigned int accel)
{
    //stepper.setAcceleration(accel);
    return 0;
}

unsigned int stepperMotorGetSpeed( )
{  
  // return stepper.speed();

  //set delay between pin high and pin low on step pin
  return delayAsSpeed*2;

}

void stepperMotorStart()
{
  // stepper.enableOutputs ();
}

void stepperMotorStop()
{

  // stepper.disableOutputs ();
  currentStep=0;
  targetStep=0;
  digitalWrite(stepPin,LOW);

}

int stepperMotorRun()
{
  // return stepper.run();
  if(currentStep<=targetStep)
  {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(delayAsSpeed); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(delayAsSpeed);
    currentStep++;
  }
  return currentStep;
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

