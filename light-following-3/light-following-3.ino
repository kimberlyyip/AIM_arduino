/*
Kimberly Yip
CS.232: Art, Interactivity, and Microcontrollers

As an alternative approach, have the servo with the photocell on it continually sweep back and forth, 
and add a second servo (placed on the table as close as you reasonably can to the first servo) to point near the brightest spot. 
The first servo should never stop sweeping; 
the second servo should move when it can to update its estimate as to where the light source is. 
There are admittedly some geometry issues in getting this perfect, since the two servos aren't at quite the same location; just get it roughly right. */

#include <Servo.h>

Servo servoOne;
Servo servoTwo;

void setup() {
  servoOne.attach(44);
  servoTwo.attach(45);
  Serial.begin(9600);
}

void loop() {
  int lightSensor;
  //QUESTION: should the following servo (the one that points to where the brightest light is), be reset to its original position after every sweep?
  //or should it remember the last location of the brightest light from the last sweep
  int minimum = 1000; //Keeps track of the minimum value
  int angle;

  //Moves the servoOne and light sensor from one end to the other, reading the value of the light sensor each time
  for (int j = 0; j < 180; j++){
    servoOne.write(j);
    lightSensor = analogRead(A5);
    //If the lightSensor value is less than the current minimum, set value of minimum to light sensor value
    if (lightSensor <= minimum){
      minimum = lightSensor;
      angle = j;
    }
    delay(50);
  }
  servoTwo.write(angle); //Move servoTwo when a new minimum value is detected.
}
