#include <LiquidCrystal.h>
#include "controllerBluetooth.h"
#include "button.h"

LiquidCrystal lcd(12, 11, 8, 7, 6, 5);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  initializeButtons(2, 3, 9, 10, 4);
}

void loop() {
  // put your main code here, to run repeatedly:
  int s[5] = {0, 0, 0, 0, 0};
  readButtons(s);
  analogWrite(13, 100);
  test(s);
}

void test(int* b) {
  if (Serial.available()) {
    char request = (char) Serial.read();
    if (request == 'R') {
      unsigned char d = packageButtonsData(b);
      Serial.write(d);
      unsigned long timeout = millis();
      while (!Serial.available()) {
        delay(1);
        if ((millis() - timeout) >= 1000) {
          return;
        }
      }
      unsigned char a = (unsigned char) Serial.read();
      String dir = byteToDir(a);
      lcd.setCursor(0, 0);
      lcd.print(dir);
      Serial.print("A");
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
