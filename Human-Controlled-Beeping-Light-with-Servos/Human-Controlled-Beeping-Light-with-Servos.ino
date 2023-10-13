
/*
  Kimberly Yip
  CS.232
  Human Controlled Beeping Light Sketch. Modified from the Blink Sketch.

  Moving the joystick to the left makes the LED dimmer. 
  Moving the joystick to the right makes the LED brighter.
  When you push the joystick, like a button, the beeper makes a sound whose frequency is proportional to the brightness of the LED.
  When the LED is brightest, the positional servo is in one position. 
  When the light is the dimmest, the positional servo is in a different position. 
  When the LED is in the middle, the positional servo is in the middle.
  The continuous rotation servo is spinning at its fastest in one direction when the LED is brightest. 
  The continuous rotation servo is spinning at its fastest in the opposite direction when the LED is the dimmest. 
  The continuous rotation servo is approximately motionless when the LED is in the middle. 


  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

#include <Servo.h>

Servo pServo;
Servo crServo;

int ourLight = 11;
int ourBeeper = 9;
int joystickButtonPin = 6;

void setup() {
  pinMode(ourLight, OUTPUT);
  pinMode(ourBeeper, OUTPUT);
  pinMode(joystickButtonPin, INPUT_PULLUP);
  pServo.attach(44);
  crServo.attach(45);
  Serial.begin(9600);
}

void loop() {
  int valueX = analogRead(A1);
  int push = digitalRead(joystickButtonPin);

  // Divided the valueX by 4 for scaling.
  int lightValue = valueX/4;
  // Multiply the light value by 2 to make the frequencies audible.
  int beeperValue = (lightValue + 100) * 2;
  // Divided the valueX by 6 for scaling (upper limit is now 170.5).
  int pServoValue = (valueX/6);

  pServo.write( pServoValue );
  crServo.write(map(valueX, 0, 1023, 80, 112));

  if (push == 0){ //Only sounds if the button is pushed.
    tone(ourBeeper, beeperValue, 50); 
  }
  analogWrite(ourLight, lightValue);
}



