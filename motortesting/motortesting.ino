/*#include <Servo.h>

#define MAX_SIGNAL 2000
#define MIN_SIGNAL 700
#define MOTOR_PIN 9

Servo motor;

void setup() {
  Serial.begin(9600);
  Serial.println("Program begin...");
  Serial.println("This program will calibrate the ESC.");

  motor.attach(MOTOR_PIN);

  Serial.println("Now writing maximum output.");
  Serial.println("Turn on power source, then wait 2 seconds and press any key.");
  motor.writeMicroseconds(MAX_SIGNAL);

  // Wait for input
  while (!Serial.available());
  Serial.read();

  // Send min output
  Serial.println("Sending minimum output");
  motor.writeMicroseconds(MIN_SIGNAL);

}



void loop() {
  // put your main code here, to run repeatedly:

}*/

/*
Coded by Marjan Olesch
Sketch from Insctructables.com
Open source - do what you want with this code!
*/
#include <Servo.h>


int value = 0; // set values you need to zero

Servo firstESC; //Create as much as Servoobject you want. You can controll 2 or more Servos at the same time

void setup() {

  firstESC.attach(9);    // attached to pin 9 I just do this with 1 Servo
  Serial.begin(9600);    // start serial at 9600 baud

}

void loop() {

//First connect your ESC WITHOUT Arming. Then Open Serial and follo Instructions
 
  firstESC.write(value);
 
  if(Serial.available()) 
  {
    Serial.println("Please give input!");
    value = Serial.parseInt();    // Parse an Integer from Serial
  }
}
