//==========================================================
// Written by: Tyler Carlile and Chase Skelton
// Date: 11/8/2016
// Last Modification: 12/7/2016
//==========================================================
// The purpose of the motor control is to control all 4
// motors on the car using inputs from the accessory
// controller. Motor control is intended to be uploaded to 
// an arduino Uno with the motor shield attached as well as 
// the I^2C Connection which allows communication with the
// accessory controller which will send driving commands.
//==========================================================


#include <AFMotor.h>
#include "button.h"
#include <Wire.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

bool directions[4] = {0, 0, 0, 0};


/* 
 * Setup will initialize the I^2C connection.
 */
void setup() {
  Wire.begin(8);  // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
}

/*
 * receiveEvent is attached to the wire receive, when the
 * data is recieved we convert the byte and set the
 * motors based on the data recieved. our driving directions
 * are 8 values and a case for no movement.
 */

void receiveEvent(int howMany) {
  unsigned char packet = (unsigned char) Wire.read();
  readPackageButtons(packet, directions);
  if (!directions[GO] && !directions[REVERSE] && 
        !directions[LEFT] && !directions[RIGHT]) {
    noMovement();
  } else if (directions[GO]) {
    if (directions[LEFT]) {
      driveForwardLeft();
    } else if (directions[RIGHT]) {
      driveForwardRight();
    } else {
      driveForward();
    }
  } else if (directions[REVERSE]) {
    if (directions[LEFT]) {
      driveReverseLeft();
    } else if (directions[RIGHT]) {
      driveReverseRight();
    } else {
      driveReverse();
    }
  } else if (directions[LEFT]) {
    driveLeft();
  } else if (directions[RIGHT]) {
    driveRight();
  }
}

/* 
 * This function will read the direction input that comes in 
 * as a single byte sent over I^2C
 */
void readPackageButtons(unsigned char packet, bool* values) {
  values[GO] = (packet & 0x08) == 0x08;
  values[REVERSE] = (packet & 0x04) == 0x04;
  values[LEFT] = (packet & 0x02) == 0x02;
  values[RIGHT] = (packet & 0x01) == 0x01;
}

void driveForward(){
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  motor3.setSpeed(250);
  motor4.setSpeed(250);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void driveReverse(){
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  motor3.setSpeed(250);
  motor4.setSpeed(250);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void driveForwardRight(){
  motor1.setSpeed(250);
  motor1.run(FORWARD);
  motor2.setSpeed(250);
  motor2.run(FORWARD);
  motor3.setSpeed(50);
  motor3.run(FORWARD);
  motor4.setSpeed(50);
  motor4.run(FORWARD);
}

void driveRight(){
  motor1.setSpeed(250);
  motor1.run(FORWARD);
  motor2.setSpeed(250);
  motor2.run(FORWARD);
  motor3.setSpeed(250);
  motor3.run(BACKWARD);
  motor4.setSpeed(250);
  motor4.run(BACKWARD);
}

void driveReverseRight(){
  motor1.setSpeed(250);
  motor1.run(BACKWARD);
  motor2.setSpeed(250);
  motor2.run(BACKWARD);
  motor3.setSpeed(50);
  motor3.run(BACKWARD);
  motor4.setSpeed(50);
  motor4.run(BACKWARD);
}

void driveLeft(){
  motor1.setSpeed(250);
  motor1.run(BACKWARD);
  motor2.setSpeed(250);
  motor2.run(BACKWARD);
  motor3.setSpeed(250);
  motor3.run(FORWARD);
  motor4.setSpeed(250);
  motor4.run(FORWARD);
}

void driveForwardLeft(){
  motor1.setSpeed(50);
  motor1.run(FORWARD);
  motor2.setSpeed(50);
  motor2.run(FORWARD);
  motor3.setSpeed(250);
  motor3.run(FORWARD);
  motor4.setSpeed(250);
  motor4.run(FORWARD);
}

void driveReverseLeft(){
  motor1.setSpeed(50);
  motor1.run(BACKWARD);
  motor2.setSpeed(50);
  motor2.run(BACKWARD);
  motor3.setSpeed(250);
  motor3.run(BACKWARD);
  motor4.setSpeed(250);
  motor4.run(BACKWARD);
}

void noMovement() {
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

void loop() {
}
