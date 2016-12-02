//==========================================================
// Written by: Tyler Carlile and Chase Skelton
// Date: 11/8/2016
// Last Modification: 11/8/2016
//==========================================================
// Used to determine how far the ultrasonic sensor is from
// an object in centimeters.
//==========================================================

#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include "Arduino.h"

int trigPin, echoPin;

/*
 * Sets the trigger and echo pins and initializes the
 * pins.
 */
void initUltrasonic(const int& trig, const int& echo) {
	trigPin = trig;
	echoPin = echo;
	
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	digitalWrite(trigPin, LOW);
}

/*
 * Gets the distance, in centimeters, that the ultrasonic
 * sensor is from an object;
 */
double getDistance() {
	digitalWrite(trigPin, HIGH);
	delay(1);
	digitalWrite(trigPin, LOW);
    unsigned long duration = pulseIn(echoPin, HIGH, 5000);
    if (duration == 0) {
        return 0.0;
    }
	double distance = (((double) duration / 2.0) / 29.1); // cm
	return distance;
}
#endif