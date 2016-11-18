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
CarLights carLights(A15, 39, 41, 6, 7, 43, 45);

void setup() {
  //Wire.begin();
  initSerial();
  intiAccessories();
}

void initSerial(){
    Serial.begin(9600);
    Serial3.begin(9600);
}

void intiAccessories(){
    initBuzzer(5);
    initCompass();
    initUltrasonic(12,13);
    initAccelerometer();

}

void loop() {
  if (Serial.read() - 48 == 1) {
     brake = !brake; 
  }
  carLights.update(brake, false, true);
  setReverse(true);
  updateBuzzer();
  getAcceleration(&accelX,&accelY);
  String compassReading = getCompassReading();

  //Serial3.write(messageOut);
  unsigned char i2cMessage;
  float x = 5.0;
  float y = 4.0;
  String data = "NW";
  sendData(data,x,y);
  
  
  
  /*
  tone(5,500);
  delay(300);
  noTone(5);
  delay (300);
  setHorn(true);
  Serial.println("Compass");
  Serial.println(getCompassReading());
  Serial.println(getDistance());
  Serial.print(accelX);
  Serial.print(" ");
  Serial.println(accelY);
  */
}
