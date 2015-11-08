/*
 * Testing Motor.h files!!
 */

#include "Motor.h"

int motorPin = 9;
Motor m1(motorPin);


void loop() 
{
  m1.SetSpeed(6);
  delay(100);
  m1.SetSpeed(10);
  delay(100);
  m1.SetSpeed(0);
  delay(100);
}
