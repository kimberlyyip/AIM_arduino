/*
Kimberly Yip
CS.232: Art, Interactivity, and Microcontrollers

Create an enhanced version of the above where after the servo completes its sweep, 
it stops and moves to the brightest point it had seen. 
Delay a moment, then repeat: 
sweep again, then after sweeping, 
point to the brightest spot. 
Repeat forever.*/

#include <Servo.h>

Servo servoOne;

void setup() {
  servoOne.attach(44);
  Serial.begin(9600);
}

void loop() {
  int lightSensor;
  int minimum = 1000; //Keeps track of the minimum value
  int angle; //Keeps track of the angle where the minimum value is found
  
  //Moves the servo and light sensor from one end to the other, reading the value of the light sensor each time
  for (int j = 0; j < 180; j++){
    servoOne.write(j);
    lightSensor = analogRead(A5);
    //If the lightSensor value is less than the current minimum, set value of minimum to light sensor value
    if (lightSensor < minimum){
      minimum = lightSensor;
      angle = j;
    }
    delay(50);
  }
  delay(100);
  servoOne.write(angle);
  delay(1000);
}
