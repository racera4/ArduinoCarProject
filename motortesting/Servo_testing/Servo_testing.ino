/*
 * Adafruit Adruino - Lesson 14. Sweep and Knob control
 */

#include <Servo.h>

int servoPin = 9;
int potPin = 0;

Servo servo;

int angle = 0;

void setup() 
{
  servo.attach(servoPin);
  Serial.begin(9600);
}

void loop() 
{

  int reading = analogRead(potPin);
  int angle = reading / 6;
  servo.write(angle);
  Serial.println(reading);
  Serial.println(angle);

}
 /* while(angle >= 169)
  {
    servo.write(0);
  }
  /*servo.write(172);
  for(angle = 0; angle <180; angle++)
  {
    servo.write(angle);
    delay(10);
  }
  
  for(angle = 180; angle >0; angle--)
  {
    servo.write(angle);
    delay(10);
  }*/

