#ifndef CAR_BLUETOOTH
#define CAR_BLUETOOTH
#include "Arduino.h"
#include "bluetoothTransfer.h"
void initializeBluetooth() {
	Serial3.begin(9600);
}

bool update(bool* carSignals, String dir) {
	unsigned char sendData = directionToByte(dir);
  Serial3.print('R');
	unsigned long timeout = millis();
  Serial.print("past one");
	while (!Serial3.available()) {
    Serial.print(Serial3.available());
		delay(1);
		if ((millis() - timeout) >= TIMEOUT) {
			return false;
		}
	}
  Serial.print("past two");
	unsigned char buttonData = (unsigned char) Serial3.read();
	Serial3.print(sendData);
  timeout = millis();
  Serial.print("past three");
  while(!Serial3.available()){
    delay(1);
    if((millis() - timeout) >= TIMEOUT){
      return false;
    }
  }
  Serial.print("past four");
	//readPackageButtons(buttonData, carSignals);
  Serial.println("past five");
	return true;
}
#endif
