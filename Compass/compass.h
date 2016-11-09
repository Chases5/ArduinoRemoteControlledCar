
#ifndef COMPASS_H
#define COMPASS_H
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <math.h>
#inclue "Arduino.h"

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void initCompass() {
	#ifndef WIRE_BEGIN
	#define WIRE_BEGIN
	Wire.begin();
	#endif
	mag.enableAutoRange(true);
	mag.begin();
}

void readMag(double* x, double* y, double* z) {
  sensors_event_t event;
  mag.getEvent(&event);
  *x = event.magnetic.x;
  *y = event.magnetic.y;
  *z = event.magnetic.z;
}

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

double determineHeading(double x, double y) {
  if (y > 0) {
    return 90.0 - (atan(x / y)) * 180.0 / M_PI;
  } else if (y < 0) {
    return 270.0 - (atan(x / y)) * 180.0 / M_PI;
  }
}

String getCompassReading() {
	double x, y, z;
	readMag(&x, &y, &z);
	return determineDirection(determineHeading(x, y));
}
#endif