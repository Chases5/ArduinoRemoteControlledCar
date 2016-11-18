//==================================================================
// Written by Tyler Carlile and Chase Skelton
// Date: 11/8/2016
// Last Modification: 11/8/2016
//==================================================================
// Declares the magnetometer that will be used to get the direction
// in which the car is facing. Functions allow user to get the
// direction, heading, and the magnetometer reading.
//==================================================================
#ifndef COMPASS_H
#define COMPASS_H
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <math.h>
#include "Arduino.h"

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

const double GRAVITY = 9.80665;

/*
 * Initializes the system to use the magnetometer.
 */
void initCompass() {
	#ifndef WIRE_BEGIN
	#define WIRE_BEGIN
	Wire.begin();
	#endif
	mag.enableAutoRange(true);
	mag.begin();
}

/*
 * Initializes the Accelerometer.
 */
void initAccelerometer() {
	#ifndef WIRE_BEGIN
	#define WIRE_BEGIN
	Wire.begin();
	#endif
	accel.begin();
}

/*
 * Gets the x and y values of the acceleration in Gs.
 */
void getAcceleration(float* x, float* y) {
	sensors_event_t event;
	accel.getEvent(&event);
	*x = ((float) event.acceleration.x) / GRAVITY;
	*y = ((float) event.acceleration.y) / GRAVITY;	
}

/*
 * Reads the values from the magnetometer. The
 * values are saved into the pointers that are
 * passed in.
 */
void readMag(double* x, double* y, double* z) {
  sensors_event_t event;
  mag.getEvent(&event);
  *x = event.magnetic.x;
  *y = event.magnetic.y;
  *z = event.magnetic.z;
}

/*
 * Using a heading, the direction is determined
 * and returned.
 */
String determineDirection(double heading) {
  if (heading >= 337.5 || heading <= 22.5) {
    return "N";
  } else if (heading > 22.5 && heading < 67.5) {
    return "NW";
  } else if (heading >= 67.5 && heading <= 112.5) {
    return "W";
  } else if (heading > 112.5 && heading < 157.5) {
    return "SW";
  } else if (heading >= 157.5 && heading <= 202.5) {
    return "S";
  } else if (heading > 202.5 && heading < 247.5) {
    return "SE";
  } else if (heading >= 247.5 && heading <= 292.5) {
    return "E";
  } else {
    return "NE";
  }
}

/*
 * Determines the heading of the magnetometer using
 * x and y. The heading is returned.
 */
double determineHeading(double x, double y) {
  if (y > 0) {
    return 90.0 - (atan(x / y)) * 180.0 / M_PI;
  } else if (y < 0) {
    return 270.0 - (atan(x / y)) * 180.0 / M_PI;
  }
}

/*
 * This method provides a simple method to call that
 * will return a compass reading using the magnetometer.
 */
String getCompassReading() {
	double x, y, z;
	readMag(&x, &y, &z);
	return determineDirection(determineHeading(x, y));
}
#endif