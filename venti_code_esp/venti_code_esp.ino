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
int powerSwitchValue = 0;
int curentLeftButtonValue = 0;
int currentRightButtonValue = 0;
int currentPotValue = 0;

int pressureInputValue = 0;
int pressureOutputValue = 0;

int bmpInputValue = 0;

int tidalVolumeInput = 0;
int tidalVolumeOutput = 0;

bool callibrationDone = false;

int fetchInput()
{
  // Serial.println("reading LeftButtonValue:");
  int buttonValue = 0;

  buttonValue = getLeftButtonValue();
  if (buttonValue != curentLeftButtonValue)
  {

    curentLeftButtonValue = buttonValue;

    Serial.print(("LeftButtonValue:"));
    Serial.println(curentLeftButtonValue);

    if (curentLeftButtonValue == 1)
    {
      boxCursorMove = 1;

      if (currentBOXcounter == 0)
        currentBOXcounter = 3;
      else
        currentBOXcounter--;

      if (currentBOXcounter == 2)
        currentBOXcounter = 1;

      Serial.print(("currentBOXcounter:"));
      Serial.println(currentBOXcounter);
    }
  }

  buttonValue = getRightButtonValue();
  // Serial.println("reading rightButtonValue:");
  if (buttonValue != currentRightButtonValue)
  {

    currentRightButtonValue = buttonValue;

    Serial.print(("RightButtonValue:"));
    Serial.println(currentRightButtonValue);

    if (currentRightButtonValue == 1)
    {
      boxCursorMove = 1;
      if (currentBOXcounter == 3)
        currentBOXcounter = 0;
      else
        currentBOXcounter++;

      if (currentBOXcounter == 2)
        currentBOXcounter = 3;

      Serial.print(("currentBOXcounter:"));
      Serial.println(currentBOXcounter);
    }
  }
  // Serial.println("reading stopstartButtonValue:");
  powerSwitchValue ^= getStartStopButtonValue();

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
  static int blinkStatus = 0;
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
  if (boxCursorMove == 1 && powerSwitchValue == LOW)
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
    if (boxCursorMove == 1 && powerSwitchValue == HIGH)
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

  // Update IOT status

  return 0;
}

int getOuputPressure()
{
}

int getOuputFlow()
{
}

int getOuputVolume()
{
}

int updateMotorParameter()
{
}

int driveMechanism()
{

  return 0;
}

int doCallibration()
{
  // calculate the speed

  // calculate step agnle

  // calculate the ON time and OFF time: ON time is 75% of one cycle and OFF time is 25% of one cycle

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
  // delay(2000);

  // stepper motor Initialised

  // Input Initialised
  Serial.println("Input initialised");
  inputInit();

  // pinMode(16, INPUT_PULLUP);

  // pressure sensor Initialised

  // flow sensor Initialised

  // current sensor Initialised

  // IOT application Initialised

  // display main page
  DisplayMainScreen();

  Serial.println(F("Ventilator is initialised"));
}

void loop()
{

  // DisplayDummyUpdate();
  // delay(1000);

  // int buttonState = digitalRead(10);
  // // print out the state of the button:
  // Serial.println(buttonState);

  // // buttonState = digitalRead(16);
  // // // print out the state of the button:
  // // Serial.println(buttonState);

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

  if (powerSwitchValue == HIGH)
  {
    // start reading pressure sensor

    // start reading flow sensor

    // check the callibration
    if (callibrationDone == false)
    {
      // do the four five iteration and adjust the value of speed ,step and acceleration motor

      // get speed,step and on-off time
      rval = doCallibration();
      if (rval != 0)
      {
        Serial.println("Callibration Failed.Existing");
        DisplayErrorMsg("Callibration Failure");
        exit(0);
      }

      callibrationDone = true;
    }
    else
    {
      // run hardware driver
      rval = driveMechanism();
      if (rval != 0)
      {
        Serial.println("Hawrdare Drive Failed.Existing");
        DisplayErrorMsg("Hawrdare Drive Failure");
        exit(0);
      }
    }
     boxCursorMove = 0;
  }
  else
  {
   
    callibrationDone = false;
  }

  // motor current and voltage

  // check for iot interval form packet and send packet

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