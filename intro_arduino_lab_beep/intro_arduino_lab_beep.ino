int ourPin = 12;
void setup()
{
  pinMode(ourPin, OUTPUT);
}


void loop()
{
  tone(ourPin, 440);
  delay(1000);
  tone(ourPin, 523);
  delay(1000);
}