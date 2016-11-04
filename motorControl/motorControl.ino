#include <AFMotor.h>
#include <Wire.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {
  // put your setup code here, to run once:
  motor1.setSpeed(250);
  motor2.setSpeed(250);
  motor3.setSpeed(250);
  motor4.setSpeed(250);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
}

//void receiveEvent(){
  /*
}
  while(1 <Wire.available()){
    char c = Wire.read();
    Serial.print(c);zΩxΩΩ
  }
  Serial.println();
  
}
*/
void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}

void loop() {
  // put your main code here, to run repeatedly:
  motor1.run(FORWARD);
  //motor1.setSpeed(100);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  //delay(500);
}
