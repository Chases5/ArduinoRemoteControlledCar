const int rightPin = 4;
const int leftPin = 5;
const int forwardPin = 6;
const int reversePin = 7;
enum{FORWARD,REVERSE,LEFT,RIGHT};

void initializeButtons();
void readButtons(int* retVal);