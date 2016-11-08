#include <CarLights.h>
bool brake;
CarLights carLights(A0, 8, 7, 10, 9, 13, 12);
void setup() {
  Serial.begin(9600);
  brake = false;
}

void loop() {
  if (Serial.read() - 48 == 1) {
     brake = !brake; 
  }
  carLights.update(brake, true, false);
}
