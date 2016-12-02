#include <LiquidCrystal.h>
#include "controllerBluetooth.h"
#include "button.h"
String currDir;

// number of messages sent to and from devices
unsigned long termToMast, mastToTerm, mastToSlave, slaveToMast;

LiquidCrystal lcd(12, 11, 8, 7, 6, 5);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial3.begin(9600);
  initializeButtons(2, 3, 9, 10, 4);
  currDir = "";
  termToMast = 0;
  mastToTerm = 0;
  mastToSlave = 0;
  slaveToMast = 0;
  displayInstructions();
}

void displayInstructions() {
  Serial.println("Enter 0 to display packet information");
  Serial.println("Enter 1 to display sensor information");
}

void displayPacketInfo() {
  Serial.println("Packets sent:");
  Serial.print("Terminal to Master: ");
  Serial.println(termToMast);
  Serial.print("Master to Terminal: ");
  Serial.println(mastToTerm);
  Serial.print("Master to Slave: ");
  Serial.println(mastToSlave);
  Serial.print("Slave to Master: ");
  Serial.println(slaveToMast);
}

void displaySensorInfo() {
  Serial.println("Sensor information:");
  Serial.print("Compass reading: ");
  Serial.println(currDir);
}

void loop() {
  if (Serial.available()) {
    char value = (char) Serial.read();
    if (value == '0') {
      displayPacketInfo();
    } else if (value == '1') {
      displaySensorInfo();
    } else {
      displayInstructions();
    }
  }
  // put your main code here, to run repeatedly:
  int buttons[5] = {0, 0, 0, 0, 0};
  readButtons(buttons);
  analogWrite(13, 100);
  test(buttons);
}

void test(int* buttonData) {
  if (Serial3.available()) {
    char request = (char) Serial3.read();
    if (request == 'R') {
      unsigned char d = packageButtonsData(buttonData);
      Serial3.write(d);
      unsigned long timeout = millis();
      while (!Serial3.available()) {
        delay(1);
        if ((millis() - timeout) >= 1000) {
          return;
        }
      }
      unsigned char directionData = (unsigned char) Serial3.read();
      Serial3.print("A");
      String dir = byteToDir(directionData);
      if (dir != currDir) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(dir);
        currDir = dir;
      }
    }
  }
}
unsigned char packageButtonsData(int* buttons) {
  unsigned char retval = 0;
  if (buttons[HORN]) {
    retval += 16;
  }
  
  if (buttons[GO]) {
    retval += 8;
  }
  if (buttons[REVERSE]) {
    retval += 4;
  }
  if (buttons[LEFT]) {
    retval += 2;
  }
  if (buttons[RIGHT]) {
    retval += 1;
  }
  return retval;
}


String byteToDir(unsigned char data) {
  String retval = "";
  if ((data & 0x08) == 0x08) {
    retval.concat("N");
  }
  if ((data & 0x04) == 0x04) {
    retval.concat("S");
  }
  if ((data & 0x02) == 0x02) {
    retval.concat("E");
  }
  if ((data & 0x01) == 0x01) {
    retval.concat("W");
  }
  return retval;
}
