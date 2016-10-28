//#ifdef CARBUTTONS_CPP
//#define CARBUTTONS_CPP
#include "carButtons.h"

void setup() {
  initializeButtons();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
     //int[] buttons = readButtons();
     int buttons[4];
     readButtons(buttons);
  for(int i = 0; i <= RIGHT; i++){
    Serial.println(buttons[i]);
  }
  delay(2000);
}


//#endif