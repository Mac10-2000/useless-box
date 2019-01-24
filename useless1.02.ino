// Define Constants

// Connections to A4988
const int STEPPIN = 10; // Step
const int DIRPIN = 11;  // Direction
const int ENABLE = 6;   //chip enable
const int SENSSWITCH = 4; //switch on top of the box
/*
   Microstepping is archieved by pulling pins MS1, MS2, MS3 high or low. See table

   MS1  MS2   MS3   Step resolution
   -------------------------
   low  low   low   full step
   high low   low   half step
   low  high  low   quarter step
   high high  low   eighth step
   high high  high  sixteenth step
*/
const int MS1 = 7;      //Pins for microstepping
const int MS2 = 8;
const int MS3 = 9;

const int stepDelay = 100;  //delay between steps in microsteps

// Motor steps per rotation
const int STEPS_PER_REV = 200;

void setup() {
  // Setup the pins as Outputs
  pinMode(STEPPIN, OUTPUT);
  pinMode(DIRPIN, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(SENSSWITCH, INPUT);

  //sixteenth steps
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);

  //read start value of switch
  int switchAtStart = digitalRead(SENSSWITCH);

  pinMode(ENABLE, LOW);
  reset();

  //disable chip to enable later in software
  pinMode(ENABLE, HIGH);
}
void loop() {
  int switchState = digitalRead(SENSSWITCH);
  if (switchState == HIGH)
  {
    toFront();
    frontToMiddle();

    // Pause for one second
    delay(1000);
  }
  else
  {
    //disable chip
    digitalWrite(ENABLE, HIGH);

  }

}

//function


void reset() {
  toBack();
  toFront();
  frontToMiddle();
  digitalWrite(ENABLE, HIGH);

}
void toFront()
{

  //enable chip
  digitalWrite(ENABLE, LOW);
  delay(500);

  digitalWrite(DIRPIN, LOW);
  do {
    for (int x = 0; x < 16; x++)
    {
      digitalWrite(STEPPIN, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEPPIN, LOW);
      delayMicroseconds(stepDelay);

    }
  } while (digitalRead(SENSSWITCH) == HIGH);




  correct();
}
void toBack()
{

  //enable chip
  digitalWrite(ENABLE, LOW);
  delay(500);

  digitalWrite(DIRPIN, LOW);
  do {
    for (int x = 0; x < 16; x++)
    {
      digitalWrite(STEPPIN, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEPPIN, LOW);
      delayMicroseconds(stepDelay);

    }
  } while (digitalRead(SENSSWITCH) == LOW);

  correct();





}
void frontToMiddle()
{

  //enable chip
  digitalWrite(ENABLE, LOW);
  delay(500);

  // Set motor direction clockwise
  digitalWrite(DIRPIN, HIGH);

  // Spin motor one rotation slowly
  for (int x = 0; x < ((STEPS_PER_REV * 16) / 4); x++)
  {
    digitalWrite(STEPPIN, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEPPIN, LOW);
    delayMicroseconds(stepDelay);

  }

}
void correct()
{

  for (int x = 0; x < 16 * 12; x++)
  {
    digitalWrite(STEPPIN, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(STEPPIN, LOW);
    delayMicroseconds(stepDelay);

  }

}
