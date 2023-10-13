/*
  Kimberly Yip
  CS.232
  Automated Beeping Light sketch modified from the Blink sketch.
  Slowly dims and brightens an LED overtime. A beeper beeps when the light is the brightest and when it is the dimmest.

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
int count = 0;
bool upOrDown = true;

void setup() {
  pinMode(ourLight, OUTPUT);
  pinMode(ourBeeper, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (count == 0) { //If the count starts at 0, we want to count upwards. We also want the beeper to beep.
    upOrDown = true;
    tone(ourBeeper, 130.81, 100);
  }
  else if (count == 255) { //If the count starts at 255, we want to count downwards. We also want the beeper to beep.
    upOrDown = false;
    tone(ourBeeper, 261.63, 100);
  }
  if (upOrDown == true) { //Count upwards
    count += 1;
  }
  else { //Count downwards
    count -= 1;
  }
  analogWrite(ourLight, count);
  delay(500);
}
