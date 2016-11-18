#include <CarLights.h>
#include "Buzzer.h"
#include "Compass.h"
#include "Ultrasonic.h"
#include "bluetoothData.h"
#include <Wire.h>

bool brake = false;
CarLights carLights(A15, 39, 41, 6, 7, 43, 45);
carData test;
void setup() {
  inti
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
  //setHorn(true);
  setReverse(true);
  updateBuzzer();
  Serial.println("Compass");
  Serial.println(getCompassReading());
  Serial.println(getDistance());
  double accelX;
  double accelY;
  getAcceleration(&accelX,&accelY);
  Serial.print(accelX);
  Serial.print(" ");
  Serial.println(accelY);
  carData messageOut;
  messageOut.xAcceleration = accelX;
  messageOut.yAcceleration = accelY;
  String compassReading = getCompassReading();
  messageOut.cardinal = compassReading[0];
  if(compassReading.length() == 2){
    messageOut.interCardinal = compassReading[1];
  } else {
    messageOut.interCardinal = -1;
  }
  Serial3.write(messageOut);

  //tone(5,500);
  //delay(300);
  //noTone(5);
  //delay (300);
}
