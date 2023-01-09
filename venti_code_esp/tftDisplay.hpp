


struct boxtag
{
    int x;
    int y;
    int width;
    int height;
    int colour;
    int txtX;
    int txtY;
    int txtWidth;
    int txtColour;

};




void DisplayInit();
void DisplayWelcomMsg();
void DisplayMainScreen();
void DisplayDummyUpdate();
void DisplayCalibrationMsg();
void DisplayErrorMsg(char*);
void DisplayStatus(char *power);
int deleteBox(int boxIndex);
int updateBoxValue(int boxIndex,float boxValue);
void DisplayWifiStatus(char *);
int getWidthDisplay();
int getHeightDisplay();
int getWidthFromMAcro();
