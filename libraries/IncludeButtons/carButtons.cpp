//#ifdef CARBUTTONS_CPP
//#define CARBUTTONS_CPP
#include "carButtons.h"

void initializeButtons(){
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(forwardPin, INPUT);
  pinMode(reversePin, INPUT);
}

void readButtons(int* retVal){
  //int retVal [4];
  if(digitalRead(forwardPin) == HIGH){
  retVal[FORWARD] =  1;
  }
  else{
    retVal[FORWARD] =  0;
  }
  if(digitalRead(reversePin) == HIGH){
  retVal[REVERSE] =  1;
  }
  else{
    retVal[REVERSE] =  0;
  }
  if(digitalRead(leftPin) == HIGH){
  retVal[LEFT] =  1;
  }
  else{
    retVal[LEFT] =  0;
  }
  if(digitalRead(rightPin) == HIGH){
  retVal[RIGHT] =  1;
  }
  else{
    retVal[RIGHT] =  0;
  }
}

//#endif