//Written By Nikodem Bartnik - nikodembartnik.pl
#define STEPPER_PIN_1 A0
#define STEPPER_PIN_2 A1
#define STEPPER_PIN_3 A2
#define STEPPER_PIN_4 A3
#define STEPPER_PIN_5 6
#define STEPPER_PIN_6 7
#define STEPPER_PIN_7 8
#define STEPPER_PIN_8 9
int step_number = 0;
void setup() {
pinMode(STEPPER_PIN_1, OUTPUT);
pinMode(STEPPER_PIN_2, OUTPUT);
pinMode(STEPPER_PIN_3, OUTPUT);
pinMode(STEPPER_PIN_4, OUTPUT);
pinMode(STEPPER_PIN_5, OUTPUT);
pinMode(STEPPER_PIN_6, OUTPUT);
pinMode(STEPPER_PIN_7, OUTPUT);
pinMode(STEPPER_PIN_8, OUTPUT);

}

void loop() {
 
  OneStep(false);
  delay(2);
  

}


void OneStep(bool dir){
    if(dir){
switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  digitalWrite(STEPPER_PIN_5, HIGH);
  digitalWrite(STEPPER_PIN_6, LOW);
  digitalWrite(STEPPER_PIN_7, LOW);
  digitalWrite(STEPPER_PIN_8, LOW);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  digitalWrite(STEPPER_PIN_5, LOW);
  digitalWrite(STEPPER_PIN_6, HIGH);
  digitalWrite(STEPPER_PIN_7, LOW);
  digitalWrite(STEPPER_PIN_8, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  digitalWrite(STEPPER_PIN_5, LOW);
  digitalWrite(STEPPER_PIN_6, LOW);
  digitalWrite(STEPPER_PIN_7, HIGH);
  digitalWrite(STEPPER_PIN_8, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  digitalWrite(STEPPER_PIN_5, LOW);
  digitalWrite(STEPPER_PIN_6, LOW);
  digitalWrite(STEPPER_PIN_7, LOW);
  digitalWrite(STEPPER_PIN_8, HIGH);
  break;
} 
  }else{
    switch(step_number){
  case 0:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, HIGH);
  digitalWrite(STEPPER_PIN_5, LOW);
  digitalWrite(STEPPER_PIN_6, LOW);
  digitalWrite(STEPPER_PIN_7, LOW);
  digitalWrite(STEPPER_PIN_8, HIGH);
  break;
  case 1:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, HIGH);
  digitalWrite(STEPPER_PIN_4, LOW);
  digitalWrite(STEPPER_PIN_5, LOW);
  digitalWrite(STEPPER_PIN_6, LOW);
  digitalWrite(STEPPER_PIN_7, HIGH);
  digitalWrite(STEPPER_PIN_8, LOW);
  break;
  case 2:
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, HIGH);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  digitalWrite(STEPPER_PIN_5, LOW);
  digitalWrite(STEPPER_PIN_6, HIGH);
  digitalWrite(STEPPER_PIN_7, LOW);
  digitalWrite(STEPPER_PIN_8, LOW);
  break;
  case 3:
  digitalWrite(STEPPER_PIN_1, HIGH);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);
  digitalWrite(STEPPER_PIN_5, HIGH);
  digitalWrite(STEPPER_PIN_6, LOW);
  digitalWrite(STEPPER_PIN_7, LOW);
  digitalWrite(STEPPER_PIN_8, LOW);
  
} 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}