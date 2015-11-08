/*********************************
* Title: Motor.h
* Author: Benjamin Finley
* Summary: This was created in as part of my Senior project
* Motor.h utilizes peices of the Servo.h from the Arduino library
* It was made to control ESC's (Engine Speed Control) modules from R/C vehicles
* Revisions:
* Version 1.00
* Created file and constructor, destructor, no methods or variables created yet.
* Version 1.01
* Added SetSpeed, and GetSpeed Methods and private variable speed.
**********************************/


#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
//#include <Servo.h>


class Motor : public Servo
{
public:
	Motor(int Cpin) : Servo() {};
	virtual ~Motor() {};
	SetSpeed (int speed) {};
	GetSpeed() const {return speed;}

private:
	SetSpeedF(int speed) {};
	SetSpeedR(int speed) {};
	int speed;
	Servo ESC;

};
#endif
