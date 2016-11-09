#ifndef BUZZER_H
#define BUZZER_H
#include <Arduino.h>

int buzzerPin = 0;
boolean buzzerReverse = false;
boolean buzzerHorn = false;
int currentBuzzerTime = 0;
boolean buzzerCycle = true;
const int BUZZER_TIME = 3000;
boolean buzzerOn = true;

void initBuzzer(int inputPin){
	buzzerPin = inputPin;
	pinMode(buzzerPin,OUTPUT);
}

void setHorn(boolean input){
	buzzerHorn = input;
}

void setReverse(boolean input){
	buzzerReverse = input;
}

void updateBuzzer() {
  // put your main code here, to run repeatedly:
	int msec = millis();
	if(buzzerReverse && !buzzerHorn){
		if(((msec - currentBuzzerTime) >= BUZZER_TIME)){
      if(buzzerOn){
        
        tone(buzzerPin,500);
      }
			else{
        noTone(buzzerPin);
      }
      currentBuzzerTime = msec;
      buzzerOn = !buzzerOn;
		}
	}
	if(buzzerHorn){
		tone(buzzerPin,500);
	}
	
}

#endif