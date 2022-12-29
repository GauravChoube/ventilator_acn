#include "currentSensor.hpp"
#include "stepperMotor.hpp"
#include "flowSensor.hpp"
#include "input.hpp"
#include "iotApp.hpp"
#include "irSensor.hpp"
#include "pressureSensor.hpp"
#include "tftDisplay.hpp"

int rval = 0xff;
int currentBOXcounter = 0;
int boxCursorMove = 0;
static int blinkStatus = 0;
static bool displayStatusDone = 0;

int powerSwitchValue = 0;
int currentPowerSwitchValue = 0;
int turnONVentilator=0;
int turnOFFVentilator=0;

int curentLeftButtonValue = 0;
int currentRightButtonValue = 0;
int currentPotValue = 0;

int pressureInputValue = 0;
int pressureOutputValue = 0;

int bmpInputValue = 0;

int tidalVolumeInput = 0;
int tidalVolumeOutput = 0;

int ieratioHardcode = 4;

int motorSpeed = 0;
int motordelayClock = 0;
int motordelayAntiClock = 0;
int motorStep = 0;
int oneCycleTime = 0;
int inHaleTime = 0;
int exHaleTime = 0;

bool callibration = false;
bool callibrationDone=false;
bool ventilatorIsRunning=false;

int fetchInput()
{
  // Serial.println("reading LeftButtonValue:");
  int buttonValue = 0;

  buttonValue = getLeftButtonValue();
  if (buttonValue != curentLeftButtonValue)
  {

    curentLeftButtonValue = buttonValue;

    Serial.print(("LeftButtonValue:"));
    Serial.print(curentLeftButtonValue);

    if (curentLeftButtonValue == 1)
    {
      boxCursorMove = 1;

      if (currentBOXcounter == 0)
        currentBOXcounter = 3;
      else
        currentBOXcounter--;

      if (currentBOXcounter == 2)
        currentBOXcounter = 1;

      Serial.print(("   currentBOXcounter:"));
      Serial.println(currentBOXcounter);
    }
  }

  buttonValue = getRightButtonValue();
  // Serial.println("reading rightButtonValue:");
  if (buttonValue != currentRightButtonValue)
  {

    currentRightButtonValue = buttonValue;

    Serial.print(("RightButtonValue:"));
    Serial.print(currentRightButtonValue);

    if (currentRightButtonValue == 1)
    {
      boxCursorMove = 1;
      if (currentBOXcounter == 3)
        currentBOXcounter = 0;
      else
        currentBOXcounter++;

      if (currentBOXcounter == 2)
        currentBOXcounter = 3;

      Serial.print(("   currentBOXcounter:"));
      Serial.println(currentBOXcounter);
    }
  }
  // Serial.println("reading stopstartButtonValue:");

  int buttonVal = getStartStopButtonValue();
  if (buttonVal != powerSwitchValue)
  {
    powerSwitchValue = buttonVal;
    if (powerSwitchValue == 0)
    {
      currentPowerSwitchValue ^= 0x01;

      if(currentPowerSwitchValue==1)
          turnONVentilator=1;
      else if(currentPowerSwitchValue==0)
          turnOFFVentilator=1;
          
      displayStatusDone = 0;
    }
  }

  // Serial.println("reading pot Value:");
  currentPotValue = getPotValue();

  // Serial.print(("LeftButtonValue:"));
  // Serial.println(curentLeftButtonValue);

  //  Serial.print(("RightButtonValue:"));
  // Serial.println(currentRightButtonValue);

  //  Serial.print(("PowerButtonValue:"));
  // Serial.println(powerSwitchValue);

  //  Serial.print(("PoTValue:"));
  // Serial.println(currentPotValue);

  // Serial.print(("currentBOXcounter:"));
  // Serial.println(currentBOXcounter);

  return 0;
}

float psCovertPotValue(int potValue)
{
  // as pressure should be in range of 5 to 30 cmH2o , we can have range from 0 to 50
  return map(potValue, 0, 1023, 0, 50); //(potValue/20);
}

float bpmCovertPotValue(int potValue)
{
  // as bpm should be in range of 8 to 25, we can have range from 0 to 40
  return map(potValue, 0, 1023, 0, 40); //(potValue/25);
}

float tvCovertPotValue(int potValue)
{
  // as tidal volume should be in range of 100 to 800 ml/kg, we can have range from 0 to 1023
  return map(potValue, 0, 1023, 0, 1000);
}

