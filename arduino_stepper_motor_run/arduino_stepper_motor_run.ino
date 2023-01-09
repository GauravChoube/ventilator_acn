#include <SoftwareSerial.h>
#include "stepperMotor.hpp"

#define rxPin 2
#define txPin 3

// Set up a new SoftwareSerial object
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

const int stepPin = 5;
const int dirPin = 4;

char c = 0;
char step[4];
char delaymil[10];
char cnt = 0;
char state = 0;
char indexU = 0;
char stepcnt = 0;
bool dataisready = 0;
bool motorResetRequested = 0;


char inhaleTimeStr[10];
long inHaleTime = 0;
char exhaleTimeStr[10];
long exHaleTime = 0;



long motordelayClock = 0;
long motordelayAntiClock = 0;
int motorStep;

static int ventilation = 0;
static bool inhaleStart = false;
static bool exhaleStart = false;




int runVentilator() {

  static int milliStart = 0;
  int currentStep = 0;


  // run for inhale action
  // start the motor positive direction with set step angle
  // inhale: capture inhale time
  if (ventilation == 0) 
  {
    if (inhaleStart == false) 
    {

      stepperMotorSetDelayForStep(motordelayClock);
      stepperMotorSetStep(motorStep);

      milliStart = millis() + inHaleTime;
      inhaleStart = true;

      Serial.print("\nVentilation:current time:");
      Serial.print(millis());
      Serial.print(("   Ventilation:Inhale End at:"));
      Serial.println(milliStart);
      Serial.println("Inhale Start\n==========\n");

      stepperMotorRun();

    }
    else 
    {
      ///Serial.println("a");
      if (milliStart >= millis()) 
      {
        currentStep = stepperMotordistanceToGo();

        if (currentStep != 0) 
        {

          stepperMotorRun();
          //Serial.println(currentStep);
        }
      } 
      else 
      {
        Serial.print(("Ventilation:Inhale Stop at step:"));
        Serial.println(stepperMotorGetStep());
        ventilation = 1;
        exhaleStart = false;
        milliStart = 0;
        inhaleStart = false;
      }
    }
  }else if (ventilation == 1) 
  {
    if (exhaleStart == false) 
    {

      stepperMotorSetDelayForStep(motordelayAntiClock);
      stepperMotorSetStep(-motorStep);

      milliStart = millis() + exHaleTime;
      exhaleStart = true;
      Serial.print("\nVentilation:current time:");
      Serial.print(millis());
      Serial.print("    Ventilation:exhale End:");
      Serial.println(milliStart);
      Serial.println("exhale Start\n==========\n");

      stepperMotorRun();

    } else 
    {
      //Serial.println("b");
      if (milliStart >= millis()) 
      {
        currentStep = stepperMotordistanceToGo();

        if (currentStep != 0) {


          stepperMotorRun();
          // Serial.println(currentStep);
        }
        //check the ir sensor to check back to zero position
      } else 
      {
        Serial.print("Ventilation:exhale Stop at step:");
        Serial.println(stepperMotorGetStep());
        ventilation = 0;
        exhaleStart = false;
        milliStart = 0;
        inhaleStart = false;
      }
    }
  }

  return 0;
}

void setup() {
  // Define pin modes for TX and RX
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);


  // Sets the two pins as Outputs
  // pinMode(stepPin, OUTPUT);
  // pinMode(dirPin, OUTPUT);
  stepperMotorInit();

  // Set the baud rate for the SoftwareSerial object
  mySerial.begin(4800);
  Serial.begin(115200);

  Serial.println("Soft arduino started");
}



void loop() {
  if (mySerial.available() > 0) {
    c = mySerial.read();
    //*msgtype;state;dir;step;delay#
    Serial.print(c);

    switch (c) {
      case '*':
        cnt = 0;
        memset(step, 0, 4);
        memset(inhaleTimeStr, 0, 10);
        memset(exhaleTimeStr, 0, 10);
        break;

      case ';':
        cnt++;
        indexU = 0;
        break;
      case '#':
        cnt = 10;
        dataisready = true;
        break;

      default:
        {
          //*msgtype;state;step;inhaletime;exhaletime#
          if (cnt == 0) {
             if((c-48)==0)
             {
                motorResetRequested=1;
             } 
          } else if (cnt == 1) {
            state = c - 48;
          } else if (cnt == 2) {
            step[indexU++] = c;
          } else if (cnt == 3) {
            inhaleTimeStr[indexU++] = c;
          } else if (cnt == 4) {
            exhaleTimeStr[indexU++] = c;
          }
        }
    }
  }

  if(motorResetRequested==1)
  {
      // right the logic for ir sensor here
      motorResetRequested=0;
  }
  else
  if (dataisready == true) {

    inHaleTime = atoi(inhaleTimeStr);
    exHaleTime = atoi(exhaleTimeStr);
    motorStep = atoi(step);

    motordelayClock = (inHaleTime * 1000) / (2 * motorStep);
    motordelayAntiClock = (exHaleTime * 1000) / (2 * motorStep);



    Serial.print("State: ");
    Serial.println(state, DEC);

    Serial.print("inhaleTime: ");
    Serial.println(inhaleTimeStr);

    Serial.print("exhaleTime: ");
    Serial.println(exhaleTimeStr);

    Serial.print("motorStep: ");
    Serial.println(motorStep);

    Serial.print("motordelayClock: ");
    Serial.println(motordelayClock);

    Serial.print("motordelayAntiClock: ");
    Serial.println(motordelayAntiClock);

    Serial.println("========");
    stepcnt = 0;
    dataisready = false;
  }

  if (state == 1) 
  {

    runVentilator();

  } else if (state == 0) 
  {
    ventilation = 0;
    exhaleStart = false;
    inhaleStart = false;
  }
}