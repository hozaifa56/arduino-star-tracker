#include <Stepper.h>
#include <Wire.h>

const int stepsPerRevolution = 2048;

#define motorPin1  2
#define motorPin2  3
#define motorPin3  4
#define motorPin4  5

#define motorPin5  A0
#define motorPin6  A1
#define motorPin7  A2
#define motorPin8  A3

const int stop = 6, stop2 = 7;

Stepper rollStepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);
Stepper yawStepper(stepsPerRevolution, motorPin5, motorPin6, motorPin7, motorPin8);

boolean stopped = true;
boolean stopped2 = true;

void setup() {
  Serial.begin(9600);
  rollStepper.setSpeed(6);
  yawStepper.setSpeed(6);
  pinMode(stop, INPUT);
  pinMode(stop2, INPUT);
}

void loop() {
  motor_roll();
  motor_yaw();
}

void motor_roll() {
  if (digitalRead(stop) == LOW) {
    stopped = true;
  } else {
    rollStepper.step(stepsPerRevolution);
    stopped=false;
  }
}

void motor_yaw() {
  if (digitalRead(stop2) == LOW) {
    stopped2 = true;
  } else {
    yawStepper.step(stepsPerRevolution);    
    stopped2 = false;
  }
}