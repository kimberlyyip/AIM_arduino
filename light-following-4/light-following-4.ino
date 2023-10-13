/*
Kimberly Yip
CS.232: Art, Interactivity, and Microcontrollers

Implement some sort of smarter algorithm for approach #2 
to try to keep the detector servo from sweeping through the whole range every time. 
There are many reasons why you won't be able to get it perfect, 
but can you strive for making a light follower that 
--- at least sometimes --- approximates finding following the light as it moves 
without having to scan the entire field of view? */

#include <Servo.h>

Servo servoOne;
int angle = 0;

void setup() {
  servoOne.attach(44);
  Serial.begin(9600);
}

void loop() {
  int lightSensor;
  int left;
  int right;

  servoOne.write(angle + 20); //checks the right value
  lightSensor = analogRead(A5);
  right = lightSensor; 

  servoOne.write(angle - 20); //checks the left value
  lightSensor = analogRead(A5);
  left = lightSensor; 

  if(right < left){ //if the right value is less than the left value, the bright light is on the right
    angle = angle + 20;
  } else if(left < right){ //if the left value is less than the right value, the bright light is on the left
    angle = angle - 20;
  }

  //check to make sure the angle doesn't go out of bounds
  if (angle > 180){
    angle = angle - 30;
  } else if (angle < 0){
    angle = angle + 30;
  }

  delay(150);

}
