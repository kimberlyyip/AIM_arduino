
/*
  Kimberly Yip
  CS.232
  Human Controlled Beeping Light Sketch. Modified from the Blink Sketch.

  Moving the joystick to the left makes the LED dimmer. Moving the joystick to the right makes the LED brighter.
  When you push the joystick, like a button, the beeper makes a sound whose frequency is proportional to the brightness of the LED.

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

int ourLight = 11;
int ourBeeper = 9;
int joystickButtonPin = 6;

void setup() {
  pinMode(ourLight, OUTPUT);
  pinMode(ourBeeper, OUTPUT);
  pinMode(joystickButtonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int valueX = analogRead(A1);
  // Note: Dave said that the push button should connect to the digital pin with digitalRead, but that did not work. However, connecting it to the analog pin and using analogRead works. 
  int push = digitalRead(joystickButtonPin);

  // Divided the valueX by 4 for scaling.
  int lightValue = valueX/4;
  // Multiply the light value by 2 to make the frequencies audible.
  int beeperValue = (lightValue + 100) * 2;


  if (push == 0){ //Only sounds if the button is pushed.
    tone(ourBeeper, beeperValue, 50); 
  }
  
  analogWrite(ourLight, lightValue);
}



