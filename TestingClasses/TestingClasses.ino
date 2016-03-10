/*********************************
* Title: TestClasses.ino
* Author: Benjamin Finley
* Summary: This was created in for my Senior project
* It utilizes Servo.h from the Arduino library to control both the ESC and the Steering Servo
* It can control ESC (Engine Speed Control) modules from R/C vehicles
* 
* Values to Operate DuraTrax BLAST ESC:
* ESC neutral range is: 1460 - 1520 -- 91-95 degrees
* 1531-1532 microseconds is a strange jittery forward motion, possible engine break. (BLAST ESC)
* 1470-1471 -- 84-90 degrees - residual positive voltage. Sending these values in degrees will cause the motor to turn in reverse
* 1533 microseconds -- 96 degrees - is the beginning range of forward motion. (BLAST ESC)
* 1455 microseconds -- 83 degrees - is the beginning range of reverse motion. (BLAST ESC)
* -- 45 Degrees is maximum reverse speed
* -- 130 Degress is maximum forward speed
* 
* Values to Properly steer the Chevy Lumina Assembly.
* Right range:
* MAX right = 110
* MIN right = 95
* Left range:
* MAX left = 72
* MIN left = 87
* CENTER = 92
* 
*PIN CONNECTIONS
*PIN 0: UNUSED
*PIN 1: UNUSED
*PIN 2: USED -- FRONT SENSOR
*PIN 3; USED -- PWM, ESC CONTROL
*PIN 4: USED -- REAR SENSOR
*PIN 5: USED -- PWM, SERVO
*PIN 6: UNUSED
*PIN 7: USED -- LEFT SENSOR
*PIN 8: USED -- RIGHT SENSOR
*PIN 9: USED -- PUSHBUTTON
*PIN 10: UNUSED
*PIN 11: UNUSED
*PIN 12: UNUSED
*PIN 13: UNUSED
* 
*/
#define DGB
#ifndef DGB

Serial.print("message");

#endif

#include "PingSensor.h"
#include <Servo.h>

#define REVERSE_SLOW 1400
#define REVERSE_SLOWER 1420
#define REVERSE_SLOWEST 1430

int frontPingPin = 2;       //Pin for front PING sensor -- Green Wire
int rearPingPin = 4;        //Pin for rear PING sensor -- Blue Wire
int leftPingPin = 7;        //Pin for left PING sensor -- Orange Wire
int rightPingPin = 8;       //Pin for right PING sensor -- Yellow Wire

int motorPin = 3;           //PWM Pin to control the ESC
int steerPin = 5;           //PWM Pin to control steering servo
int sDelay = 25;            //Amount of delay between pulses of ping
int startPin = 9;           //Input pin for pushbutton

int buttonPressed = 0;
boolean waitHere = true;

int MAX_RIGHT = 110;        //Maximum right turn in degrees
int MIN_RIGHT = 95;         //Slight right turn in degrees
int MAX_LEFT = 72;          //Maximum left turn in degrees
int MIN_LEFT = 87;          //Slight left turn in degrees
int CENTER = 92;            //Center point

int minDist = 3;            //The Minimum distance allowed (inches)


PingSensor frontSensor(frontPingPin, sDelay);       //Initialize front sensor
PingSensor rearSensor(rearPingPin, sDelay);         //Initialize rear sensor
PingSensor leftSensor(leftPingPin, sDelay);         //Initialize left sensor
PingSensor rightSensor(rightPingPin, sDelay);       //Initialize right sensor
Servo Motor;        //Initialize motor control
Servo Steer;        //Initialize steering control

int initFrontDist = 0;
int initRearDist = 0;
int initLeftDist = 0;
int initRightDist = 0;

void setup()
{
    pinMode(startPin, INPUT);     //Declare input pin for pushbutton
    Motor.attach(motorPin);       //attach motor to control pin
    Steer.attach(steerPin);       //attach steering servo to control pin
    Steer.write(90);              //Center steering servo
    moveStop();                   //Stop motor to prevent accidental takeoff
    Serial.begin(115200);
    while(waitHere)
    {
      buttonPressed = digitalRead(startPin);
      if(buttonPressed == LOW)
      {
        waitHere = false;
        Serial.println("Button Pressed!");
        startPark();
      }
    }
    
}

void loop() 
{
/*    
 *     frontSensor.sensorRead();                //Read front sensor
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
    }

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
    }*/
}

void startPark()
{
  boolean parking = true;
  getInitDistance();
  while(parking)
  {
    frontSensor.sensorRead();                //Read front sensor
    int fDist = frontSensor.getDistance();   //Get the last read distance
    rearSensor.sensorRead();                 //Read rear sensor
    int rDist = rearSensor.getDistance();    //Get the last read distance
    leftSensor.sensorRead();                 //Read left sensor
    int lDist = leftSensor.getDistance();    //Get the last read distance
    rightSensor.sensorRead();                //Read right sensor
    int rtDist = rightSensor.getDistance();  //Get the last read distance

    //Move backwards ~4 inches from original position then stop
    if(rDist-(initRearDist-4) > 0)
    {
      Steer.write(CENTER);
      moveReverse();
    }
    else
    {
      moveStop();
      //Turn wheels full right
     Steer.write(MAX_RIGHT);
    }
    
    
    //Move backwards ~2 inches again
  }
  parking = false;
}

void getInitDistance()
{
  int sensorReads = 0;
    for(int i=0; i>11; i++)
    {
      frontSensor.sensorRead();                     //Read front sensor
      sensorReads += frontSensor.getDistance();
    }
    initFrontDist = sensorReads/10; 
    
    sensorReads = 0;
    for(int i=0; i>11; i++)
    {
      rearSensor.sensorRead();                      //Read rear sensor
      sensorReads+= rearSensor.getDistance();
    }
    initRearDist =  sensorReads/10;               //Get the last read distance

    sensorReads = 0;
    for(int i=0; i>11; i++)
    {
      leftSensor.sensorRead();                      //Read left sensor
      sensorReads+= leftSensor.getDistance();
    }
    initLeftDist = sensorReads/10;               //Get the last read distance
    sensorReads = 0;
    for(int i=0; i>11; i++)
    {
      rightSensor.sensorRead();                      //Read rught sensor
      sensorReads+= rightSensor.getDistance();
    }
    initRightDist = sensorReads/10;    //Get the last read distance
    sensorReads = 0;
}


void moveForward()
{
    Motor.write(100);
}

void moveReverse()
{
    Motor.writeMicroseconds(REVERSE_SLOW);
}

void moveStop()
{
    Motor.write(92);
}

void deBug()
{
    Serial.println("This is a Debug message");
}

