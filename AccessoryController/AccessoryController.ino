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
bool dataRead []= {false,false,false,false,false};

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
    initializeBluetooth();
}

void loop() {
  /*
  if (Serial.read() - 48 == 1) {
     brake = !brake; 
  }
  carLights.update(brake, false, true);
  setReverse(true);
  updateBuzzer();
  getAcceleration(&accelX,&accelY);
  String compassReading = getCompassReading();

  //Serial3.write(messageOut);
  */
  unsigned char i2cMessage;
  float x = 4.0;
  float y = 5.0;
  //getAcceleration(x,y);
  String data = "SE";
  //sendData(data,x,y);
  //delay(2000);
  data = "N";
  //sendData(data,x,y);  
  update(dataRead, "SE");
  for(int i = 0 ; i < 5; i++){
    Serial.print(dataRead[i]);
    Serial.print(",");
  }
  Serial.println("");
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

void processButtonCommands(){
    bool toMotor [] = {false,false,false,false};
    if(dataRead[0] == true){
      setHorn(true);
    }
    else{
      setHorn(false);
    }
    for(int i = 0; i < 5; i ++){
      toMotor[i] = dataRead[i + 1];
    }
    sendButtonCommands(toMotor);
}

void sendButtonCommands(bool* motorData){
  
}

