#include <Servo.h>

Servo cloudLeft;
Servo cloudMid;
Servo cloudRight;
Servo sky;
Servo thunder;

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

  Serial.begin(9600);
  Serial.print('A');
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
  delay(100);
  analogWrite(redpin,   255);
  analogWrite(greenpin, 255);
  analogWrite(bluepin,  255);
  delay(100);
}

void nolight(int redpin, int greenpin, int bluepin){
  analogWrite(redpin,   255);
  analogWrite(greenpin, 255);
  analogWrite(bluepin,  255);
}

void showRight(){
  sky.write(110);
  delay(4500);
  sky.write(91);
}

void showLeft(){
  sky.write(80);
  delay(5500);
  sky.write(91);
}

void loop() {
  analogWrite(redMid,   0);
  analogWrite(greenMid, 0);
  analogWrite(blueMid,  0);

  analogWrite(redRight,   0);
  analogWrite(greenRight, 0);
  analogWrite(blueRight,  0);

  analogWrite(redLeft,   0);
  analogWrite(greenLeft, 0);
  analogWrite(blueLeft,  0);


  if (Serial.available() > 5) {
    // reads the queue
    upCloud = Serial.read();
    downCloud = Serial.read();
    storm = Serial.read();
    noStorm = Serial.read();
    changeRight = Serial.read();
    changeLeft = Serial.read();
  }

  if (upCloud){
    cloudDown(); 
    upCloud = false;
  } 
  if (downCloud){
    cloudUp();
    downCloud = false;
  }

  if (storm){
    while(true){
      lightning(redRight, greenRight, blueRight);
      lightning(redLeft, greenLeft, blueLeft);
      lightning(redMid, greenMid, blueMid);
      thunder.write(80);
      storm = false;
    }
  }
  if (noStorm){
    nolight(redRight, greenRight, blueRight);
    nolight(redLeft, greenLeft, blueLeft);
    nolight(redMid, greenMid, blueMid);
    noStorm = false;
  }

  if (changeLeft){
    showLeft();
    changeLeft = false;
  }
  if (changeRight){
    showRight();
    changeRight = false;
  }
}
