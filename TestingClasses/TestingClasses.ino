
#define DGB
#ifndef DGB

Serial.print("message");

#endif


#include "PingSensor.h"
#include <Servo.h>
#include "Motor.h"

int pingPin = 11;
int sPin = 3;
int sDelay = 100;

PingSensor sensor(pingPin, sDelay);
//Motor ESC1(sPin);
Servo M1;

void setup()
{
    // put your setup code here, to run once:
    sensor.startSerial();
    M1.attach(sPin);
    //moveStop();
}

void loop() 
{
    // put your main code here, to run repeatedly:
    
    sensor.sensorRead();
    sensor.printDistance();
    if(sensor.getDistance() > 6)
    {
      moveForward();
    }
    else
    {
      moveReverse();
    }
    /*if (sensor.getDistance() > 5)
    {
      moveForward();
      deBug();
    }
    else if(sensor.getDistance() < 5)
    {
      moveReverse();
    }
    else
    {
      moveStop();
    }*/

}
void moveForward()
{
    M1.write(100);
    //ESC1.setSpeed(100);
}
void moveReverse()
{
    M1.write(82);
    //ESC1.setSpeed(82);
}
void moveStop()
{
    M1.write(92);
    //ESC1.setSpeed(92);
}

void deBug()
{
    Serial.println("This is a Debug message");
}

