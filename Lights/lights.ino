const byte PHOTOCELL = A0;
const byte CUTOFF = 100;
const byte LEFT_HEAD_LIGHT = 8;
const byte RIGHT_HEAD_LIGHT = 7;
const byte TAIL_L = 11;
const byte TAIL_R = 10;
const byte TAIL_V = 50;
const byte BUTTON = 12;
const int BUTTON_V = 255;

void setup() {
  Serial.begin(9600);
  pinMode(PHOTOCELL, INPUT);
  pinMode(LEFT_HEAD_LIGHT, OUTPUT);
  pinMode(RIGHT_HEAD_LIGHT, OUTPUT);
  pinMode(TAIL_R, OUTPUT);
  pinMode(TAIL_L, OUTPUT);
  
  digitalWrite(LEFT_HEAD_LIGHT, LOW);
  digitalWrite(RIGHT_HEAD_LIGHT, LOW);
  
  analogWrite(TAIL_R, 0);
  analogWrite(TAIL_L, 0);
  
  pinMode(BUTTON, INPUT);
}

void loop() {
  int cellValue = analogRead(PHOTOCELL);
  Serial.println(cellValue);
  
  byte buttonValue = digitalRead(BUTTON);
  if (!buttonValue && cellValue > CUTOFF) {
     analogWrite(TAIL_L, 0);
     analogWrite(TAIL_R, 0);
  }
  
  if (cellValue <= CUTOFF) {
     digitalWrite(LEFT_HEAD_LIGHT, HIGH);
     digitalWrite(RIGHT_HEAD_LIGHT, HIGH); 
     analogWrite(TAIL_R, TAIL_V);
     analogWrite(TAIL_L, TAIL_V);
  } else {
    digitalWrite(LEFT_HEAD_LIGHT, LOW);
    digitalWrite(RIGHT_HEAD_LIGHT, LOW);
    analogWrite(TAIL_R, 0);
    analogWrite(TAIL_L, 0);
  }
  
  if (buttonValue) {
     analogWrite(TAIL_L, BUTTON_V);
     analogWrite(TAIL_R, BUTTON_V); 
  }
}
