/*
Kimberly Yip
CS.232 Art, Interactivity, and Microcontrollers
Narrative Assignment

An adapted light following sketch attatched to a sculpture of the Hōkūleʻa.
Led by the Polynesian Voyaging Society, the Hōkūleʻa attempts to revive the traditional art of Polynesian voyaging and navigation.
To mimic the Hōkūleʻa and navigation by the stars, this sketch has a sculpture of the Hōkūleʻa attatched to two light sensors to allow for a more accurate light following.
The use of two light sensors was inspired by https://youtu.be/BgIA_BjH-Yk?si=nQs24miz3DkJAuJL 
*/

#include <Servo.h>

Servo servoBoat;
int lightSensorRight; 
int lightSensorLeft;
int angle;

void setup() {
  servoBoat.attach(44);
  Serial.begin(9600);
}

void loop(){
  lightSensorRight = analogRead(A0);
  // if the light sensor on the right of the boat is greater than the light sensor on the left of the boat
  // and less than 180 degrees, we want to move the boat to the right to follow the light
  // A buffer of 15 is added to ensure that if the light is at the right angle and hitting both light sensors with the same value,
  // it does not get stuck 
  if(lightSensorRight > 15 + lightSensorLeft && angle < 180){
    angle++;
    servoBoat.write(angle);
    delay(10);
  } 
  
  lightSensorLeft = analogRead(A5);
  // if the light sensor on the left of the boat is greater than the light sensor on the right of the boat
  // and greater than 0 degrees, we want to move the boat to the left to follow the light
  // A buffer of 15 is added to ensure that if the light is at the right angle and hitting both light sensors with the same value,
  // it does not get stuck 
  if(lightSensorLeft > 15 + lightSensorRight && angle > 0){
    angle --; 
    servoBoat.write(angle);
    delay(10);
  }

}