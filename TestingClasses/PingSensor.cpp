/* Title: Ping))) Sensor
 *  
   This sketch reads a PING))) ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse
   to return.  The length of the returning pulse is proportional to
   the distance of the object from the sensor.

   The circuit:
    * +V connection of the PING))) attached to +5V
    * GND connection of the PING))) attached to ground
    * SIG connection of the PING))) attached to digital pin 7

   http://www.arduino.cc/en/Tutorial/Ping

   created 3 Nov 2008
   by David A. Mellis
   modified 30 Aug 2011
   by Tom Igoe

   Summary:
   This Code was adapted from the Example code that is located in the Public domain.
   This file breaks down the original example into sections to allow for execution from other classes.

   Revisions:
   Version 1.50
   This version changes when the distance is converted to inches, and how often
   and where.

 */
#include <Arduino.h>
#include "PingSensor.h"

using namespace std;

// establish variables for duration of the ping,
// and the distance result in inches and centimeters:
double duration, inches, cm;

PingSensor::PingSensor(int pingPin, int sDelay)
{
  setPingPin(pingPin);
  setDelay(sDelay);
}

void PingSensor::startSerial() {
  // initialize serial communication:
  Serial.begin(115200);
}

void PingSensor::sensorRead() {

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(getPingPin(), OUTPUT);
  digitalWrite(getPingPin(), LOW);
  delayMicroseconds(2);
  digitalWrite(getPingPin(), HIGH);
  delayMicroseconds(5);
  digitalWrite(getPingPin(), LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(getPingPin(), INPUT);
  duration = pulseIn(getPingPin(), HIGH);

  // convert the time into a distance
  getDistance(duration);

  delay(getDelay());
}
void PingSensor::printDistance()
{
  getDistance();
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
}
void PingSensor::getDistance(double duration)
{
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
}
double PingSensor::getDistance()
{
  return inches;
}
double PingSensor::microsecondsToInches(double microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

double PingSensor::microsecondsToCentimeters(double microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
