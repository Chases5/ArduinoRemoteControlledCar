#ifndef BLUETOOTH_TRANSFER
#define BLUETOOTH_TRANSFER
#include "button.h"
#define PRECISION 100
#define MASK 0x01

unsigned char directionToByte(String direction) {
	unsigned char charByte = 0;
	for (int i = 0; i < direction.length(); i++) {
		if (direction[i] == 'N') {
			charByte |= 0x08;
		} else if (direction[i] == 'S') {
			charByte |= 0x04;
		} else if (direction[i] == 'E') {
			charByte |= 0x02;
		} else {
			charByte |= 0x01;
		}
	}
	return charByte;
}

String byteToDirection(unsigned char data) {
	String retval = "";
	if ((data & 0x08) == 0x08) {
		retval.concat("N");
	}
	if ((data & 0x04) == 0x04) {
		retval.concat("S");
	}
	if ((data & 0x02) == 0x02) {
		retval.concat("E");
	}
	if ((data & 0x01) == 0x01) {
		retval.concat("W");
	}
	return retval;
}

void floatToBytes(float val, unsigned char* bytes) {
	int transfer = (int) (val * PRECISION);
	for (int i = 3; i >= 0; i--) {
		*(bytes + i) = (unsigned char) (0 | transfer);
		transfer >>= 8;
	}
}

float bytesToFloat(unsigned char* bytes) {
	int retval = 0;
	for (int i = 0; i < 4; i++) {
		retval <<= 8;
		retval |= *(bytes + i);
	}
	return ((float) retval) / ((float) PRECISION);
}

unsigned char packageButtonData(int* buttons) {
	unsigned char retval = 0;

	retval |= (buttons[GO] & ~buttons[REVERSE]);
	retval <<= 1;
	retval |= (buttons[GO] | buttons[REVERSE]);
	retval <<= 1;

	retval |= (buttons[LEFT] & ~buttons[RIGHT]);
	retval <<= 1;
	retval |= (buttons[LEFT] | buttons[RIGHT]);
	retval <<= 1;

	retval |= buttons[HORN];
	return retval;
}

void readPackageButtons(unsigned char packet, int* values) {
	if (packet & MASK) {
		values[HORN] = 1;
	} else {
		values[HORN] = 0;
	}

	packet >>= 1;

	if (packet & MASK) {
		packet >>= 1;
		if (packet & MASK) {
			values[LEFT] = 1;
			values[RIGHT] = 0;
		} else {
			values[RIGHT] = 1;
			values[LEFT] = 0;
		}
		packet >>= 1;
	}	else {
		packet >>= 2;
		values[LEFT] = 0;
		values[RIGHT] = 0;
	}

	if (packet & MASK) {
		packet >>= 1;
		if (packet & MASK) {
			values[GO] = 1;
			values[REVERSE] = 0;
		}
		else {
			values[GO] = 0;
			values[REVERSE] = 1;
		}
		packet >>= 1;
	}
	else {
		packet >>= 2;
		values[GO] = 0;
		values[REVERSE] = 0;
	}
}
#endif
