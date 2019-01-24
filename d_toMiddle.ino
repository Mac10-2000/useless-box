void toMiddle()
{
invert(DIRPIN);
  // Spin motor one rotation slowly
  for (int x = 0; x < ((STEPS_PER_REV * 16) / 4); x++)
  {
    digitalWrite(STEPPIN, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEPPIN, LOW);
    delayMicroseconds(stepDelay);

  }
}
void middle(int steps)
{

invert(DIRPIN);
  // Spin motor one rotation slowly
  for (int x = 0; x < (((STEPS_PER_REV * 16) / 4) - steps); x++)
  {
    digitalWrite(STEPPIN, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEPPIN, LOW);
    delayMicroseconds(stepDelay);

  }

}
