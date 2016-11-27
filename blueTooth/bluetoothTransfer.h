#ifndef BLUETOOTH_TRANSFER
#define BLUETOOTH_TRANSFER
#include "button.h"
#define PRECISION 100
#define MASK 0x01
#define TIMEOUT 1000

unsigned char directionToByte(String dir) {
	unsigned char charByte = 0;
	for (int i = 0; i < dir.length(); i++) {
		if (dir[i] == 'N') {
			charByte |= 0x08;
		} else if (dir[i] == 'S') {
			charByte |= 0x04;
		} else if (dir[i] == 'E') {
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

void packageButtonData(int* buttons, unsigned char* bytes) {
	unsigned char first = 0;
	if (buttons[HORN] == 1) {
		*(bytes + 1) = 1;
	} else {
		*(bytes + 1) = 0;
	}
	
	first += (8 * buttons[GO]);
	first += (4 * buttons[REVERSE]);
	first += (2 * buttons[LEFT]);
	first += (1 * buttons[RIGHT]);
	*(bytes + 0) = first;
}

void readPackageButtons(unsigned char* packet, bool* values) {
	if (*(packet + 1) == 1) {
		values[HORN] = true;
	} else {
		values[HORN] = false;
	}
	
	unsigned char first = *packet;
	if ((first & 0x01) == 0x01) {
		values[RIGHT] = true;
	} else {
		vaues[RIGHT] = false;
	}
	
	if ((first & 0x02) == 0x02) {
		values[LEFT] = true;
	} else {
		values[LEFT] = false;
	}
	
	if ((first & 0x04) == 0x04) {
		values[REVERSE] = true;
	} else {
		values[REVERSE] = false;
	}
	
	if ((first & 0x08) == 0x08) {
		values[GO] = true;
	} else {
		values[Go] = false;
	}
}
#endif
