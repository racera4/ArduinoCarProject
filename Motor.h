#ifndef MOTOR_H
#define MOTOR_H

#include "Servo.h"
#include "Arduino.h"

class Motor : public Servo
{
public:
	Motor(int Cpin) : Servo() {};
	virtual ~Motor() {};
	



private:
	

}