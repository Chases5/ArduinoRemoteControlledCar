//------------------------------------------------------------------
// By: Tyler Carlile and Chase Skelton
// Date: 11/28/2016
// Last Modification: 12/8/2016
//------------------------------------------------------------------
// This is the driver for the Car's controller. This file includes
// methods that are used to convert data that is to be sent to the
// car into manageable bytes as well as converting bytes that are
// from the car into data. This file also provides code so that the
// controller can communicate with a terminal device in order to get
// the compass reading from the car and number of messages sent to
// and from each device in the system.
//------------------------------------------------------------------

#include <LiquidCrystal.h>
#include "button.h"

// Saves the compass direction
String currDir;
// number of messages sent to and from devices
unsigned long termToMast, mastToTerm, mastToSlave, slaveToMast;

LiquidCrystal lcd(12, 11, 8, 7, 6, 5);

/*
 * Initializes all pins, data, and starts the serial communications
 * to communicate with the car and with the terminal. This method also
 * displays instructions to the terminal on how to get requested
 * data.
 */
void setup() {
  lcd.begin(16, 2);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial3.begin(9600);
  initializeButtons(2, 3, 9, 10, 4);
  currDir = "";
  termToMast = 0;
  mastToTerm = 0;
  mastToSlave = 0;
  slaveToMast = 0;
  displayInstructions();
}

/*
 * Displays the instructions to the terminal on how to
 * get sensor data and packet data. The number of messages
 * sent is updated accordingly.
 */
void displayInstructions() {
  Serial.println("Enter 0 to display packet information");
  Serial.println("Enter 1 to display sensor information");
  Serial.println("");
  mastToTerm += 3;
}

/*
 * Displays the packet information to the terminal. The 
 * packet information is then updated accordingly.
 */
void displayPacketInfo() {
  Serial.println("Packets sent:");
  Serial.print("Terminal to Master: ");
  Serial.println(termToMast);
  Serial.print("Master to Terminal: ");
  Serial.println(mastToTerm);
  Serial.print("Master to Slave: ");
  Serial.println(mastToSlave);
  Serial.print("Slave to Master: ");
  Serial.println(slaveToMast);
  Serial.println("");
  mastToTerm += 10;
}

/*
 * Displays the sensor information to the terminal.
 * The packet information is then updated accordingly.
 */
void displaySensorInfo() {
  Serial.println("Sensor information:");
  Serial.print("Compass reading: ");
  Serial.println(currDir);
  Serial.println("");
  mastToTerm += 4;
}

/*
 * Runs the main loop for the arduino. 
 * This loop checks to see if there is any input from the
 * terminal and responds to it accordingly. Otherwise, the button data
 * is read from the buttons on the controller, and sent to the car.
 */
void loop() {
  /*
   * Check for and respond to terminal input.
   */
  if (Serial.available()) {
    char value = (char) Serial.read();
    termToMast++;
    if (value == '0') {
      displayPacketInfo();
    } else if (value == '1') {
      displaySensorInfo();
    } else {
      displayInstructions();
    }
  }
  int buttons[5] = {0, 0, 0, 0, 0};
  readButtons(buttons);
  analogWrite(13, 50);
  // sync with the car
  updateInfo(buttons);
}

/*
 * Checks to see if the car has requested the latest information. If so,
 * the button data is sent over. The car responds with sensor information
 * and the controller replies with an 'A' as the ack. After this, each 
 * device processes the data they got from the other.
 */
void updateInfo(int* buttonData) {
  /*
   * Checks to see if the bluetooth has information
   */
  if (Serial3.available()) {
    char request = (char) Serial3.read();
    /*
     * If a request has been made, send and recieve data
     */
    if (request == 'R') {
      unsigned char d = packageButtonsData(buttonData);
      // send requested data
      Serial3.write(d);
      unsigned long timeout = millis();
      /*
       * Waits for a reply but timesout after a second
       */
      while (!Serial3.available()) {
        delay(1);
        if ((millis() - timeout) >= 1000) {
          return;
        }
      }
      // read required data
      unsigned char directionData = (unsigned char) Serial3.read();
      // send acknowledgement
      Serial3.print("A");
      // sending the acknowledgement means message was completed successfully
      // master and slave both communicate one message at a time so we will
      // increment both counts together (2 packets each).
      slaveToMast += 2;
      mastToSlave += 2;
      // convert the data to meaningful information
      String dir = byteToDir(directionData);
      /*
       * Updates the LCD if the information has changed.
       */
      if (dir != currDir) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(dir);
        currDir = dir;
      }
    }
  }
}

/*
 * Uses the provided button data and packages them into
 * a byte of data (as an unsigned char) that can easily
 * be sent over bluetooth. If the horn button is pressed,
 * the 5th bit it set, if the forward button is pressed,
 * the 4th bit is set, if the reverse button is pressed,
 * the 3rd bit is set, if the left turn button is pressed,
 * the 2nd bit is set, and if the right turn button is
 * pressed, the 1st bit is set.
 * 
 * This function does nothing to 'fix' input. For example,
 * if the forward and reverse buttons are pressed, this
 * method will still package the data with both bits set. 
 * The actual executed command will be determined by the 
 * car once the data is acquired.
 */
unsigned char packageButtonsData(int* buttons) {
  unsigned char retval = 0;
  if (buttons[HORN]) {
    retval += 16;
  }
  if (buttons[GO]) {
    retval += 8;
  }
  if (buttons[REVERSE]) {
    retval += 4;
  }
  if (buttons[LEFT]) {
    retval += 2;
  }
  if (buttons[RIGHT]) {
    retval += 1;
  }
  return retval;
}

/*
 * Converts a byte of data (as an unsigned char)
 * to a compass direction. Only the first 4 bits
 * are used. The first bit represents west, the
 * second is east, the third is south, and the fourth
 * is north. Multiple bits can be set, for example, NW
 * will have the north and west bit set.
 */
String byteToDir(unsigned char data) {
  String retval = "";
  if ((data & 0x08) == 0x08) {
    retval.concat("N");
  }
  if ((data & 0x04) == 0x04) {
    retval.concat("S");
  }
  if ((data & 0x02) == 0x02) {
    retval.concat("E");
  }
  if ((data & 0x01) == 0x01) {
    retval.concat("W");
  }
  return retval;
}
