
#include <Wire.h>
void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  digitalWrite(7, HIGH);
  delay(10);
  digitalWrite(7, LOW);

  int duration = pulseIn(8, HIGH);
  int distance = (duration / 2) / 29.1;
  Wire.beginTransmission(8);
  Wire.write(distance);
  Wire.endTransmission();
  Serial.println(distance);
  delay(500);
}