float convertInputValueInSensorRange(int boxIndex, int potValue)
{
  float rval = 0;

  if (boxIndex == 0)
  {
    // covert pot value to input pressure
    // Serial.println("0");
    rval = pressureInputValue = psCovertPotValue(potValue);
  }
  else if (boxIndex == 1)
  {
    // Serial.println("1");
    rval = bmpInputValue = bpmCovertPotValue(potValue);
  }
  else if (boxIndex == 2)
  {
  }
  else if (boxIndex == 3)
  {
    // Serial.println("3");
    rval = tidalVolumeInput = tvCovertPotValue(potValue);
  }
  return rval;
}

int blinkAndUpdateBox(int boxIndex, float boxValue)
{
  static int currentBlinker = 0;
  static unsigned int BlinkCounter = 0;
  static int prevBoxValue;

  if (boxIndex != currentBlinker)
  {
    BlinkCounter = 0;
    updateBoxValue(currentBlinker, prevBoxValue);
    currentBlinker = boxIndex;
  }

  if (millis() % 100 == 0)
  {

    if (blinkStatus == 0)
    {
      // box will be disappeared
      deleteBox(boxIndex);
    }
    else
    {
      // box will be appeared with value
      updateBoxValue(boxIndex, boxValue);
      prevBoxValue = boxValue;
    }
    blinkStatus ^= 0x01;
  }

  return 0;
}

int updateDisplay()
{
  float potCovertValue = 0;

  // Box cursor movement
  if ((blinkStatus == 1) || (boxCursorMove == 1 && currentPowerSwitchValue == LOW))
  {
    // Serial.println("checkpoint 1");
    // get input value and convert into respective in range
    potCovertValue = convertInputValueInSensorRange(currentBOXcounter, currentPotValue);

    // Serial.println("checkpoint 2");
    // update box with input value
    blinkAndUpdateBox(currentBOXcounter, potCovertValue);
  }
  else
  {
    // display error message
    if (boxCursorMove == 1 && currentPowerSwitchValue == HIGH)
    {
      // Serial.println("checkpoint 3");
      Serial.print(F("INput cannot set when Ventilator is ON"));
      DisplayErrorMsg("Input can't set if Device is ON");
      delay(1000);
      boxCursorMove = 0;
    }
    else
    {
      // Serial.println("checkpoint 5");
      // Update output Box with value
      boxCursorMove = 0;
    }
  }

  // update Status of operation
  if (currentPowerSwitchValue == HIGH)
  {
    if (displayStatusDone == 0)
    {
      
      DisplayStatus("ON");
      displayStatusDone = 1;
      Serial.println("Ventilator Start\n====================\n");
    }
  }
  else
  {

    if (displayStatusDone == 0)
    {
     
      DisplayStatus("OFF");
      displayStatusDone = 1;
       Serial.println("====================\nVentilator Stop\n");
    }
  }

  // Update IOT status

  return 0;
}

int getOuputPressure()
{

  return 0;
}

int getOuputFlow()
{

  return 0;
}

int getOuputVolume()
{

  return 0;
}

