#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 14, 15, 16, 17);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("wilson sucks");
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
