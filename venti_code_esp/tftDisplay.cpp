#include "Adafruit_ST77xx.h"
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7735.h>  // Hardware-specific library for ST7735
#include <SPI.h>
#include "tftDisplay.hpp"

#define TFT_RST -1   //No pin     // TFT RST pin is connected to NodeMCU pin D4 (GPIO2)
#define TFT_CS 15    // TFT CS  pin is connected to NodeMCU pin D8 (GPIO15)
#define TFT_DC 3     // TFT DC  pin is connected to NodeMCU pin Rx (GPIO3)
#define TFT_MOSI 13  // Data out is connected to NodeMCU pin D7 (GPIO13)
#define TFT_SCLK 14  // Clock out is connected to NodeMCU pin D5 (GPIO14)

// For ST7735-based displays, we will use this call
// Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define X 5
#define Y 25

#define BOX_1_X X
#define BOX_1_Y (Y + 15)
#define BOX_1_WIDTH (X + 60)
#define BOX_1_HEIGHT  20
#define BOX_1_COLOUR ST77XX_GREEN
#define BOX_1_TXT_X (X + 6)
#define BOX_1_TXT_Y (Y + 20)
#define BOX_1_TXT_WIDTH 0
#define BOX_1_TXT_COLOUR ST77XX_MAGENTA


#define BOX_2_X (X + 80)
#define BOX_2_Y (Y + 15)
#define BOX_2_WIDTH  (X + 60)
#define BOX_2_HEIGHT 20
#define BOX_2_COLOUR ST77XX_GREEN
#define BOX_2_TXT_X (X + 80 + 10)
#define BOX_2_TXT_Y (Y + 20)
#define BOX_2_TXT_WIDTH 0
#define BOX_2_TXT_COLOUR ST77XX_MAGENTA

#define BOX_3_X X
#define BOX_3_Y (Y + 60)
#define BOX_3_WIDTH (X + 60)
#define BOX_3_HEIGHT 20
#define BOX_3_COLOUR ST77XX_GREEN
#define BOX_3_TXT_X (X + 6)
#define BOX_3_TXT_Y (Y + 65)
#define BOX_3_TXT_WIDTH 0
#define BOX_3_TXT_COLOUR ST77XX_MAGENTA

#define BOX_4_X (X + 80)
#define BOX_4_Y (Y + 60)
#define BOX_4_WIDTH (X + 60)
#define BOX_4_HEIGHT 20
#define BOX_4_COLOUR ST77XX_GREEN
#define BOX_4_TXT_X (X + 80+ 10)
#define BOX_4_TXT_Y (Y + 65)
#define BOX_4_TXT_WIDTH 0
#define BOX_4_TXT_COLOUR ST77XX_MAGENTA

#define BXX tft.width()

struct boxtag BOXES[4] = { { BOX_1_X, BOX_1_Y, BOX_1_WIDTH, BOX_1_HEIGHT, BOX_1_COLOUR, BOX_1_TXT_X, BOX_1_TXT_Y, BOX_1_TXT_WIDTH, BOX_1_TXT_COLOUR },
                           {  BOX_2_X, BOX_2_Y, BOX_2_WIDTH, BOX_2_HEIGHT, BOX_2_COLOUR, BOX_2_TXT_X, BOX_2_TXT_Y, BOX_2_TXT_WIDTH, BOX_2_TXT_COLOUR },
                           {  BOX_3_X, BOX_3_Y, BOX_3_WIDTH, BOX_3_HEIGHT, BOX_3_COLOUR, BOX_3_TXT_X, BOX_3_TXT_Y, BOX_3_TXT_WIDTH, BOX_3_TXT_COLOUR},
                           {  BOX_4_X, BOX_4_Y, BOX_4_WIDTH, BOX_4_HEIGHT, BOX_4_COLOUR, BOX_4_TXT_X, BOX_4_TXT_Y, BOX_4_TXT_WIDTH, BOX_4_TXT_COLOUR} };

void DisplayInit() {
  // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);  // Init ST7735S chip, black tab
  tft.setRotation(3);
}

int DisplayClear() {
  tft.fillScreen(ST77XX_BLACK);
  return 0;
}

int DisplayWriteText(unsigned char x, unsigned char y, int width, char* txt, unsigned int colour) {
  tft.setTextWrap(false);
  tft.setCursor(x, y);
  tft.setTextColor(colour);
  tft.setTextSize(width);
  tft.println(txt);
  return 0;
}

int DisplayWriteValue(unsigned char x, unsigned char y, int width, float value, unsigned int colour) {
  tft.setTextWrap(false);
  tft.setCursor(x, y);
  tft.setTextColor(colour);
  tft.setTextSize(width);
  tft.print(value);
  return 0;
}