int updateMotorParameter()
{
  // set speed of motor

  // set step of motor

  return 0;
}

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
      // stepperMotorSetSpeed(motorSpeed);

      // stepperMotorSetAcceleration(motorSpeed);
      stepperMotorSetDelayForStep(motordelayClock);
      stepperMotorSetStep(motorStep);
      milliStart = millis() + inHaleTime;
      inhaleStart = true;
      
      Serial.print("Ventilation:current time:");
      Serial.print(millis());
      Serial.print(("   Ventilation:Inhale End at:"));
      Serial.println(milliStart);
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
        inhaleStart=false;
      }
    }
  }
  else if (ventilation == 1)
  {
    if (exhaleStart == false)
    {
     
      stepperMotorSetDelayForStep(motordelayAntiClock);
      stepperMotorSetStep(-motorStep);
      milliStart = millis() + exHaleTime;
      exhaleStart = true;
      Serial.print("Ventilation:current time:");
      Serial.print(millis());
      Serial.print("    Ventilation:exhale End:");
      Serial.println(milliStart);

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
           // Serial.println(currentStep);
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

int doCallibration()
{

  // read/fetch the output value :
  // 1. fetch the output pressure
  // 2. fetch the output volume
  // 3. fetch flow rate

  // generate deviation in set parameter as well as output parameter

  // calculate the stepper motor input like speed, step, inhales:exhales timing
  // calculate the ON time and OFF time base on BPM as well as IE ratio
  // example,consier maximum bpm =30 mean 1breath will take 2sec
  //      oneCycleTime=2000
  //      inHaleTime=500
  //      exHaleTime=1500
  oneCycleTime = (60000) / bmpInputValue;
  inHaleTime = oneCycleTime / ieratioHardcode;
  exHaleTime = oneCycleTime - inHaleTime;


  // calculate step angle
  /*
    Bag compress about 75% by using our mechanics which exhale the almost 1350ml volume of air.
    To achieve, motor need to rotate 180 degree(nothing but half of total steps of stepper motor).
    As per maximum volume support for human ventilator is range from 100-800ml only.
    example:
      step of motor =200
      total step require to rotate for 1350ml(180 degree) of air  = 100 (total step/2).
      step require to rotate for X ml of air
      1350      ---> 100
      X(input)  ---> steps                = (100*X)/1350 = 0.07408 * X
  */
  motorStep = 0.07408 * tidalVolumeInput;

  // calculate the speed and delya between each step while rotationg clockwise and anti-clock wise
  motorSpeed = 200;
  motordelayClock = (inHaleTime*1000)/(2*motorStep);
  motordelayAntiClock = (exHaleTime*1000)/(2*motorStep);

  // set all value of step ,speed to stepper motor as well as IE value into variable
  updateMotorParameter();

  return 0;
}

int startVentilator()
{
  stepperMotorStart();
  return 0;
}

int stopVentilator()
{
  stepperMotorStop();
  return 0;
}

void setup()
{

  // Serial Uart Initialised
  Serial.begin(9600);
  Serial.println(F("Ventilator Debug is ready."));

  // Display Initialised
  DisplayInit();
  Serial.println(F("TFT Display Initialised Successfully"));
  DisplayWelcomMsg();

  // stepper motor Initialised and reset motor

  // Input Initialised
  Serial.println("Input initialised");
  inputInit();

  // pressure sensor Initialised

  // flow sensor Initialised

  // current sensor Initialised

  // IOT application Initialised

  delay(2000);
  // display main page
  DisplayMainScreen();

  Serial.println(F("Ventilator is initialised"));
}

void loop()
{

  // DisplayDummyUpdate();
  // delay(1000);

  /****************************
   *   Get sync the all data
   *****************************/
  // sync the input switch value
  rval = fetchInput();
  if (rval != 0)
  {
    Serial.println("Failed sync input switch value.Existing");
    DisplayErrorMsg("Input Sync Failed");
    exit(0);
  }

  if(turnONVentilator==1)
  {
    //start the ventilator

    turnONVentilator=0;
    ventilatorIsRunning=1;
    boxCursorMove = 0;    

  }

  if(ventilatorIsRunning==1)
  {
    // start reading pressure sensor
    getOuputPressure();

    // start reading flow sensor
    getOuputFlow();

    // start reading the volume
    getOuputVolume();

    // check the callibration
    if (callibration == false)
    {
      // do the four five iteration and adjust the value of speed ,step and acceleration motor
      DisplayCalibrationMsg();

      // get speed,step and on-off time
      rval = doCallibration();
      if (rval != 0)
      {
        Serial.println("Callibration Failed.Existing");
        DisplayErrorMsg("Callibration Failure");
        exit(0);
      }
      else
      {
          delay(2000);
          callibration = true;
      }
      callibrationDone=false;
    }
    else
    {
      if (callibrationDone == false)
      {
        Serial.print(("Step of Motor                     : "));
        Serial.println(motorStep);

        Serial.print(("Motor step delay-clock in uS      : "));
        Serial.println(motordelayClock);

        Serial.print(("Motor step delay-anticlock in uS  : "));
        Serial.println(motordelayAntiClock);

        Serial.print(("Motor speed                       : "));
        Serial.println(motorSpeed);

        Serial.print(("Inhale Time in ms                 : "));
        Serial.println(inHaleTime);

        Serial.print(("exhale Time in ms                 : "));
        Serial.println(exHaleTime);

        displayStatusDone=0;
        DisplayMainScreen();
        updateBoxValue(0, pressureInputValue);
        updateBoxValue(1, bmpInputValue);
        updateBoxValue(3, tidalVolumeInput);
        startVentilator();
        

        Serial.println(("Starting The Ventilator"));
        callibrationDone=true;
      }
    }
    rval = runVentilator();
    if (rval != 0)
    {
      Serial.println("Hardware Drive Failed.Existing");
      DisplayErrorMsg("Hardware Drive Failure");
      exit(0);
    }

  }

  if(turnOFFVentilator==1)
  {
    //start the ventilator

    turnOFFVentilator=0;
    ventilatorIsRunning=0;
    stopVentilator();
    callibration = false;    
    
  }


  // motor current and voltage

  // check for iot interval form packet and send packet

    //check for ventilator start
    //currentPowerSwitchValue=0 off


    //check for ventilator stop
    //currentPowerSwitchValue=1 on

    //check if ventilator runnning , send the latest value every 5 sec
    //ventilatorIsRunning

  /****************************
   *   process synced data
   *****************************/
  rval = updateDisplay();
  if (rval != 0)
  {
    Serial.println("Failed Update display with latest value.Existing");
    DisplayErrorMsg("Updating Display Failed");
    delay(1000);
    exit(0);
  }
}

 
 