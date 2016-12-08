//==========================================================
// Written by: Tyler Carlile and Chase Skelton
// Date: 11/8/2016
// Last Modification: 12/7/2016
//==========================================================
// This file is only used to test the the LCD. The actual
// LCD call is used in Controller driver.
//==========================================================

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 8, 7, 6, 5);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  pinMode(13, OUTPUT);
}


void loop() {
 
  analogWrite(13, 100);
  lcd.setCursor(0, 0);
  lcd.print("wilson sux");
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  String dir = "NE";
  String accel = "151.25";
  // print the number of seconds since reset:
  String printVal = dir + " || " + accel + " m/s";
  lcd.print(printVal);
}

// Example
//NE || Accl 15.4 m/s
