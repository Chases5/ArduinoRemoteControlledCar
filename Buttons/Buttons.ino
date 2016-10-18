//Button Pins
const int rightPin = 4;
const int leftPin = 5;
const int forwardPin = 6;
const int reversePin = 7;
enum{FORWARD,REVERSE,LEFT,RIGHT};

void setup() {
  initializeButtons();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
     //int[] buttons = readButtons();
     int buttons[4];
     readButtons(buttons);
  for(int i = 0; i <= RIGHT; i++){
    Serial.println(buttons[i]);
  }
  delay(2000);
}

void initializeButtons(){
  pinMode(rightPin, INPUT);
  pinMode(leftPin, INPUT);
  pinMode(forwardPin, INPUT);
  pinMode(reversePin, INPUT);
}

void readButtons(int* retVal){
  //int retVal [4];
  if(digitalRead(forwardPin) == HIGH){
  retVal[FORWARD] =  1;
  }
  else{
    retVal[FORWARD] =  0;
  }
  if(digitalRead(reversePin) == HIGH){
  retVal[REVERSE] =  1;
  }
  else{
    retVal[REVERSE] =  0;
  }
  if(digitalRead(leftPin) == HIGH){
  retVal[LEFT] =  1;
  }
  else{
    retVal[LEFT] =  0;
  }
  if(digitalRead(rightPin) == HIGH){
  retVal[RIGHT] =  1;
  }
  else{
    retVal[RIGHT] =  0;
  }
}

