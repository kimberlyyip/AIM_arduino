#include <Servo.h>

Servo cloudOne;
Servo cloudTwo;
Servo water;
Servo sky; 

int flashLeft = 11;
int flashRight = 12;

void setup() {
  pinMode(flashLeft, OUTPUT);
  pinMode(flashRight, OUTPUT);
  cloudOne.attach(44);
  cloudTwo.attach(45);
  water.attach(9);
  sky.attach(15);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

}
