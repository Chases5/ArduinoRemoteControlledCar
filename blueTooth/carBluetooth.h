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
		//unsigned char buttonData = (unsigned char) Serial3.read();
	//Serial.println(buttonData);
	char lowChar = (char)Serial3.read();
	char highChar = (char)Serial3.read();
	int dataInput;
	if(highChar < 0){
		dataInput = ((int)lowChar) - 48;
	}
	else{
		dataInput = ((int)highChar) - 48;
		dataInput *= 10;
		dataInput += ((int)lowChar) - 48;
	}
	readPackageButtons(dataInput, carSignals);
	
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
