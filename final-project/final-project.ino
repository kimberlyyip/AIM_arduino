#include <Servo.h>

// Declaring Servos
Servo cloudLeft;
Servo cloudMid;
Servo cloudRight;
Servo sky;
Servo thunder;

// Declaring boolean values used
bool upCloud;
bool downCloud; 
bool storm;
bool noStorm;
bool changeRight; 
bool changeLeft;

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
  sky.attach(38);
  thunder.attach(22);

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

  pinMode(26, INPUT);

  Serial.begin(9600);
  // Ensures the arduino and python connection is established well
  Serial.print('A');
}

/** Cloud related functions **/
// Brings the clouds down
void cloudDown(){
  cloudLeft.write(80);
  cloudMid.write(78);
  cloudRight.write(80);
  delay(2500);
  cloudLeft.write(90);
  cloudMid.write(93);
  cloudRight.write(91);
}

// Brings the clouds up
void cloudUp(){
  cloudLeft.write(104);
  cloudMid.write(107);
  cloudRight.write(107);
  delay(2500);
  cloudLeft.write(90);
  cloudMid.write(93);
  cloudRight.write(91);
}

// Triggers lightning
void lightning(int redpin, int greenpin, int bluepin){
  analogWrite(redpin,   0);
  analogWrite(greenpin, 0);
  analogWrite(bluepin,  0);
  delay(100);
  analogWrite(redpin,   255);
  analogWrite(greenpin, 255);
  analogWrite(bluepin,  255);
  delay(100);
}

// Keeps a constant light on to illuminate the backdrop
void constantlight(int redpin, int greenpin, int bluepin){
  analogWrite(redpin,   0);
  analogWrite(greenpin, 0);
  analogWrite(bluepin,  0);
}

// Turns the rotating backdrop right: midday -> night -> sunriseset
void showRight(){
  sky.write(110);
  delay(1000);
  while (digitalRead(26) != LOW){
    sky.write(110);
  }
  sky.write(92);
}

// Turns the rotating backdrop left: midday -> sunriseset -> night
void showLeft(){
  sky.write(80);
  delay(1000);
  while (digitalRead(26) != LOW){
    sky.write(80);
  }
  sky.write(92);
}

void loop() {
  if (Serial.available() > 5) {
    // reads the queue of data sent by python
    upCloud = Serial.read();
    downCloud = Serial.read();
    storm = Serial.read();
    noStorm = Serial.read();
    changeRight = Serial.read();
    changeLeft = Serial.read();
  }

  // If the cloud is currently up, bring the clouds down.
  if (upCloud){
    cloudDown(); 
    upCloud = false;
  } 
  // If the cloud is currently down, bring the clouds up.
  if (downCloud){
    cloudUp();
    downCloud = false;
  }

  // If it is stormy, turn on lightning and thunder
  if (storm){
    while(true){
      lightning(redRight, greenRight, blueRight);
      lightning(redLeft, greenLeft, blueLeft);
      lightning(redMid, greenMid, blueMid);
      thunder.write(82);
      storm = false;
    }
  }

  // If it is not stormy, keep lights on to illuminate the backdrop
  if (noStorm){
    constantlight(redRight, greenRight, blueRight);
    constantlight(redLeft, greenLeft, blueLeft);
    constantlight(redMid, greenMid, blueMid);
    noStorm = false;
  }

  // If changeLeft, turn the backdrop left
  if (changeLeft){
    showLeft();
    changeLeft = false;
  }

  // If changeRight, turn the backdrop right
  if (changeRight){
    showRight();
    changeRight = false;
  }
}
