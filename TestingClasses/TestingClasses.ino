#include "PingSensor.h"
#include <Servo.h>

int pingPin = 11;
int servoPin = 9;
int sDelay = 100;

PingSensor sensor(pingPin, sDelay);
Servo ESC;

void setup() {
  // put your setup code here, to run once:
  sensor.startSerial();
  ESC.attach(servoPin);
  moveStop();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor.sensorRead();
  sensor.printDistance();
  if (sensor.getDistance() > 5)
  {
    moveForward();
    Serial.println("I made it here!");
  }
  else if (sensor.getDistance() < 5)
  {
    moveReverse();
  }
  else
  {
    moveStop();
  }

}
void moveForward()
{
  ESC.write(100);
}
void moveReverse()
{
  ESC.write(30);
}
void moveStop()
{
  ESC.write(92);
}

