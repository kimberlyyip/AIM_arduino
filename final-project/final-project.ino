#include <Servo.h>

Servo cloudLeft;
Servo cloudMid;
Servo cloudRight;
Servo water;
Servo sky; 

int flashLeft = 11;
int flashRight = 12;
bool up = true;
bool down = false;

void setup() {
  pinMode(flashLeft, OUTPUT);
  pinMode(flashRight, OUTPUT);
  cloudLeft.attach(45);
  cloudMid.attach(44);
  cloudRight.attach(43);
  water.attach(9);
  sky.attach(15);
  Serial.begin(9600);
}

void timeOfDay();

void stormy(){
  // Lightning
  analogWrite(flashLeft, 255);
  analogWrite(flashRight, 255);
  delay(10);
  analogWrite(flashLeft, 0);
  delay(10);
  analogWrite(flashRight, 0);
  delay(50);
}

/* Cloud related functions */
void cloudDown(){
  cloudLeft.write(80);
  cloudMid.write(78);
  cloudRight.write(80);
  delay(2500);
  cloudLeft.write(90);
  cloudMid.write(93);
  cloudRight.write(91);
}

void cloudUp(){
  cloudLeft.write(105);
  cloudMid.write(107);
  cloudRight.write(106);
  delay(2500);
  cloudLeft.write(90);
  cloudMid.write(93);
  cloudRight.write(91);
}


void loop() {
  // put your main code here, to run repeatedly:
  // for (int j=0; j < 5; j++){
  //   stormy();
  // }
  if (up){
    cloudDown();
    up = false;
    down = true; 
  } 
  if (down){
    cloudUp();
    down = false;
    // up = true;
  }

}
