/*********************************
* Title: Motor.cpp
* Author: Benjamin Finley
* Summary: This was created in as part of my Senior project
* Motor.h utilizes peices of the Servo.h from the Arduino library
* It was made to control ESC's (Engine Speed Control) modules from R/C vehicles
* 
* Value to Operate DuraTrax BLAST ESC:
* ESC neutral range is: 1472 - 1530 -- 91-95 degrees
* 1531-1532 microseconds is a strange jittery forward motion, possible engine break. (BLAST ESC)
* 1470-1471 -- 84-90 degrees - residual positive voltage. Sending these values in degrees will cause the motor to turn in reverse
* 1533 microseconds -- 96 degrees - is the beginning range of forward motion. (BLAST ESC)
* 1469 microseconds -- 83 degrees - is the beginning range of reverse motion. (BLAST ESC)
* 
* Revisions:
* Version 1.00
* Date: 11-7-2015
* Created file. Defined constructor, destructor, no methods or variables created yet.
* Version 1.01
* Date: 11-8-2015
* 
* Version 1.50
* Date: 11-18-2015
* Adjust the case of some of the methods to match proper standards.
* Code complies as it should.
* Version 1.60
* Date: 11-22-2015
* Calibrated for BLAST ESC, details of operation are listed above in the summary
* 
* 
**********************************/

#include <Arduino.h>
#include "Motor.h"

using namespace std;

Motor::Motor(int Cpin)
{
	m_ESC.attach(Cpin);
}
void Motor::setSpeed(int speed)
{
	//convert user readable speed to ESC readable speed
	m_speed = speed;
	m_ESC.write(m_speed);
}
