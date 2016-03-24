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
int speakerPin = 10;        //Output pin for piezo element

int buttonPressed = 0;
boolean waitHere = true;

int toneFrequency = 440;

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

boolean phaseOne = false;
boolean phaseTwo = false;
boolean phaseThree = false;
boolean phaseFour = false;

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
    /*while(waitHere)
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
    }*/
}

void loop() 
{
      // read the value from the sensor:
  int sensorValue = readsensor();    

  //Spit it out the serial port
  Serial.print("A0: ");
  Serial.println(sensorValue,DEC);

  // Delay for so many milliseconds:
  delay(100);    
}

int readFsensor()
{
  static int fBoxcar[10];

  frontSensor.sensorRead();

  /*Serial.print("Address:");
  Serial.println((unsigned int) boxcar, HEX);

  Serial.print("0:");
  Serial.println(*boxcar);
  Serial.print("1:");
  Serial.println(*(boxcar+1));
  Serial.print("2:");
  Serial.println(*(boxcar+2));
  Serial.print("3:");
  Serial.println(*(boxcar+3));
  Serial.print("4:");
  Serial.println(*(boxcar+4));
  Serial.print("5:");
  Serial.println(*(boxcar+5));
  Serial.print("6:");
  Serial.println(*(boxcar+6));
  Serial.print("7:");
  Serial.println(*(boxcar+7));
  Serial.print("8:");
  Serial.println(*(boxcar+8));
  Serial.print("9:");
  Serial.println(*(boxcar+9));*/
  
  
  fBoxcar[9] = fBoxcar[8];
  fBoxcar[8] = fBoxcar[7];
  fBoxcar[7] = fBoxcar[6];
  fBoxcar[6] = fBoxcar[5];
  fBoxcar[5] = fBoxcar[4];
  fBoxcar[4] = fBoxcar[3];
  fBoxcar[3] = fBoxcar[2];
  fBoxcar[2] = fBoxcar[1];
  fBoxcar[1] = fBoxcar[0];
  fBoxcar[0] = frontSensor.getDistance();
  
  return ((fBoxcar[9]+fBoxcar[8]+fBoxcar[7]+fBoxcar[6]+fBoxcar[5]+fBoxcar[4]+fBoxcar[3]+fBoxcar[2]+fBoxcar[1]+fBoxcar[0])/10);
}

int readRsensor()
{
  static int rBoxcar[10];

  rearSensor.sensorRead();

  /*Serial.print("Address:");
  Serial.println((unsigned int) boxcar, HEX);

  Serial.print("0:");
  Serial.println(*boxcar);
  Serial.print("1:");
  Serial.println(*(boxcar+1));
  Serial.print("2:");
  Serial.println(*(boxcar+2));
  Serial.print("3:");
  Serial.println(*(boxcar+3));
  Serial.print("4:");
  Serial.println(*(boxcar+4));
  Serial.print("5:");
  Serial.println(*(boxcar+5));
  Serial.print("6:");
  Serial.println(*(boxcar+6));
  Serial.print("7:");
  Serial.println(*(boxcar+7));
  Serial.print("8:");
  Serial.println(*(boxcar+8));
  Serial.print("9:");
  Serial.println(*(boxcar+9));*/
  
  
  rBoxcar[9] = rBoxcar[8];
  rBoxcar[8] = rBoxcar[7];
  rBoxcar[7] = rBoxcar[6];
  rBoxcar[6] = rBoxcar[5];
  rBoxcar[5] = rBoxcar[4];
  rBoxcar[4] = rBoxcar[3];
  rBoxcar[3] = rBoxcar[2];
  rBoxcar[2] = rBoxcar[1];
  rBoxcar[1] = rBoxcar[0];
  rBoxcar[0] = rearSensor.getDistance();
  
  return ((rBoxcar[9]+rBoxcar[8]+rBoxcar[7]+rBoxcar[6]+rBoxcar[5]+rBoxcar[4]+rBoxcar[3]+rBoxcar[2]+rBoxcar[1]+rBoxcar[0])/10);
}
int readlsensor()
{
  static int lBoxcar[10];

  frontSensor.sensorRead();

  /*Serial.print("Address:");
  Serial.println((unsigned int) boxcar, HEX);

  Serial.print("0:");
  Serial.println(*boxcar);
  Serial.print("1:");
  Serial.println(*(boxcar+1));
  Serial.print("2:");
  Serial.println(*(boxcar+2));
  Serial.print("3:");
  Serial.println(*(boxcar+3));
  Serial.print("4:");
  Serial.println(*(boxcar+4));
  Serial.print("5:");
  Serial.println(*(boxcar+5));
  Serial.print("6:");
  Serial.println(*(boxcar+6));
  Serial.print("7:");
  Serial.println(*(boxcar+7));
  Serial.print("8:");
  Serial.println(*(boxcar+8));
  Serial.print("9:");
  Serial.println(*(boxcar+9));*/
  
  
  lBoxcar[9] = lBoxcar[8];
  lBoxcar[8] = lBoxcar[7];
  lBoxcar[7] = lBoxcar[6];
  lBoxcar[6] = lBoxcar[5];
  lBoxcar[5] = lBoxcar[4];
  lBoxcar[4] = lBoxcar[3];
  lBoxcar[3] = lBoxcar[2];
  lBoxcar[2] = lBoxcar[1];
  lBoxcar[1] = lBoxcar[0];
  lBoxcar[0] = leftSensor.getDistance();
  
  return ((lBoxcar[9]+lBoxcar[8]+lBoxcar[7]+lBoxcar[6]+lBoxcar[5]+lBoxcar[4]+lBoxcar[3]+lBoxcar[2]+lBoxcar[1]+lBoxcar[0])/10);
}
int readRtsensor()
{
  static int RtBoxcar[10];

  rightSensor.sensorRead();

  /*Serial.print("Address:");
  Serial.println((unsigned int) boxcar, HEX);

  Serial.print("0:");
  Serial.println(*boxcar);
  Serial.print("1:");
  Serial.println(*(boxcar+1));
  Serial.print("2:");
  Serial.println(*(boxcar+2));
  Serial.print("3:");
  Serial.println(*(boxcar+3));
  Serial.print("4:");
  Serial.println(*(boxcar+4));
  Serial.print("5:");
  Serial.println(*(boxcar+5));
  Serial.print("6:");
  Serial.println(*(boxcar+6));
  Serial.print("7:");
  Serial.println(*(boxcar+7));
  Serial.print("8:");
  Serial.println(*(boxcar+8));
  Serial.print("9:");
  Serial.println(*(boxcar+9));*/
  
  
  RtBoxcar[9] = RtBoxcar[8];
  RtBoxcar[8] = RtBoxcar[7];
  RtBoxcar[7] = RtBoxcar[6];
  RtBoxcar[6] = RtBoxcar[5];
  RtBoxcar[5] = RtBoxcar[4];
  RtBoxcar[4] = RtBoxcar[3];
  RtBoxcar[3] = RtBoxcar[2];
  RtBoxcar[2] = RtBoxcar[1];
  RtBoxcar[1] = RtBoxcar[0];
  RtBoxcar[0] = rightSensor.getDistance();
  
  return ((RtBoxcar[9]+RtBoxcar[8]+RtBoxcar[7]+RtBoxcar[6]+RtBoxcar[5]+RtBoxcar[4]+RtBoxcar[3]+RtBoxcar[2]+RtBoxcar[1]+RtBoxcar[0])/10);
}

