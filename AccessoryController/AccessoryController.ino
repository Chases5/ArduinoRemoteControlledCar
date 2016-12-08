//==========================================================
// Written by: Tyler Carlile and Chase Skelton
// Date: 11/8/2016
// Last Modification: 12/7/2016
//==========================================================
// Accessory Controller handles everything that is needed
// to run the car.
//==========================================================

#include <CarLights.h>
#include "Buzzer.h"
#include "Compass.h"
#include "Ultrasonic.h"
#include <Wire.h>
#include "carBluetooth.h"
#include "bluetoothTransfer.h";

bool brake = false;
double accelX;
double accelY;
CarLights carLights(A14, 39, 41, 6, 7, 43, 45);
bool dataRead []= {false,false,false,false,false};
bool lastMessageGo = false;
bool carLightData[] = {false,false,false};

/* 
 * begin the Wire, Serial and call the init functions
 * on the included libraries.
 */
 
void setup() {
  Wire.begin();
  initSerial();
  intiAccessories();
}

void initSerial(){
    Serial.begin(9600);
    Serial2.begin(9600);
}

void intiAccessories(){
    initBuzzer(5);
    initCompass();
    initUltrasonic(12,13);
    initAccelerometer();
    initializeBluetooth();
    initUltrasonic(12,13);
}

/*
 * Read the data from the compass send the compass data to the
 * controller and read the controller instructions and send them
 * to the motor. Then update the lights and horn based on input
 * from the controller.
 */
 
void loop() {
  String compassData = getCompassReading();
  carUpdate(compassData);
  carLights.update(carLightData[0],carLightData[1],carLightData[2]);
  if(buzzerHorn){
    tone(buzzerPin,500);
  }
  else{
    noTone(buzzerPin);
  }
}

/*
 * Request data from the controller and wait to receive it
 * read the data and write back the ack. Send the data to
 * the motor controller and update the lights and horn.
 */
void carUpdate(String dir){
  Serial2.print("R");
  unsigned long timeout = millis();
  while(!Serial2.available()){
    if(millis() - timeout >= 1000){
      return;
    }
    delay(1);
  }
  unsigned char button = Serial2.read();
  readPackButtons(button, dataRead);
      
  unsigned char d = dirToByte(dir);
  Serial2.write(d);
  timeout = millis();
  while(Serial2.read() != 'A'){
    //Serial.print(Serial2.available());
    if(millis() - timeout >= 1000){
      return;
    }
    delay(1);
  }

  double ultraDist = getDistance();
  if(ultraDist >= 8 && ultraDist < 60 && dataRead[GO]){
    button -= 8;  
  }
  Wire.beginTransmission(8);
  Wire.write(button);
  Wire.endTransmission();
  setHorn(dataRead[4]);
  
  if(!dataRead[GO] && !dataRead[REVERSE]){
    brake = true;
  }
  if(dataRead[LEFT] && !dataRead[RIGHT]){
    carLightData[0] = false;
    carLightData[1] = true;
    carLightData[2] = false;
  } else if(dataRead[RIGHT] && !dataRead[LEFT]){
    carLightData[0] = false;
    carLightData[1] = false;
    carLightData[2] = true;
  } else if (dataRead[GO] || dataRead[REVERSE]){
    carLightData[0] = false;
    carLightData[1] = false;
    carLightData[2] = false;
  } else{
    carLightData[0] = true;
    carLightData[1] = false;
    carLightData[2] = false;
  }
}

/*
 * Convert the String value that we get from
 * the compass function into a byte to send to the 
 * controller.
 */
unsigned char dirToByte(String dir) {
  unsigned char charByte = 0;
  for (int i = 0; i < dir.length(); i++) {
    if (dir[i] == 'N') {
      charByte |= 0x08;
    } else if (dir[i] == 'S') {
      charByte |= 0x04;
    } else if (dir[i] == 'E') {
      charByte |= 0x02;
    } else {
      charByte |= 0x01;
    }
  }
  return charByte;
}

/*
 * Convert the unsigned char packed that was received from the 
 * controller set the data in the passed boolean array at the
 * direction values.
 */
void readPackButtons(unsigned char packet, bool* values) {
  values[HORN] = (packet & 0x10) == 0x10;
  values[GO] = (packet & 0x08) == 0x08;
  values[REVERSE] = (packet & 0x04) == 0x04;
  values[LEFT] = (packet & 0x02) == 0x02;
  values[RIGHT] = (packet & 0x01) == 0x01;
}

