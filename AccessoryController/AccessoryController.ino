#include <CarLights.h>
#include "Buzzer.h"
#include "Compass.h"
#include "Ultrasonic.h"

bool brake;
CarLights carLights(A15, 39, 41, 6, 7, 43, 45);
void setup() {
  Serial.begin(9600);
  initBuzzer(5);
  initCompass();
  brake = false;
  initUltrasonic(12,13);
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
  Serial.println(accelX + " " accelY);
  //tone(5,500);
  //delay(300);
  //noTone(5);
  //delay (300);
}
