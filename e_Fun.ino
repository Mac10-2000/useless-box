void Fun()
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
void part1(int scenario) {
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
void part2(int scenario) {
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







inline void invert(byte pin)
{
  digitalWrite(pin, !digitalRead(pin));


}
