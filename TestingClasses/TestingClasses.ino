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
************************
*As of 4/19/2016
*This Code is what was final for 
*the senior project presentation.
*Further development should be done
*to extend the project into further
*use cases and to also give better
*accuracy for the car.
*/
#define DGB
#ifndef DGB

.print("message");

#endif

#include "PingSensor.h"
#include <Servo.h>

#define FORWARD_SLOW 1536
#define REVERSE_SLOW 1430
#define REVERSE_SLOWER 1440
#define REVERSE_SLOWEST 1450

int frontPingPin = 2;       //Pin for front PING sensor -- Green Wire
int rearPingPin = 4;        //Pin for rear PING sensor -- Blue Wire
int leftPingPin = 7;        //Pin for left PING sensor -- Orange Wire
int rightPingPin = 8;       //Pin for right PING sensor -- Yellow Wire

int motorPin = 3;           //PWM Pin to control the ESC
int steerPin = 5;           //PWM Pin to control steering servo
int sDelay = 25;            //Amount of delay between pulses of ping
int startPin = 9;           //Input pin for pushbutton
int speakerPin = 10;        //Output pin for piezo element

int buttonPressed = 0;
boolean waitHere = true;

int toneFrequency = 440;

int MAX_RIGHT = 110;        //Maximum right turn in degrees
int MIN_RIGHT = 95;         //Slight right turn in degrees
int MAX_LEFT = 74;          //Maximum left turn in degrees
int MIN_LEFT = 87;          //Slight left turn in degrees
int CENTER = 92;            //Center point

int minDist = 7.6;            //The Minimum distance allowed (inches)


PingSensor frontSensor(frontPingPin, sDelay);       //Initialize front sensor
PingSensor rearSensor(rearPingPin, sDelay);         //Initialize rear sensor
PingSensor leftSensor(leftPingPin, sDelay);         //Initialize left sensor
PingSensor rightSensor(rightPingPin, sDelay);       //Initialize right sensor
Servo Motor;        //Initialize motor control
Servo Steer;        //Initialize steering control

double initFrontDist = 0;
double initRearDist = 0;
double initLeftDist = 0;
double initRightDist = 0;

boolean phaseOne = false;
boolean phaseTwo = false;
boolean phaseThree = false;
boolean phaseFour = false;

long previousMillis = 0;
long interval_1 = 2500; //3250 when battery is low
long interval_2 = 1750; //2250 when battery is low
long interval_3 = 1900; //1750 when.....

void moveStop()
{
    Motor.write(92);
}

void getInitDistance()
{
    frontSensor.sensorRead();                     //Read front sensor
    initFrontDist = frontSensor.getDistance();    //Get the last read distance
    rearSensor.sensorRead();                      //Read rear sensor
    initRearDist = rearSensor.getDistance();      //Get the last read distance
    leftSensor.sensorRead();                      //Read left sensor
    initLeftDist = leftSensor.getDistance();      //Get the last read distance
    rightSensor.sensorRead();                     //Read right sensor
    initRightDist = rightSensor.getDistance();    //Get the last read distance
}


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
      else
      {
        tone(speakerPin,toneFrequency,10); //Sound tone for operator to know that the button can be pressed.
      }
    }
}

void loop() 
{
    //Not being used
}

void startPark()
{
  boolean parking = true;
  delay(500);
  getInitDistance();

  phaseOnePark();

  parkingComplete();
}

boolean phaseOnePark()
{
    frontSensor.sensorRead();                //Read front sensor
    double fDist = frontSensor.getDistance();   //Get the last read distance
    rearSensor.sensorRead();                 //Read rear sensor
    double rDist = rearSensor.getDistance();    //Get the last read distance
    leftSensor.sensorRead();                 //Read left sensor
    double lDist = leftSensor.getDistance();    //Get the last read distance
    rightSensor.sensorRead();                //Read right sensor
    double rtDist = rightSensor.getDistance();  //Get the last read distance
    
    //Move backwards ~2.5 centimeters from original position then stop
    if(rDist-(initRearDist-2.5) > 0)
    {
      Steer.write(CENTER);                   //Center steering while reversing
      moveReverse();                         //Reverse motor
      phaseOne = false;
    }
    else
    {
      moveStop();                            //If this is accomplished stop motor
      phaseOne = true;
    }
    if(!phaseOne)
      phaseOnePark();
    else
    {
      previousMillis = millis();
      return phaseTwoPark();
    }
}
boolean phaseTwoPark()
{
    frontSensor.sensorRead();                //Read front sensor
    double fDist = frontSensor.getDistance();   //Get the last read distance
    rearSensor.sensorRead();                 //Read rear sensor
    double rDist = rearSensor.getDistance();    //Get the last read distance
    leftSensor.sensorRead();                 //Read left sensor
    double lDist = leftSensor.getDistance();    //Get the last read distance
    rightSensor.sensorRead();                //Read right sensor
    double rtDist = rightSensor.getDistance();  //Get the last read distance
    
    Serial.println("PhaseTwo initiated");
    if(phaseOne && !phaseTwo)
    {    
      unsigned long currentMillis = millis();
      Serial.println(currentMillis);
      Serial.println(previousMillis);    
      Serial.println(currentMillis - previousMillis);  
      if(currentMillis - previousMillis > interval_1)
      {
        moveStop();
        phaseTwo = true;
      }
      else if (rDist < 7.5)
      {
        moveStop();
        parkingFail();
      }
      else
      {
        Steer.write(MAX_RIGHT);
        moveReverse();
        phaseTwoPark();
      }
    }
    previousMillis = millis();
    return phaseThreePark();
}