void DisplayWelcomMsg() {
  DisplayClear();
  DisplayWriteText(20, 45, 3, "Welcome", ST77XX_WHITE);
  DisplayWriteText(40, 75, 1, "Powered by Accenture", ST77XX_GREEN);
}
void DisplayDummyUpdate() {
  //remove it.Only for test
  tft.fillRect(X + 1, Y + 16, X + 58, 18, ST77XX_BLACK);
  tft.setCursor(X + 6, Y + 20);
  tft.setTextSize(0);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);

  //remove it.Only for test
  tft.fillRect(X + 2, Y + 61, X + 57, 18, ST77XX_BLACK);
  tft.setCursor(X + 6, Y + 65);
  tft.setTextSize(0);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);

  //remove it.Only for test
  tft.fillRect(X + tft.width() / 2 + 1, Y + 16, X + 58, 18, ST77XX_BLACK);
  tft.setCursor(X + tft.width() / 2 + 10, Y + 20);
  tft.setTextSize(0);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);

  //remove it.Only for test
  tft.fillRect(X + tft.width() / 2 + 1, Y + 61, X + 58, 18, ST77XX_BLACK);
  tft.setCursor(X + tft.width() / 2 + 10, Y + 65);
  tft.setTextSize(0);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
}
void DisplayMainScreen() {
  int colour = ST77XX_GREEN;
  DisplayClear();
  //lines draw on screen
  tft.drawLine(0, 20, tft.width() - 1, 20, colour);
  tft.drawLine(tft.width() / 2, 20, tft.width() / 2, tft.height(), colour);

  //status bar
  DisplayWriteText(5, 5, 1, "Status:", ST77XX_WHITE);

  //Input pressure
  DisplayWriteText(X, Y + 2, 1, "Pressure I/P", ST77XX_WHITE);
  tft.drawRect(X, Y + 15, X + 60, 20, colour);


  //output pressure
  DisplayWriteText(X, Y + 45, 1, "Pressure O/P", ST77XX_WHITE);
  tft.drawRect(X, Y + 60, X + 60, 20, colour);


  //input BPM
  DisplayWriteText(X + tft.width() / 2 + 15, Y + 2, 1, "BPM", ST77XX_WHITE);
  tft.drawRect(X + tft.width() / 2, Y + 15, X + 60, 20, colour);

  //input Tidal volume
  DisplayWriteText(X + tft.width() / 2 + 5, Y + 45, 1, "Tidal I/P", ST77XX_WHITE);
  tft.drawRect(X + tft.width() / 2, Y + 60, X + 60, 20, colour);
}

int getWidthDisplay()
{
    return tft.width();
}

int getHeightDisplay()
{
    return tft.height();
}

int getWidthFromMAcro()
{
  return 0;
}



void DisplayCalibrationMsg() {
  DisplayClear();
  int colour = ST77XX_GREEN;
  // tft.drawRect(starting X position,starting Y position , width, length, colour);
  // tft.drawRect(X+tft.width()/4+2.5,Y+35, 37, 40, colour);
  tft.drawRect(X + tft.width() / 4 - 20, Y + 15, tft.width() / 2 + 20, 45, colour);
  //  tft.fillRect(X+tft.width()/4-5,Y+35, tft.width()/2, 40, ST77XX_WHITE);
  DisplayWriteText(X + tft.width() / 4 - 10, Y + 33.5, 1.5, "Calibrating...", ST77XX_MAGENTA);
  //  tft.reset();
}

void DisplayErrorMsg(char* error_msg) {
  DisplayClear();
  int colour = ST77XX_GREEN;
  tft.drawRect(0, Y + 15, tft.width(), 45, colour);
  DisplayWriteText(X + tft.width() / 4 - 5, Y + 30, 1.2, "SYSTEM ERROR", ST77XX_MAGENTA);
  DisplayWriteText(X + tft.width() / 4 - 40, Y + 40, 0.1, error_msg, ST77XX_MAGENTA);
}

int deleteBox(int boxIndex) {
  //just delete it
  tft.fillRect(BOXES[boxIndex].x, BOXES[boxIndex].y, BOXES[boxIndex].width, BOXES[boxIndex].height, ST77XX_BLACK);
  return 0;
}

int updateBoxValue(int boxIndex, float boxValue) {
  //clear box
  deleteBox(boxIndex);
  //draw the box
  tft.drawRect(BOXES[boxIndex].x, BOXES[boxIndex].y, BOXES[boxIndex].width, BOXES[boxIndex].height, BOXES[boxIndex].colour);
  //write the value
  DisplayWriteValue(BOXES[boxIndex].txtX, BOXES[boxIndex].txtY, BOXES[boxIndex].txtWidth, boxValue, BOXES[boxIndex].txtColour);

  return 0;
}