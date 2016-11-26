/*
Written by: Tyler Carlile and Chase Skelton
Date: 10/20/2016
Last Modification: 10/26/2016
-------------------------------------------------------------
CarLights class is used to create an object that 
controls the lights of the car. The lights are, 
for the most part, controlled by a photocell. The
value from the photocell is used to determine how
dark it is, if it is dark enough, the head lights and
tail lights will be turned on. Additional input from
the car is required in order to turn on/off the brake lights
and to flash the turn indicators.
-------------------------------------------------------------
Hardware Setup:

Head Lights:
There are 2 head lights (white LEDs). These go on the front
of the car, connect the power of each to digital pins and
connect the other end to ground using 220-ohm resistors.
The digital pins connected for power, are the pins passed
into the constructor for the head lights.

Tail Lights:
There are also 2 tail lights (red LEDs). These go on the back
of the car, connect the power of each to digital pins THAT
SUPPORT PWM (I will explain later). The other end is to be
connected to ground using 220-ohm resistors. The digital pins
are the pins to be passed into the constructor for the tail
lights.

Brake Lights:
The brake lights are not 2 additional lights. They work off
of the same LEDs that the tail lights use. The tail lights
use a small analog value to dim the LEDs while the brake 
lights use a larger value to brighten the LEDs. This is why
these lights need to be connected to pins that support PWM.

Turn Signals:
The turn signals are 2 lights (yellow LEDs). These go on 
the back of the car and flash when the car is turning. 
Connect the power for the LEDs to digital pins and connect
the other side to ground using 220-ohm resistors. The digital
pins are passed into the constructor for the turn signals.

Photocell:
Connect one end of the photocell to 5v. At the other end,
connect the output to an analog in pin (this will be passed
to the constructor) and to ground using a 220-ohm resistor.
-------------------------------------------------------------
*/

#ifndef CAR_LIGHTS_H
#define CAR_LIGHTS_H

const int TAIL_VALUE = 50;
const int BRAKE_VALUE = 127;
const int PHOTOCELL_CUTOFF = 100;
const unsigned long SIGNAL_TIME = 500; // milliseconds

/*
Enum to hold indices for currentTurn array.
*/
enum CurrentTurnIndices {
	LEFT_LIGHT, RIGHT_LIGHT, LIGHT_VALUE
};

class CarLights {
public:

	/*
	Sets all of the pin values for the lights and photocell as well
	as initializing data used for blinking the turn indicators.
	*/
	CarLights(const int& photo, const int& hl, const int& hr,
		const int& tl, const int& tr, const int& sl, const int& sr);
	
	/*
	Updates the lights in the system. Uses passed in booleans to determine
	the value for the brake lights and the turn indicators.
	*/
	void update(const bool& brakesApplied, bool turnLeft, bool turnRight);
	
private:
	int photocell;
	int headL;
	int headR;
	int tailL;
	int tailR;
	int signalL;
	int signalR;
	bool currentTurn[3];
	unsigned long currentTurnTime;
	
	/*
	Initializes the head lights.
	*/
	void initHeadLights() const;
	
	/*
	Initializes the tail lights.
	*/
	void initTailLights() const;
	
	/*
	Initializes the photocell.
	*/
	void initPhotocell() const;
	
	/*
	Initializes the signals (turn indicators).
	*/
	void initSignals();
	
	/*
	Used when the car is starting a turn. Turns on the proper signal and 
	initializes the turn variables.
	*/
	void startTurn(CurrentTurnIndices toStart, int pinToStart, CurrentTurnIndices toStop, int pinToStop);
	
	/*
	Used when the car is still turning. Determines when to flash the 
	turn signal.
	*/
	void continueTurn(int activePin, int inactivePin);
	
	/*
	Resets all of the variables used for the turn indicators and
	turns them off.
	*/
	void resetSignals();
};

#endif
