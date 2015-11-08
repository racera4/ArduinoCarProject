#include "PingSensor.h"

int pingPin = 11;
int sDelay = 100;

PingSensor sensor(pingPin, sDelay);


void setup() {
  // put your setup code here, to run once:
  sensor.startSerial();

}

void loop() {
  // put your main code here, to run repeatedly:
  sensor.sensorRead();
  sensor.printDistance();

}
