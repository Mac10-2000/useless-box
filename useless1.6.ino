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
const int RAND= 5;
const int stepDelay = 100;  //delay between steps in microsteps

// Motor steps per rotation
const int STEPS_PER_REV = 200;
//read start value of switch
boolean switchAtStart = digitalRead(SENSSWITCH);

bool state2;
boolean state1;
const int stepCount=100;

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
  reset();
  //disable chip to enable later in software
  pinMode(ENABLE, HIGH);
  state2 = digitalRead(SENSSWITCH);
  Serial.println(switchAtStart);
  Serial.println(state2);
randomSeed(analogRead(RAND));
}

void loop() {



  state1 = digitalRead(SENSSWITCH);
//  Serial.println(state1);
 // Serial.println(state2);
  if (state1 != state2) {
   int delay1 =random(21);
   if (delay1==20){delay(3000);}
delay(500); 
digitalWrite(ENABLE,LOW);
delay(5);

    Fun();
    
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


void reset() {
digitalWrite(ENABLE,LOW);
delay(500);
  toExtreme();
  toMiddle();
  digitalWrite(ENABLE, HIGH);

}
