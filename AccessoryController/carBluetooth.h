#ifndef CAR_BLUETOOTH
#define CAR_BLUETOOTH
#include "Arduino.h"
#include "bluetoothTransfer.h"

void initializeBluetooth() {
	Serial3.begin(9600);
}

void sendData(String directionString, float x, float y) {
	unsigned char packet = directionToByte(directionString);
	//unsigned char xBytes[4], yBytes[4];
	//floatToBytes(x, xBytes);
	//floatToBytes(y, yBytes);
	Serial3.print(packet);
	/*for (int i = 0; i < 4; i++) {
		Serial3.print(xBytes[i]);
	}
	for (int i = 0; i < 4; i++) {
		Serial3.print(yBytes[i]);
	}
 */
}

bool readData(int* values) {
	if (Serial3.available()) {
		unsigned char packet = (unsigned char) Serial3.read();
		readPackageButtons(packet, values);
		return true;
	}
	
	return false;
}
#endif
