#include <Stepper.h>
#include <Wire.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  2     // IN1 on the ULN2003 driver 1
#define motorPin2  3     // IN2 on the ULN2003 driver 1
#define motorPin3  4     // IN3 on the ULN2003 driver 1
#define motorPin4  5     // IN4 on the ULN2003 driver 1

#define motorPin5  A0     // IN1 on the ULN2003 driver 1
#define motorPin6  A1     // IN2 on the ULN2003 driver 1
#define motorPin7  A2     // IN3 on the ULN2003 driver 1
#define motorPin8  A3     // IN4 on the ULN2003 driver 1

const int stepsPerRevolution = 2048; // Change this according to your motor
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
Stepper stepper1(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);
Stepper stepper2(stepsPerRevolution, motorPin5, motorPin6, motorPin7, motorPin8);

int stahp = 6,stahp2=9;
int cw = 7,cw2 = 10;
int ccw = 8,ccw2=11;

boolean stopped = false;
boolean stopped2 = false;
void setup() {
    Serial.begin(9600);
    stepper1.setSpeed(6);
    stepper2.setSpeed(6);
    pinMode(stahp2,INPUT);
    pinMode(cw2,INPUT);
    pinMode(ccw2,INPUT);
    pinMode(stahp,INPUT);
    pinMode(cw,INPUT);
    pinMode(ccw,INPUT);

}//--(end setup )---
void loop()
{
    motor_pitch();
    motor_roll();
    Serial.println(stahp);
    Serial.println(digitalRead(cw));
    Serial.println(digitalRead(ccw));
    
    if(stopped==false){
        stepper1.step(stepsPerRevolution);
    }
    if(stopped2==false){
        stepper2.step(stepsPerRevolution);
    }
}
void motor_roll(){
    if(digitalRead(stahp)==HIGH){
        stopped = true;
    }else{ if(digitalRead(cw)==HIGH){
            stepper1.setSpeed(6);
            stopped = false;
        }
        if(digitalRead(ccw)==HIGH){
            stepper1.setSpeed(-6);
            stopped = false;
        }
    }
}
void motor_pitch(){
    if(digitalRead(stahp2)==HIGH){
        stopped2 = true;
    }else{ if(digitalRead(cw2)==HIGH){
            stepper2.setSpeed(6);
            stopped2 = false;
        }
        if(digitalRead(ccw2)==HIGH){
            stepper2.setSpeed(-6);
            stopped2 = false;
        }
    }
   
}