#ifndef CONTROLLER_BLUETOOTH
#define CONTROLLER_BLUETOOTH
#include "Arduino.h"
#include "bluetoothTransfer.h"

void initializeBluetooth() {
	Serial.begin(9600);
}

void sendButtonData(int* buttons) {
	unsigned char data = packageButtonData(buttons);
	Serial.print(data);
}

bool readData(int* values) {
	if (Serial.available()) {
		unsigned char packet = (unsigned char) Serial.read();
		readPackageButtons(packet, values);
		return true;
	}
	
	return false;
}
#endif
