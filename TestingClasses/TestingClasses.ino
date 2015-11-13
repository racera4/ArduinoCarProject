#include "PingSensor.h"
#include <Servo.h>
#include "Motor.h"

int pingPin = 11;
int servoPin = 9;
int sDelay = 100;

PingSensor sensor(pingPin, sDelay);
Motor ESC(servoPin);

void setup() {
  // put your setup code here, to run once:
  sensor.startSerial();
  //ESC.attach(servoPin);
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
  ESC.setSpeed(100);
}
void moveReverse()
{
  ESC.setSpeed(30);
}
void moveStop()
{
  ESC.setSpeed(92);
}

