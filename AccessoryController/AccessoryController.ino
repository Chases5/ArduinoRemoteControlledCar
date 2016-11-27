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
    Serial2.begin(9600);
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

  //Serial2.write(messageOut);
  */
 /*
  unsigned char i2cMessage;
  float x = 4.0;
  float y = 5.0;
  //getAcceleration(x,y);
  String data = "SE";
  //sendData(data,x,y);
  //delay(2000);
  data = "N";
  //sendData(data,x,y);  
  carUpdate(dataRead, "SE");
    for(int i = 0 ; i < 5; i++){
      Serial.print(dataRead[i]);
      Serial.print(",");
    }
    Serial.println("");
  //Serial.println("");
  */
  //carUpdate(dataRead, "SE");
  String compassReading = getCompassReading();
  carUpdate(compassReading);
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

void carUpdate(String dir){
  Serial2.print("R");
  unsigned long timeout = millis();
  while(!Serial2.available()){
    //Serial.print(Serial2.available());
    if(millis() - timeout >= 1000){
      return;
    }
    delay(1);
  }
  unsigned char button = Serial2.read();
  readPackButtons(button, dataRead);
  
  for(int i = 0 ; i < 5; i++){
      Serial.print(dataRead[i]);
      Serial.print(",");
    }
    Serial.println("");
    
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

void readPackButtons(unsigned char packet, bool* values) {
  values[HORN] = (packet & 0x10) == 0x10;
  values[GO] = (packet & 0x08) == 0x08;
  values[REVERSE] = (packet & 0x04) == 0x04;
  values[LEFT] = (packet & 0x02) == 0x02;
  values[RIGHT] = (packet & 0x01) == 0x01;
}

