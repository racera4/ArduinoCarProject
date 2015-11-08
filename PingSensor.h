/* Ping))) Sensor
This Code was based off of the Example code that is located in the Public domain. 

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

   This example code is in the public domain.

 */
#ifndef PINGSENSOR_H
#define PINGSENSOR_H

using namespace std;

class PingSensor
{
public:
  PingSensor(int pingPin, int sDelay);
  //virtual ~PingSensor();

  
  void startSerial();
  void sensorRead();
  void printDistance();
  double microsecondsToInches(double microseconds);
  double microsecondsToCentimeters(double microseconds);
  
  void setPingPin(int pingPin) {m_pingPin = pingPin;}
  void setDelay(int sDelay) {m_delay = sDelay;}

  void getDistance(double duration);
  int getPingPin() const {return m_pingPin;}
  int getDelay() const {return m_delay;}

private:
  int m_delay;
  int m_pingPin;

};

#endif
