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
			unsigned char sendBytes[2];
			//packageButtonData(buttons, sendBytes);
			Serial.print(sendBytes[0]);
			Serial.print(sendBytes[1]);
			unsigned long timeout = millis();
			while (!Serial.available()) {
				delay(1);
				if ((millis() - timeout) >= TIMEOUT) {
					return false;
				}
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
