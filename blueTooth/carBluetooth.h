#ifndef CAR_BLUETOOTH
#define CAR_BLUETOOTH
#include "Arduino.h"
#include "bluetoothTransfer.h"
void initializeBluetooth() {
	Serial3.begin(9600);
}

bool update(bool* carSignals, String dir) {
	unsigned char sendData = directionToByte(dir);
	Serial3.print("R");
	unsigned long timeout = millis();
	while (!Serial3.available()) {
		delay(1);
		if ((millis() - timeout) >= TIMEOUT) {
			return false;
		}
	}
	unsigned char buttonData = (unsigned char) Serial3.read();
	Serial3.print(sendData);
	timeout = millis();
	while (!Serial3.available()) {
		delay(1);
		if ((millis() - timeout) >= TIMEOUT) {
			return false;
		}
	}
	char response = (char) Serial3.read();
	if (response == 'A') {
		return true;
	}
	return false;
}
#endif
