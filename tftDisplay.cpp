#include "Adafruit_ST77xx.h"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>


#define TFT_RST         -1 //No pin     // TFT RST pin is connected to NodeMCU pin D4 (GPIO2)
#define TFT_CS          15     // TFT CS  pin is connected to NodeMCU pin D8 (GPIO15)
#define TFT_DC          3     // TFT DC  pin is connected to NodeMCU pin Rx (GPIO3)
#define TFT_MOSI        13  // Data out is connected to NodeMCU pin D7 (GPIO13)
#define TFT_SCLK        14  // Clock out is connected to NodeMCU pin D5 (GPIO14)

// For ST7735-based displays, we will use this call
// Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

#define X   5
#define Y   25

void DisplayInit()
{
   // Use this initializer if using a 1.8" TFT screen:
  tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
  tft.setRotation(3);
  
}

int DisplayClear()
{
  tft.fillScreen(ST77XX_BLACK);
  return 0;
}

int DisplayWriteText(unsigned char x,unsigned char y, int width, char *txt, unsigned int colour)
{
  tft.setTextWrap(false);
  tft.setCursor(x, y);
  tft.setTextColor(colour);
  tft.setTextSize(width);
  tft.println(txt);
return 0;
}

void DisplayWelcomMsg(){
  DisplayClear();
  DisplayWriteText(20, 45, 3,"Welcome", ST77XX_WHITE);
  DisplayWriteText(40, 75, 1,"Powered by Accenture", ST77XX_GREEN);

}
void DisplayDummyUpdate()
{
  //remove it.Only for test
  tft.fillRect(X+1,Y+16,X+58,18, ST77XX_BLACK);
  tft.setCursor(X+6, Y+20);
  tft.setTextSize(0);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);

    //remove it.Only for test
    tft.fillRect(X+2,Y+61,X+57,18, ST77XX_BLACK);
  tft.setCursor(X+6, Y+65);
  tft.setTextSize(0);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);

    //remove it.Only for test
    tft.fillRect(X+tft.width()/2+1,Y+16,X+58,18, ST77XX_BLACK);
  tft.setCursor(X+tft.width()/2+10, Y+20);
  tft.setTextSize(0);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);

    //remove it.Only for test
    tft.fillRect(X+tft.width()/2+1,Y+61,X+58,18, ST77XX_BLACK);
  tft.setCursor(X+tft.width()/2+10, Y+65);
  tft.setTextSize(0);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);


}
void DisplayMainScreen()
{
  int colour = ST77XX_GREEN;
  DisplayClear();
  //lines draw on screen
  tft.drawLine(0, 20, tft.width()-1, 20, colour);
  tft.drawLine(tft.width()/2, 20, tft.width()/2, tft.height(), colour);

  //status bar
  DisplayWriteText(5,5, 1, "Status:", ST77XX_WHITE);

  //Input pressure
  DisplayWriteText(X,Y+2, 1, "Pressure I/P", ST77XX_WHITE);
  tft.drawRect(X,Y+15,X+60,20, colour);
  

  //output pressure
  DisplayWriteText(X,Y+45, 1, "Pressure O/P", ST77XX_WHITE);
  tft.drawRect(X,Y+60,X+60,20, colour);
  

  //input BPM 
  DisplayWriteText(X+tft.width()/2+15,Y+2, 1, "BPM", ST77XX_WHITE);
  tft.drawRect(X+tft.width()/2,Y+15,X+60,20, colour);
  
  //input Tidal volume 
  DisplayWriteText(X+tft.width()/2+5,Y+45, 1, "Tidal I/P", ST77XX_WHITE);
  tft.drawRect(X+tft.width()/2,Y+60,X+60,20, colour);
  

}
