//#ifndef CARBUTTONS_H
//#define CARBUTTONS_H
# include "Arduino.h"

const int rightPin = 4;
const int leftPin = 5;
const int forwardPin = 6;
const int reversePin = 7;
enum{FORWARD,REVERSE,LEFT,RIGHT};

void readButtons(int* retVal);

void initializeButtons();

//#endif