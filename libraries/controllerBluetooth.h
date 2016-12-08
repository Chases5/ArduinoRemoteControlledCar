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
			Serial.write(sendData);
			unsigned long timeout = millis();
			while (!Serial.available()) {
				delay(1);
				if ((millis() - timeout) >= TIMEOUT) {
					return false;
				}
			}
			unsigned char directionByte = (unsigned char) Serial.read();
			*dir = byteToDirection(directionByte);
			return true;
		}
	}
	return false;
}
#endif
