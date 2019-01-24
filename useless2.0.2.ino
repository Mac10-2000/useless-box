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
const int RAND = 5;         // Pin used as RandomSeed
const int stepDelay = 100;  //delay between steps in microsteps

// Motor steps per rotation
const int STEPS_PER_REV = 200;
//read start value of switch
boolean switchAtStart = digitalRead(SENSSWITCH);

bool state2;
boolean state1;
const int stepCount = 100;

void setup() {
  Serial.begin(9600);
  // Setup the pins as Outputs
  pinMode(STEPPIN, OUTPUT);
  pinMode(DIRPIN, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(SENSSWITCH, INPUT);
  pinMode(RAND, INPUT);

  //sixteenth steps
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);
  Serial.println("hey");
  digitalWrite(DIRPIN, HIGH);
  reset();                    //moves the switch to the correct position
  //disable chip to enable later in software
  pinMode(ENABLE, HIGH);
  state2 = digitalRead(SENSSWITCH);
  Serial.println(switchAtStart);
  Serial.println(state2);
  randomSeed(analogRead(RAND));
}

void loop() {



  state1 = digitalRead(SENSSWITCH);     //Checks if the State of the switch changes
  if (state1 != state2) {
    int delay1 = random(21);
    if (delay1 == 20) {
      delay(3000);
    }
    delay(500);
    digitalWrite(ENABLE, LOW);
    delay(5);

    Fun();                              //Main code,executet only when switch changes

    // Pause for one second
    digitalWrite(ENABLE, HIGH);
    state1 = digitalRead(SENSSWITCH);
    state2 = digitalRead(SENSSWITCH);

  }


  //disable chip
  digitalWrite(ENABLE, HIGH);

  state2 = state1;
}

//function


void reset() {                    //executed in the very beginning to garantee the correct position of the switch
  digitalWrite(ENABLE, LOW);
  delay(5);
  toExtreme();
  toMiddle();
  digitalWrite(ENABLE, HIGH);

}


void toExtreme()                //Moves the switch to the end of the slide/ until it gets flipped
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

void correct()            //Corrects the problem that the switch isn´t at the end of the slide when it gets flipped
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


void toMiddle()         //moves the switch from the extreme position to the Middle
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
void middle(int steps)                  //moves the switch to the middle from any position  /needs the distance from the last extreme to the current position
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

}void Fun()         //Main code running after the switchstate changes
{ int dir = random(1,3);
int rep = random(21);
Serial.println("dir");
Serial.print(dir);
  int scenario =random(1,4);
  int scenario2 =random(1,4);

//if (delay1==20){delay(3000);}

  
Serial.print(scenario);
  switch (dir) {
    case 1 :
      digitalWrite(DIRPIN, HIGH);

      break;
    case 2 :
      digitalWrite(DIRPIN, LOW);

      break;
    default:
      digitalWrite(DIRPIN, HIGH);

      break;
  }
  
  part1(scenario);

 // invert(DIRPIN);

  part2(scenario2);
if(rep==20){
  Fun();}


}
void part1(int scenario) {     // part of the code which slides the switch into the extreme position whith diverent movement options
  int rep = random(11);
  Serial.print(rep);
  int steps;
  switch (scenario) {
    case 1 :
      
      toExtreme();
      break;
      case 2 :
      toExtreme();
      toExtreme();
      break;
    case 3 :

      toExtreme();
      break;
    default:
      toExtreme();

      break;



  }
}
void part2(int scenario) {    // part of the code which slides the switch back to the middleposition with diverent movement options
  int rep = random(4,6);
  switch (rep) {
    case 1 :
      toMiddle();
      invert(DIRPIN);
      toMiddle();
      invert(DIRPIN);
      toMiddle();
      break;
    case 2 :
      toMiddle();
      middle(stepCount);
      invert(DIRPIN);
      middle(stepCount);
      break;
    case 3 :
      toMiddle();

      break;
    default:

      toMiddle();

      break;
      
      
      }

  //toMiddle();

  
}







inline void invert(byte pin)// inverts the pinstate of the pin used
{
  digitalWrite(pin, !digitalRead(pin));


}
