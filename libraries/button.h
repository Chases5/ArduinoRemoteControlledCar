# ifndef BUTTON
# define BUTTON
int rightPin = 0;
int leftPin = 0;
int forwardPin = 0;
int reversePin = 0;
int hornPin = 0;

enum{FORWARD,REVERSE,LEFT,RIGHT,HORN};

void initializeButtons(int right, int left, int forward, int reverse, int horn){
  pinMode(right, INPUT);
  rightPin = right;
  pinMode(left, INPUT);
  leftPin = left;
  pinMode(forward, INPUT);
  forwardPin = forward;
  pinMode(reverse, INPUT);
  reversePin = reverse;
  pinMode(horn, INPUT);
  hornPin = horn;
}

void readButtons(int* retVal){
  retVal[FOWARD] = digitalRead(forwardPin);
  retVal[REVERSE] = digitalRead(reversePin);
  retVal[LEFT] = digitalRead(leftPin);
  retVal[RIGHT] = digitalRead(rightPin);
  retVal[HORN] = digitalRead(hornPin);
}
#endif