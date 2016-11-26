#ifndef CONTROLLER_BLUETOOTH
#define CONTROLLER_BLUETOOTH
#include "Arduino.h"
#include "bluetoothTransfer.h"

void initializeBluetooth() {
	Serial.begin(9600);
}

bool update(String* dir, int* buttons) {
	if (Serial.available()) {
		char value = (char) Serial.read();
		if (value == 'R') {
			unsigned char sendData = packageButtonData(buttons);
			Serial.print(sendData);
			while (!Serial.available()) {
				delay(1);
			}
			unsigned char directionByte = (unsigned char) Serial.read();
			Serial.print("A");
			*dir = byteToDirection(directionByte);
			return true;
		}
	}
	return false;
}
#endif
