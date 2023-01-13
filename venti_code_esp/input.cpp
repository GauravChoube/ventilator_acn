#include <Arduino.h>
#include <Esp.h>

#define LEFT_BUTTON 16
#define RIGHT_BUTTON 0
#define START_STOP_BUTTON 10
#define POT_BUTTON A0
#define INHHALE_PIN 2

#define LEFT_BUTTON_ACTIVE_STATE 1
#define RIGHT_BUTTON_ACTIVE_STATE 0
#define START_STOP_BUTTON_ACTIVE_STATE 0

int inputInit() {

  pinMode(LEFT_BUTTON, INPUT_PULLDOWN_16);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(START_STOP_BUTTON, INPUT_PULLUP);
  pinMode(INHHALE_PIN, INPUT);

  return 0;
}

int getLeftButtonValue() {
  return digitalRead(LEFT_BUTTON) == LEFT_BUTTON_ACTIVE_STATE;
}

int getRightButtonValue() {
  return digitalRead(RIGHT_BUTTON) == RIGHT_BUTTON_ACTIVE_STATE;
}

int getStartStopButtonValue() {
  return digitalRead(START_STOP_BUTTON) == START_STOP_BUTTON_ACTIVE_STATE;
}

int getPotValue() {
  return analogRead(POT_BUTTON);
}

bool getInhaleValue() {
  return digitalRead(INHHALE_PIN);
}