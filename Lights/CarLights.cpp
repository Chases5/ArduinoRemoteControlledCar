/*
Written by: Tyler Carlile and Chase Skelton
Date: 10/20/2016
Last Modification: 10/26/2016
*/

#ifndef CAR_LIGHTS_CPP
#define CAR_LIGHTS_CPP
#include "CarLights.h"
#include "Arduino.h"

/*
Receives pin values for the photocell, head lights, tail lights,
and turn signals. These values are stored and each component is 
initialized. Initialization sets the pin mode and writes any
starting value to the pin; it also initializes variables.
*/
CarLights::CarLights(const int& photo, const int& hl, const int& hr,
		const int& tl, const int& tr, const int& sl, const int& sr) {
	this->photocell = photo;
	this->headL = hl;
	this->headR = hr;
	this->tailL = tl;
	this->tailR = tr;
	this->signalL = sl;
	this->signalR = sr;
	
	this->initPhotocell();
	this->initHeadLights();
	this->initTailLights();
	this->initSignals();
}

/*
Sets the photocell's pin mode.
*/
void CarLights::initPhotocell() const {
	pinMode(photocell, INPUT);
}

/*
Sets the head lights' pin mode and makes
sure they are off.
*/
void CarLights::initHeadLights() const {
	pinMode(headL, OUTPUT);
	pinMode(headR, OUTPUT);
	digitalWrite(headL, LOW);
	digitalWrite(headR, LOW);
}

/*
Sets the tail lights' pin mode and makes
sure they are off.
*/
void CarLights::initTailLights() const {
	pinMode(tailL, OUTPUT);
	pinMode(tailR, OUTPUT);
	digitalWrite(tailL, LOW);
	digitalWrite(tailR, LOW);
}

/*
Sets the pin mode for the signals, makes sure they are off,
and initializes data required for blinking the turn signals
without using delays as this will decrease the responsiveness
of the entire system.
*/
void CarLights::initSignals() {
	pinMode(signalL, OUTPUT);
	pinMode(signalR, OUTPUT);
	this->resetSignals();
}

/*
Used to turn off the turn signals and to reset all variables
used in determining a turn.
*/
void CarLights::resetSignals() {
	digitalWrite(signalL, LOW);
	digitalWrite(signalR, LOW);
	currentTurn[LEFT_LIGHT] = false; // not turning left
	currentTurn[RIGHT_LIGHT] = false; // not turning right
	currentTurn[LIGHT_VALUE] = false; // indicates the digital value of turn (off)
	currentTurnTime = -1; // not turning
}

/*
Receives the photocell value to determine if it is dark out.

If it is dark out, the head lights and tail lights are turned on.

If it is not dark, the head lights and tail lights are turned off.

If the brakes are on, the brake lights are turned on.

If the car is turning left, the left signal is toggled.

If the car is turning right, the right signal is toggled.
*/
void CarLights::update(const bool& brakesApplied, bool turnLeft, bool turnRight) {
	bool dark = analogRead(photocell) <= PHOTOCELL_CUTOFF;
	
	/*
	The car cannot be turning left and right at the same time.
	These two are mutually exclusive. Therefore, if they are both
	true, assume the car is not turning and set both to false.
	*/
	if (turnLeft && turnRight) {
		turnLeft = turnRight = false;
	}
	
	/*
	Determines the current state of the turn indicators.
	*/
	if (turnLeft && !currentTurn[LEFT_LIGHT]) { // starting a left turn
		startTurn(LEFT_LIGHT, signalL, RIGHT_LIGHT, signalR);
	} else if (turnRight && !currentTurn[RIGHT_LIGHT]) { // starting a right turn
		startTurn(RIGHT_LIGHT, signalR, LEFT_LIGHT, signalL);
	} else if (turnLeft && currentTurn[LEFT_LIGHT]) { // continuing left turn
		continueTurn(signalL, signalR);
	} else if (turnRight && currentTurn[RIGHT_LIGHT]) { // continuing right turn
		continueTurn(signalR, signalL);
	} else { // no turn
		resetSignals();
	}
	
	/*
	If dark, turn on head lights and tail lights.
	Otherwise, turn them off.
	*/
	if (dark) {
		digitalWrite(headL, HIGH);
		digitalWrite(headR, HIGH);
		if (!brakesApplied) {
			analogWrite(tailL, TAIL_VALUE);
			analogWrite(tailR, TAIL_VALUE);
		}
	} else {
		digitalWrite(headL, LOW);
		digitalWrite(headR, LOW);
		if (!brakesApplied) {
			analogWrite(tailL, LOW);
			analogWrite(tailR, LOW);
		}
	}
	
	/*
	If the brakes are being applied, turn on the brake lights.
	*/
	if (brakesApplied) {
		analogWrite(tailL, BRAKE_VALUE);
		analogWrite(tailR, BRAKE_VALUE);
	}
}

/*
Used to start a turn. This sets the appropriate variables and 
turns on the turn indicator for the turn.
*/
void CarLights::startTurn(CurrentTurnIndices toStart, int pinToStart, CurrentTurnIndices toStop, int pinToStop) {
	currentTurn[toStart] = true;
	currentTurn[toStop] = false;
	currentTurnTime = millis();
	currentTurn[LIGHT_VALUE] = true;
	digitalWrite(pinToStart, currentTurn[LIGHT_VALUE]);
	digitalWrite(pinToStop, LOW);
}

/*
Used to continue a turn. Determines when to flash the
turn indicator and sets the values of the appropriate turn
indicators.
*/
void CarLights::continueTurn(int activePin, int inactivePin) {
	unsigned long msec = millis();
	if ((msec - currentTurnTime) >= SIGNAL_TIME) {
		currentTurnTime = msec;
		currentTurn[LIGHT_VALUE] = !currentTurn[LIGHT_VALUE];
	}
	digitalWrite(activePin, currentTurn[LIGHT_VALUE]);
	digitalWrite(inactivePin, LOW);
}

#endif
