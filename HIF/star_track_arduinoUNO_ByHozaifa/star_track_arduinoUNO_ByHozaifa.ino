#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
// Timers
unsigned long timer = 0;
float timeStep = 0.01;


// Pitch, Roll and Yaw values

float rollRaw = 0;
float yawRaw = 0;
int roll;
int yaw;
//pin definition
const int stop=6,stop2=7;

int val = 0;//variable to store the user input DEC
int val2 = 0;//variable to store the user input RA
bool receivedCoordinates = false; // Flag to track if coordinates are received
void setup() {

  Serial.begin(9600);
  Wire.begin();
    pinMode(stop,OUTPUT);
    pinMode(stop2,OUTPUT);
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
    // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();
}

void loop() {
  if(!receivedCoordinates) {
    recvdata(); // Receive coordinates only once
    receivedCoordinates = true; // Set the flag to true after receiving coordinates
  }
  altitude_check();
  azimuth_check();
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw

  rollRaw = rollRaw + norm.XAxis * timeStep;
  yawRaw = yawRaw + norm.ZAxis * timeStep;

  roll = rollRaw * (1/(3.142/180));
  yaw = yawRaw * (1/(3.142/180));
  // Output raw

  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  // Wait to full timeStep period
  delay(500);
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
        val=value1.toInt();
        val2=value2.toInt();
     
        Serial.println("the coordinates:");
        Serial.println(val);
        Serial.println(val2);  

}
void altitude_check(){
    Serial.println("i am in altitude_check function");
    if(val2==roll){
      digitalWrite(stop2,LOW);
      Serial.println(digitalRead(stop2));
    }
    else{
      digitalWrite(stop2,HIGH);
      Serial.println(digitalRead(stop2));
    }

}
void azimuth_check(){
    Serial.println("i am in azimuth_check function");
    if(val==yaw){
      digitalWrite(stop,LOW);
      Serial.println(digitalRead(stop));
    }
    else{
      digitalWrite(stop,HIGH);
      Serial.println(digitalRead(stop));
    }
    
}
