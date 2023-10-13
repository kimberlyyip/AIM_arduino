/* 
Author: Kimberly Yip
CS.232 Art, Interactivity, and Microcontrollers

This sketch controls a zoetrope (a moving animation similar to a flipbook). 
The speed at which the zoetrope spins is controlled by a potentiometer. 
Along with the zoetrope is an accompanying song, "Fais Do Do." 
The tempo of the song corresponds with the speed of the zoetrope and is also controlled by a potentiometer.
This is for the Embodied Electronic Emotions assignment for the emotion: excited. 
The increasing speed and tempo conveys increased excitement, attempting to abstractly embody the physical attributes associated with excitement. */

#include <Servo.h>

Servo crServo;
int ourBeeper = 9;

void setup() {
  crServo.attach(45);
  pinMode(ourBeeper, OUTPUT);
  Serial.begin(9600);
} 

void loop() {
  //Array to store the frequencies to the song "Fais Do Do."
  int pitch[66] = {277.18, 246.94, 220.00, 0, 220.00, 246.94, 220.00, 246.94, 277.18, 220.00, 277.18, 246.94, 220.00, 0, 
    220.00, 246.94, 277.18, 246.94, 220.00, 277.18, 0, 277.18, 293.66, 329.63, 246.94, 0, 246.94, 277.18, 293.66, 392.63, 
    246.94, 0, 246.94, 277.18, 293.66, 329.63, 246.94, 220.00, 246.94, 220.00, 246.94, 277.18, 293.66, 329.63, 246.94, 
    277.18, 246.94, 220.00, 0, 220.00, 246.94, 220.00, 246.94, 277.18, 220.00, 277.18, 246.94, 220.00, 0, 220.00, 246.94, 
    277.18, 246.94, 220.00};
  //Array to store the delays for note length for the song "Fais Do Do."
  int duration[66] = {1000, 500, 1000, 10, 500, 350, 350, 350, 1000, 500, 1000, 500, 1000, 10, 500, 350, 350, 350, 1000, 
    500, 10, 350, 350, 350, 1000, 10, 500, 350, 350, 350, 1000, 10, 500, 350, 350, 350, 350, 350, 350, 350, 350, 350, 1350, 
    1000, 500, 1000, 10, 500, 350, 350, 350, 1000, 500, 1000, 500, 1000, 10, 500, 350, 350, 350, 1000};

  //Nested loop that allows the tempo and speed to update dynamically according to the potentiometer. 
  for (int j=0; j < 66; j++){
    //pot value: min= 0; max= 1023
    int pot = analogRead(A0); //reads the value of the pot every loop to get a dynamically updated 
    int tempo = map(pot, 0, 1023, 1, 10); //controlls the tempo of the music
    int speed = map(pot, 0, 1023, 80, 60); //controlls the speed of the zoetrope

    if (pot == 0){ //a way to turn the sculpture off
      tone(ourBeeper, 0);
      crServo.write(90);
    } else {
      //crServo speed: fastest = 60; slowest = 90
      crServo.write(speed); //Have the speed of the crServo change along with the tempo of the music
      tone(ourBeeper, pitch[j]);
      delay(duration[j]/tempo);
    }  
  }
}