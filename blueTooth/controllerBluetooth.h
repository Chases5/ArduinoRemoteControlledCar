#ifndef CONTROLLER_BLUETOOTH
#define CONTROLLER_BLUETOOTH
#include "Arduino.h"
#include "bluetoothTransfer.h"

void initializeBluetooth() {
	Serial.begin(9600);
}

void sendData(int* buttons) {
	unsigned char data = packageButtonData(buttons);
	Serial.print(data);
}

bool readData(String* direction, float* x, float* y) {
	if (Serial.available()) {
		unsigned char dir = (unsigned char) Serial.read();
		unsigned char xBytes[4], yBytes[4];
		for (int i = 0; i < 4; i++) {
			xBytes[i]= (unsigned char) Serial.read();
		}
		for (int i = 0; i < 4; i++) {
			yBytes[i] = (unsigned char) Serial.read();
		}
		
		*direction = byteToDirection(dir);
		*x = bytesToFloat(xBytes);
		*y = bytesToFloat(yBytes);
		
		return true;
	}
	
	return false;
}
#endif
