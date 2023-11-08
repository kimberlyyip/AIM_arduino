#include <Servo.h>

Servo cloudLeft;
Servo cloudMid;
Servo cloudRight;
Servo skyLeft; 
Servo skyRight;

bool up = true;
bool down = true;
bool storm = true;
bool nostorm = true;

// Values for RGB on the right side of the frame
const int redRight   = 9;
const int greenRight = 10;
const int blueRight  = 11;

// Values for RGB on the left side of the frame
const int redLeft   = 16;
const int greenLeft = 15;
const int blueLeft  = 14;

// Values for RGB in the middle of the frame
const int redMid   = 5;
const int greenMid = 6;
const int blueMid  = 7;


void setup() {
  skyRight.attach(38);
  skyLeft.attach(39);

  cloudLeft.attach(45);
  cloudMid.attach(44);
  cloudRight.attach(43);
  
  pinMode(redRight,   OUTPUT);
  pinMode(greenRight, OUTPUT);
  pinMode(blueRight,  OUTPUT);

  pinMode(redLeft,   OUTPUT);
  pinMode(greenLeft, OUTPUT);
  pinMode(blueLeft,  OUTPUT);

  pinMode(redMid,   OUTPUT);
  pinMode(greenMid, OUTPUT);
  pinMode(blueMid,  OUTPUT);

  Serial.begin(9600);
}

/** Cloud related functions **/
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
  cloudLeft.write(104);
  cloudMid.write(107);
  cloudRight.write(107);
  delay(2500);
  cloudLeft.write(90);
  cloudMid.write(93);
  cloudRight.write(91);
}

void lightning(int redpin, int greenpin, int bluepin){
  analogWrite(redpin,   0);
  analogWrite(greenpin, 0);
  analogWrite(bluepin,  0);
  delay(50);
  analogWrite(redpin,   255);
  analogWrite(greenpin, 255);
  analogWrite(bluepin,  255);
  delay(50);
}

void nolight(int redpin, int greenpin, int bluepin){
  analogWrite(redpin,   255);
  analogWrite(greenpin, 255);
  analogWrite(bluepin,  255);
}

void showLeft(){
  skyRight.write(80);
  skyLeft.write(80);
}

void showRight(){
  skyRight.write(100);
  skyLeft.write(100);
}

void loop() {
  // if (up){
  //   cloudDown();
  //   up = false;
  //   down = true; 
  // } 
  // if (down){
  //   cloudUp();
  //   down = false;
  //   // up = true;
  // }

  // if (storm){
  //   lightning(redRight, greenRight, blueRight);
  //   lightning(redLeft, greenLeft, blueLeft);
  //   lightning(redMid, greenMid, blueMid);
  // }

  nolight(redRight, greenRight, blueRight);
  nolight(redLeft, greenLeft, blueLeft);
  nolight(redMid, greenMid, blueMid);

  
  

  

}
