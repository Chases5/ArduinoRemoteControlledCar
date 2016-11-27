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
  char readArray [2];
  readArray[1] = (char)Serial3.read();
  readArray[0] = (char)Serial3.read();
  
  readPackageButtons(readArray, carSignals);
  for(int i = 0; i < 5; i++){
    Serial.print(carSignals[i]);
    Serial.print(",");
  }
  Serial.println("");
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

