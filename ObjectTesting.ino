/*
 * Testing Motor.h files!!
 * and testing sensor stuff!
 */

//#include "Motor.h"
#include <NewPing.h>

int PingPin = 12;
NewPing sonar(PingPin, PingPin);

int motorPin = 9;
//Motor m1(motorPin);

void setup()
{
	Serial.begin(115200);
}

void loop() 
{
	delay(50);

	unsigned int uS = sonar.ping();

	Serial.print(uS/ US_ROUNDTRIP_IN);

	Serial.print("cm");
	/*m1.SetSpeed(6);
	delay(100);
	m1.SetSpeed(10);
	delay(100);
	m1.SetSpeed(0);
	delay(100);*/
}
