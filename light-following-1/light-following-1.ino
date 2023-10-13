/*
Kimberly Yip
CS.232: Art, Interactivity, and Microcontrollers

Sweep the servo from one end of its range to the other, 
and print out via the Serial monitor the minimum value seen (that's the brightest point), 
and at what angle it was found. 
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
  Serial.println("Servo minimum value seen: ");
  Serial.println(minimum);
  Serial.println("Angle at which minimum value was found: ");
  Serial.println(angle);
}
