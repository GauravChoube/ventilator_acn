#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3

// Set up a new SoftwareSerial object
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

const int stepPin = 5;
const int dirPin = 4;

char c = 0;
char step[4];
char delaymil[5];
char dir = 0;
char cnt = 0;
char state = 0;
char index = 0;
char stepcnt = 0;
bool dataisready = 0;

int delayinmili = 0;
int stepvalue;

void setup() {
  // Define pin modes for TX and RX
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);


  // Sets the two pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

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
        memset(delaymil, 0, 5);
        break;

      case ';':
        cnt++;
        index = 0;
        break;
      case '#':
        cnt = 10;
        dataisready = true;
        break;

      default:
        {
          if (cnt == 1) {
              state=c-48;
          } else if (cnt == 2){ 
                dir=c-48;
          } else if (cnt == 3) {
            step[index++] = c;
          } else if (cnt == 4) {
            delaymil[index++] = c;
          }
        }
    }
  }

  if (dataisready == true) {
    delayinmili = atoi(delaymil);
    stepvalue = atoi(step);
    digitalWrite(stepPin, dir);

    dataisready=false;
    Serial.print("State: ");
    Serial.println(state,DEC);

    Serial.print("delayinmili: ");
    Serial.println(delayinmili);

    Serial.print("stepvalue: ");
    Serial.println(stepvalue);

    Serial.print("dir: ");
    Serial.println(dir,DEC);
    Serial.println("========");


  }

  if (state == 1) {
    if (stepcnt++ < stepvalue) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(delayinmili);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(delayinmili);
    }
    else
      stepcnt=200;
  }
}