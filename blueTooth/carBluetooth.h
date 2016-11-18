#ifndef CAR_BLUETOOTH
#define CAR_BLUETOOTH
#include "Arduino.h"
#include "bluetoothTransfer.h"

void initializeBluetooth() {
	Serial.begin()
}

void sendButtonData(int* buttons) {
	unsigned char data = packageButtonData(buttons);
	Serial.print(data);
}

bool readData(String* direction, float* x, float* y) {
	if (Serial.available()) {
		unsigned char dir = (unsigned char) Serial.read();
		unsigned char xBytes[4], yBytes[4];
		xBytes[0] = (unsigned char) Serial.read();
		xBytes[1] = (unsigned char) Serial.read();
		xBytes[2] = (unsigned char) Serial.read();
		xBytes[3] = (unsigned char) Serial.read();
		
		yBytes[0] = (unsigned char) Serial.read();
		yBytes[1] = (unsigned char) Serial.read();
		yBytes[2] = (unsigned char) Serial.read();
		yBytes[3] = (unsigned char) Serial.read();
		
		*direction = byteToDirection(dir);
		*x = bytesToFloat(xBytes);
		*y = bytesToFloat(yBytes);
		return true;
	}
	
	return false;
}
#endif
