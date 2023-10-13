/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

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
  if (count == 0) {
    upOrDown = true;
    tone(ourBeeper, 130.81, 100);
  }
  else if (count == 255) {
    upOrDown = false;
    tone(ourBeeper, 261.63, 100);
  }
  if (upOrDown == true) {
    count += 1;
  }
  else {
    count -= 1;
  }
  analogWrite(ourLight, count);
  delay(500);
}
