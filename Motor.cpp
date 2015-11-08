/*********************************
* Title: Motor.cpp
* Author: Benjamin Finley
* Summary: This was created in as part of my Senior project
* Motor.h utilizes peices of the Servo.h from the Arduino library
* It was made to control ESC's (Engine Speed Control) modules from R/C vehicles
* Revisions:
* Version 1.00
* Date: 11-7-2015
* Created file. Defined constructor, destructor, no methods or variables created yet.
**********************************/

/*#include "Servo.h"
#include "Arduino.h"*/

Motor::Motor(int Cpin)
{
	ESC.attach(Cpin);
}
virtual ~Motor() {};
SetSpeed(int speed)
{
	//convert user readable speed to ESC readable speed
	speed = speed * 18;
	ESC.write(speed);
}
SetSpeedF(int speed)
{	
	//stop reverse movement
	this.SetSpeedR(0);
	//Convert speed value to servo-ESC readable number.
	//Microseconds is prefered due to better precision.

}
SetSpeedR(int speed)
{
	//Stop forward movement
	this.SetSpeedF(0);
	//Convert speed value to servo-ESC readable number.
	//Microseconds is prefered due to better precision.

}
