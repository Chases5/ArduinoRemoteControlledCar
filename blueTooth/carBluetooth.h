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
	while (!Serial3.available()) {
		delay(1);
	}
	unsigned char buttonData = (unsigned char) Serial3.read();
	Serial3.print(sendData);
	
	while (!Serial3.available()) {
		delay(1);
	}
	char response = (char) Serial3.read();
	if (response == 'A') {
		return true;
	}
	return false;
}
#endif
