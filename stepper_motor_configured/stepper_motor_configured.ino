#include "stepperMotor.hpp"

int motorSpeed=10;
int inHaleTime=714;
int exHaleTime=2143;
int motorStep=200;


int runVentilator()
{
  static int ventilation = 0;
  static bool inhaleStart = false;
  static bool exhaleStart = false;
  static int milliStart = 0;
  int currentStep=0;

  // run for inhale action
  // start the motor positive direction with set step angle
  // inhale: capture inhale time
  if (ventilation == 0)
  {
    if (inhaleStart == false)
    {
      motorStep=50; //for 90 degree
      motorSpeed= 500000/100;
      //stepperMotorSetAcceleration(motorSpeed);
      stepperMotorSetStep(motorStep);
      stepperMotorSetSpeed(motorSpeed);
      milliStart = millis() + inHaleTime;
      inhaleStart = true;
      Serial.print(("Ventilation:Inhale Start:"));
      Serial.println(milliStart);
      Serial.print("Ventilation:current time:");
      Serial.println(millis());
      stepperMotorRun();
    }
    else
    {
       ///Serial.println("a");
      if (milliStart >= millis())
      {
        currentStep=stepperMotordistanceToGo();
        
        if (currentStep!=0)
        {
            stepperMotorRun();
            Serial.println(currentStep);
        }
      }
      else
      {
        Serial.print(("Ventilation:Inhale Stop at step:"));
        Serial.println(stepperMotorGetStep());
        ventilation = 1;
        exhaleStart = false;
        milliStart = 0;
        inhaleStart=false;
      }
    }
  }
  else if (ventilation == 1)
  {
    if (exhaleStart == false)
    {
      stepperMotorSetSpeed(motorSpeed);
      stepperMotorSetAcceleration(motorSpeed);
      stepperMotorSetStep(-motorStep);
      milliStart = millis() + exHaleTime;
      exhaleStart = true;

      Serial.print("Ventilation:exhale Start:");
      Serial.println(milliStart);
      Serial.print("Ventilation:current time:");
      Serial.println(millis());

      stepperMotorRun();
    }
    else
    {
      //Serial.println("b");
      if (milliStart >= millis())
      {
        currentStep=stepperMotordistanceToGo();

         if (currentStep!=0)
        {
            stepperMotorRun();
            Serial.println(currentStep);
        }
      }
      else
      {
        Serial.print("Ventilation:exhale Stop at step:");
        Serial.println(stepperMotorGetStep());
        ventilation = 0;
        exhaleStart = false;
        milliStart = 0;
        inhaleStart=false;
      }
    }
  }

  return 0;
}

 
void setup() {
  // Sets the two pins as Outputs
  Serial.begin(9600);
  Serial.println(F("Ventilator Debug is ready."));

  stepperMotorInit();
  stepperMotorSetStep(motorStep);
  stepperMotorSetDelayForStep(5000);   //total step=200 , time =1sec=1000000us, for each step time will be = 1000000/200=5000

  
}


void loop() {

  // runVentilator();
  // Serial.print(F("change the direction:"));
  //   Serial.println(stepperMotordistanceToGo());
  if(stepperMotordistanceToGo()==0)
  {
    Serial.print(F("change the direction:"));
    Serial.println(-stepperMotorGetStep());
    stepperMotorSetStep(-stepperMotorGetStep());
    
  }
  stepperMotorRun();
}