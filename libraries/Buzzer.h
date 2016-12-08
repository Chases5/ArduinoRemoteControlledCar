//==========================================================
// Written by: Tyler Carlile and Chase Skelton
// Date: 11/8/2016
// Last Modification: 11/8/2016
//==========================================================
// Provided functions to set the buzzer to a pin and output
// sound based on the horn and reverse conditions. on
// reverse a pulsing buzzing noise will sound. When the horn
// is set to on it will play a constant sound until the 
// button is released.
//==========================================================

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

/*
 * Set the pin with the value of the passed in value as
 * the output pin for the buzzer. No error checking is 
 * done.
 */

void initBuzzer(int inputPin){
	buzzerPin = inputPin;
	pinMode(buzzerPin,OUTPUT);
}

/*
 * Set the horn value to the passed in boolean. This will
 * be used in the update buzzer function.
 */

void setHorn(boolean input){
	buzzerHorn = input;
}

/*
 * Set the reverse value to the passed in boolean. This will
 * be used in the update buzzer function.
 */

void setReverse(boolean input){
	buzzerReverse = input;
}

/*
 * Update buzzer should be called in the loop of the accessory
 * controller. It will check the value of setHorn and reverse
 * and play the appropirate buzzing sound.
 */

void updateBuzzer() {
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