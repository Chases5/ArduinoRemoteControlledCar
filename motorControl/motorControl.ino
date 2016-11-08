#include <AFMotor.h>
#include <Wire.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() 
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
}
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
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

void driveRight(){
  motor1.setSpeed(250);
  motor1.run(FORWARD);
  motor2.setSpeed(250);
  motor2.run(FORWARD);
  motor3.setSpeed(0);
  motor4.setSpeed(0);
}

void driveLeft(){
  motor1.setSpeed(0);
  motor2.setSpeed(0);
  motor3.setSpeed(250);
  motor3.run(FORWARD);
  motor4.setSpeed(250);
  motor4.run(FORWARD);
}

void loop() {
  driveForward();
  delay(5000);
  driveRight();
  delay(5000);
  driveLeft();
  delay(5000);
  driveReverse();
  delay(5000);
}
