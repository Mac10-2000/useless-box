void toExtreme()
{
  bool state1 = digitalRead(SENSSWITCH);
  //enable chip
  

  
  do {
    for (int x = 0; x < 16; x++)
    {
      digitalWrite(STEPPIN, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEPPIN, LOW);
      delayMicroseconds(stepDelay);
    }

  } while ( digitalRead(SENSSWITCH) == state1);
  correct();
  //  digitalWrite(ENABLE, HIGH);
}

void correct()
{
  int c;
  if (digitalRead(SENSSWITCH) == HIGH) {
    c = 1;
  }
  if (digitalRead(SENSSWITCH) == LOW) {
    c = 12;
  }

  for (int x = 0; x < 16 * c; x++)

  {
    digitalWrite(STEPPIN, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEPPIN, LOW);
    delayMicroseconds(stepDelay);

  }

}
