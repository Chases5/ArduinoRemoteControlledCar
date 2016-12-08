//==========================================================
// Written by: Tyler Carlile and Chase Skelton
// Date: 11/8/2016
// Last Modification: 12/7/2016
//==========================================================
// The button functions are used the initialize and read 
// The button pins. Pins must be chosen by the user and
// will not be checked for errors.
//==========================================================

# ifndef BUTTON
# define BUTTON
int rightPin = 0;
int leftPin = 0;
int forwardPin = 0;
int reversePin = 0;
int hornPin = 0;

enum{GO,REVERSE,LEFT,RIGHT,HORN};

/*
 * Initializes the pins of the passed in values. This does not
 * do any error checking. 
 */

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

/*
 * Reads the buttons and sets them in place in the array
 * at the position of the defined enum.
 * ex. [GO,REVERSE, LEFT, RIGHT, HORN].
 */

void readButtons(int* retVal){
  retVal[GO] = digitalRead(forwardPin);
  retVal[REVERSE] = digitalRead(reversePin);
  retVal[LEFT] = digitalRead(leftPin);
  retVal[RIGHT] = digitalRead(rightPin);
  retVal[HORN] = digitalRead(hornPin);
}
#endif