void startPark()
{
  boolean parking = true;
  getInitDistance();

  /*while(parking)
  {
    frontSensor.sensorRead();                //Read front sensor
    int fDist = frontSensor.getDistance();   //Get the last read distance
    rearSensor.sensorRead();                 //Read rear sensor
    int rDist = rearSensor.getDistance();    //Get the last read distance
    leftSensor.sensorRead();                 //Read left sensor
    int lDist = leftSensor.getDistance();    //Get the last read distance
    rightSensor.sensorRead();                //Read right sensor
    int rtDist = rightSensor.getDistance();  //Get the last read distance
  
   /* Serial.println(rDist);
    //Move backwards ~4 inches from original position then stop
    if(rDist-(initRearDist-4) > 0)
    {
      Steer.write(CENTER);                   //Center steering while reversing
      moveReverse();                         //Reverse motor
      phaseOne = false;
    }
    else if(rtDist <= initRightDist)
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
    if(phaseOne && !phaseTwo)
    {
      Serial.println("PhaseTwo initiated");
      getInitDistance();
      if(rDist-(initRearDist-2) > 0)
      {
        Steer.write(MAX_RIGHT);
        moveReverse();
      }
    }
    if(phaseOne && phaseTwo && phaseThree /* && phaseFour)
   /* {
      parking = false;
    }
  }*/

  phaseOnePark();

  parkingComplete();
}

boolean phaseOnePark()
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
      Steer.write(CENTER);                   //Center steering while reversing
      moveReverse();                         //Reverse motor
      phaseOne = false;
    }
    else if(rtDist <= initRightDist)
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
      return phaseTwoPark();
}
boolean phaseTwoPark()
{
    frontSensor.sensorRead();                //Read front sensor
    int fDist = frontSensor.getDistance();   //Get the last read distance
    rearSensor.sensorRead();                 //Read rear sensor
    int rDist = rearSensor.getDistance();    //Get the last read distance
    leftSensor.sensorRead();                 //Read left sensor
    int lDist = leftSensor.getDistance();    //Get the last read distance
    rightSensor.sensorRead();                //Read right sensor
    int rtDist = rightSensor.getDistance();  //Get the last read distance
    
    if(phaseOne && !phaseTwo)
    {
      Serial.println("PhaseTwo initiated");
      getInitDistance();
      if(rDist-(initRearDist-2) > 0)
      {
        Steer.write(MAX_RIGHT);
        moveReverse();
        phaseTwoPark();
      }
      else
      {
        moveStop();
        phaseTwo = true;
      }
    }

    return phaseThreePark();
}

boolean phaseThreePark()
{
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

void moveForward()
{
    Motor.write(100);
}

void moveReverse()
{
    Motor.writeMicroseconds(constrain(REVERSE_SLOW,1400, 1430));
}


void deBug()
{
    Serial.println("This is a Debug message");
}

