/*********************************
* Title: TestClasses.ino
* Author: Benjamin Finley
* Summary: This was created in for my Senior project
* It utilizes Servo.h from the Arduino library to control both the ESC and the Steering Servo
* It can control ESC (Engine Speed Control) modules from R/C vehicles
* 
* Values to Operate DuraTrax BLAST ESC:
* ESC neutral range is: 1472 - 1530 -- 91-95 degrees
* 1531-1532 microseconds is a strange jittery forward motion, possible engine break. (BLAST ESC)
* 1470-1471 -- 84-90 degrees - residual positive voltage. Sending these values in degrees will cause the motor to turn in reverse
* 1533 microseconds -- 96 degrees - is the beginning range of forward motion. (BLAST ESC)
* 1469 microseconds -- 83 degrees - is the beginning range of reverse motion. (BLAST ESC)
* 
* Values to Properly steer the Chevy Lumina Assembly.
* Right range:
* MAX right = 111
* MIN right = 95
* Left range:
* MAX left = 75
* MIN left = 87
* CENTER = 92
* 
* 
* 
 */
#define DGB
#ifndef DGB

Serial.print("message");

#endif

#include "PingSensor.h"
#include <Servo.h>

int frontPingPin = 2;       //Pin for front PING sensor -- Green Wire
int rearPingPin = 4;        //Pin for rear PING sensor -- Blue Wire
int leftPingPin = 7;        //Pin for left PING sensor -- Orange Wire
int rightPingPin = 8;       //Pin for right PING sensor -- Yellow Wire

int motorPin = 3;           //PWM Pin to control the ESC
int steerPin = 5;           //PWM Pin to control steering servo
int sDelay = 25;            //Amount of delay between pulses of ping

int MAX_RIGHT = 111;        //Maximum right turn in degrees
int MIN_RIGHT = 95;         //Slight right turn in degrees
int MAX_LEFT = 75;          //Maximum left turn in degrees
int MIN_LEFT = 87;          //Slight left turn in degrees
int CENTER = 92;            //Center point

int minDist = 3;            //The Minimum distance allowed (inches)


PingSensor frontSensor(frontPingPin, sDelay);       //Initialize front sensor
PingSensor rearSensor(rearPingPin, sDelay);         //Initialize rear sensor
PingSensor leftSensor(leftPingPin, sDelay);         //Initialize left sensor
PingSensor rightSensor(rightPingPin, sDelay);       //Initialize right sensor
Servo Motor;        //Initialize motor control
Servo Steer;        //Initialize steering control

void setup()
{
    Motor.attach(motorPin);       //attach motor to control pin
    Steer.attach(steerPin);       //attach steering servo to control pin
    Steer.write(90);              //Center steering servo
    moveStop();                   //Stop motor to prevent accidental takeoff
}

void loop() 
{
    frontSensor.sensorRead();                //Read front sensor
    int fDist = frontSensor.getDistance();   //Get the last read distance
    rearSensor.sensorRead();                 //Read rear sensor
    int rDist = rearSensor.getDistance();    //Get the last read distance
    leftSensor.sensorRead();                 //Read left sensor
    int lDist = leftSensor.getDistance();    //Get the last read distance
    rightSensor.sensorRead();                //Read right sensor
    int rtDist = rightSensor.getDistance();  //Get the last read distance
    
    //Steering Control
    if (rtDist-lDist < 0 ) // This creates more of a dynamic control for autonomous driving. (lDist < 5 && rtDist < 5)
    {
      Steer.write(MAX_LEFT);
    }
    else if (rtDist-lDist > 0)
    {
      Steer.write(MAX_RIGHT);
    }
    else
    {
      Steer.write(CENTER);
    }
    /*else if(rtDist < 5)
    {
      Steer.write(30);   
    }
    else if (lDist < 5)
    {
      Steer.write(150);
    }
    else
    {
      Steer.write(90);
    }*/

    //Motor Control
    if(fDist >= 10)
    {
      moveForward();
    }
    else if (fDist <= 10 && fDist >= minDist)
    {
      if(rDist > minDist)
      {
        moveReverse();
      }
      else
      {
        moveStop();
      }
    }
    else
    {
      moveStop();
    }
}

void moveForward()
{
    Motor.write(100);
}

void moveReverse()
{
    Motor.write(82);
}

void moveStop()
{
    Motor.write(92);
}

void deBug()
{
    Serial.println("This is a Debug message");
}