boolean phaseThreePark()
{
    frontSensor.sensorRead();                //Read front sensor
    double fDist = frontSensor.getDistance();   //Get the last read distance
    rearSensor.sensorRead();                 //Read rear sensor
    double rDist = rearSensor.getDistance();    //Get the last read distance
    leftSensor.sensorRead();                 //Read left sensor
    double lDist = leftSensor.getDistance();    //Get the last read distance
    rightSensor.sensorRead();                //Read right sensor
    double rtDist = rightSensor.getDistance();  //Get the last read distance
    Serial.println("PhaseThree initiated");
    
    if(phaseOne && phaseTwo && !phaseThree)
    {
      unsigned long currentMillis = millis();
      Serial.println(currentMillis);
      Serial.println(previousMillis);    
      Serial.println(currentMillis - previousMillis);    
      if(currentMillis - previousMillis > interval_2)
      {
        Serial.println("STOP");
        moveStop();
        phaseThree = true;
        Steer.write(CENTER);
      }
      else if (rDist < 5)
      {
        moveStop();
        parkingFail();
      }
      else
      {
        Serial.println("Keep GOING!");
        Steer.write(MAX_LEFT);
        moveReverse();
        phaseThreePark();
      }
    }
    previousMillis = millis();
    return phaseFourPark();
}

boolean phaseFourPark()
{
    frontSensor.sensorRead();                //Read front sensor
    double fDist = frontSensor.getDistance();   //Get the last read distance
    rearSensor.sensorRead();                 //Read rear sensor
    double rDist = rearSensor.getDistance();    //Get the last read distance
    leftSensor.sensorRead();                 //Read left sensor
    double lDist = leftSensor.getDistance();    //Get the last read distance
    rightSensor.sensorRead();                //Read right sensor
    double rtDist = rightSensor.getDistance();  //Get the last read distance
    Serial.println("PhaseFour initiated");

/*    Serial.println("The values of PhaseFour is:");
    Serial.println(phaseFour);
    Serial.println("The values of PhaseThree is:");
    Serial.println(phaseThree);
    Serial.println("The values of PhaseTwo is:");
    Serial.println(phaseTwo);
    Serial.println("The values of PhaseOne is:");
    Serial.println(phaseOne);*/
    
    if(phaseOne && phaseTwo && phaseThree && !phaseFour)
    {
      unsigned long currentMillis = millis();
      Serial.println(currentMillis);
      Serial.println(previousMillis);    
      Serial.println(currentMillis - previousMillis);    
      if(currentMillis - previousMillis > interval_2)
      {
        Serial.println("STOP@4");
        moveStop();
        phaseFour = true;
        Steer.write(CENTER);
      }
      else if (fDist < 5)
      {
        moveStop();
        parkingFail();
      }
      else
      {
        Steer.write(MAX_RIGHT);
        moveForward();
        phaseFourPark();
      }
    }
    return true;
}

void parkingComplete()
{
  while(true)
  {
    moveStop();
    tone(speakerPin, toneFrequency);
    delay(400);
    noTone(speakerPin);
    delay(400);
  }
}
void parkingFail()
{
  while(true)
  {
    moveStop();
    tone(speakerPin, toneFrequency);
    delay(200);
    noTone(speakerPin);
    delay(200);
  }
}

void moveForward()
{
    Motor.writeMicroseconds(constrain(FORWARD_SLOW,1533,1550));
}

void moveReverse()
{
    Motor.writeMicroseconds(constrain(REVERSE_SLOWEST,1400, 1455));
}
void deBug()
{
    Serial.println("This is a Debug message");
}

