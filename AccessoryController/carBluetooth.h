#ifndef CAR_BLUETOOTH
#define CAR_BLUETOOTH
#include "Arduino.h"
#include "bluetoothTransfer.h"
void initializeBluetooth() {
	Serial2.begin(9600);
}

bool carUpdate(bool* carSignals, String dir) {
    Serial2.print('R');
    //while(!Serial2.available()){
	  //  delay(1);
    //}
    //if(Serial2.available()){
      Serial.println((char)Serial2.read());
    //}
    //unsigned char compassData = directionToByte(dir);
    //Serial2.write(compassData);
    return true;
}
#endif
