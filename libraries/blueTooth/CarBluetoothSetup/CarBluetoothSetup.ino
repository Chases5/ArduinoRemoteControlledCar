
void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  Serial3.begin(38400);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    Serial3.print((char) Serial.read());
  }
  if (Serial3.available()) {
    Serial.print((char) Serial3.read());
  }
}
