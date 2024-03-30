
#include <virtuabotixRTC.h>
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;
//define RTC.
virtuabotixRTC myRTC(A0, A1, A2);
double M,Y,D,MN,H,S;
double A,B;
double location =80.94;//your longtitude.
double location2 =26.84;//your latitude.
double LST_degrees;//variable to store local side real time(LST) in degrees.
double LST_hours;//variable to store local side real time(LST) in decimal hours.
unsigned long timer = 0;
float timeStep = 0.01;
// Pitch and Yaw values
double pitch = 0;
double yaw = 0;
double val = 0;//variable to store the user input DEC
double val2 = 0;//variable to store the user input RA
double temp = val2;//temporary value to store val2
const int stahp=6,stahp2=9;
const int cw=7,cw2=10;
const int ccw=8,ccw2=11;
bool receivedCoordinates = false; // Flag to track if coordinates are received
void setup() {
    //set date-time according to (seconds, minutes, hours, day of the week, day of the month, month, year) 
    myRTC.setDS1302Time(00, 45, 10, 2, 11, 11, 2023);
    Wire.begin();
    Serial.begin(9600);
    pinMode(stahp,OUTPUT);
    pinMode(cw,OUTPUT);
    pinMode(ccw,OUTPUT);
    pinMode(stahp2,OUTPUT);
    pinMode(cw2,OUTPUT);
    pinMode(ccw2,OUTPUT);
    delay(5000);//wait before starting
    while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
    {
    }
    mpu.calibrateGyro();
    mpu.setThreshold(3);
}//--(end setup )---
void loop()
{
    //this will update the RA degrees with sidereal time 1degree at a time
    //this way the object or star on the sky is tracked.
  if(location2>0){//for the northern hemisphere. 
    if( floor(LST_degrees)==LST_degrees ){ 
      if (LST_degrees>180){
        val2 = temp+(360-LST_degrees);
        }else{
        val2 = temp-LST_degrees; //use val2 = temp+LST_degrees; if you are located in the southern hemisphere.
        }
    }
  }else{//for the southern hemisphere.
   if( floor(LST_degrees)==LST_degrees ){ 
      if (LST_degrees>180){
        val2 = temp-(360-LST_degrees);
        }else{
        val2 = temp+LST_degrees; //use val2 = temp+LST_degrees; if you are located in the southern hemisphere.
        }
    }
  }
    myRTC.updateTime();
    LST_time();
    if (!receivedCoordinates) {
        recvdata(); // Receive coordinates only once
        receivedCoordinates = true; // Set the flag to true after receiving coordinates
    }
    pitch_check();
    yaw_check();
    timer = millis();
    Vector norm = mpu.readNormalizeGyro();
    //I've put the sensor with a 90 degree angle on the setup due to
    //cable connection problems. Because of that the data values from the mpu6050 chip are
    //different in this case:
    //roll data(X-axis) is pitch.
    //pitch data(Y-axis) is yaw.
    yaw = yaw + norm.YAxis * timeStep;
    pitch = pitch + norm.XAxis * timeStep;
    Serial.print(" Yaw = ");
    Serial.print(yaw);
    Serial.print(" Pitch = ");
    Serial.print(pitch);
    Serial.print(" LST_d = ");
    Serial.print(LST_degrees);
    Serial.print(" LST_h = ");
    Serial.println(LST_hours);//local sidereal time in decimal hours.
    delay((timeStep*1000) - (millis() - timer));//timer for the gyro.
}


void recvdata(){

    Serial.println("Enter the coordinates:");
    while (!Serial.available()) {
      // Wait for input
    }
    String a= Serial.readString();
        String value1, value2;
        // For loop which will separate the String in parts
        // and assign them the the variables we declare
        for (int i = 0; i < a.length(); i++) {
            if (a.substring(i, i+1) == ",") {
                value2 = a.substring(0, i);
                value1= a.substring(i+1);
                break;
            }
        }
        Serial.println(val);
        Serial.println(val2);
        val=90-value1.toFloat();
        val2=value2.toFloat();
        temp = val2;
        Serial.println("the coordinates:");
        Serial.println(val);
        Serial.println(temp);
}
void pitch_check(){
    //check if pitch is high, low or equal to the user input
    //send commands to slave-module to start and stop motors
    Serial.println("i am in pitch_check function");
    if(floor(pitch*100)/100==floor(val*100)/100){
        digitalWrite(stahp,HIGH);
        }else{
        digitalWrite(stahp,LOW);
    }
    if(floor(pitch*100)<floor(val*100)){
        digitalWrite(cw,HIGH); 
        }else{
        digitalWrite(cw,LOW);
    }
    if(floor(pitch*100)>floor(val*100)){
        digitalWrite(ccw,HIGH);
        }else{
        digitalWrite(ccw,LOW);
    }
}
void yaw_check(){
    //check if yaw is high, low or equal to the user input
    //send commands to slave-module to start and stop motors
    Serial.println("i am in yaw_check function");
    if(floor(yaw*100)==floor(val2*100)){
        digitalWrite(stahp2,HIGH);
        }else{
        digitalWrite(stahp2,LOW);
    }
    if(floor(yaw*100)<floor(val2*100)){
        digitalWrite(cw2,HIGH);
        }else{
        digitalWrite(cw2,LOW);
    }
    if(floor(yaw*100)>floor(val2*100)){
        digitalWrite(ccw2,HIGH);
        }else{
        digitalWrite(ccw2,LOW);
    }
}
void LST_time(){
    //Calculates local sidereal time based on this calculation,
    //http://www.stargazing.net/kepler/altaz.html 
    M = (double) myRTC.month;
    Y = (double) myRTC.year;
    D = (double) myRTC.dayofmonth;
    MN = (double) myRTC.minutes;
    H = (double) myRTC.hours;
    S = (double) myRTC.seconds;
    A = (double)(Y-2000)*365.242199;
    B = (double)(M-1)*30.4368499;
    double JDN2000=A+B+(D-1)+myRTC.hours/24;
    double decimal_time = H+(MN/60)+(S/3600) ;
    double LST = 100.46 + 0.985647 * JDN2000 + location + 15*decimal_time;
    LST_degrees = (LST-(floor(LST/360)*360));
    LST_hours = LST_degrees/15;
}