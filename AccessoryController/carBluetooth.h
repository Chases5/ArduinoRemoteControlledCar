#ifndef CAR_BLUETOOTH
#define CAR_BLUETOOTH
#include "Arduino.h"
#include "bluetoothTransfer.h"
void initializeBluetooth() {
	Serial2.begin(9600);
}

bool carUpdate(bool* carSignals, String dir) {
	  Serial.print(Serial2.read());
    return true;
}
#endif
