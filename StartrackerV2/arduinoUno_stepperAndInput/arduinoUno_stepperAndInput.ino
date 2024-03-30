#include <Stepper.h>
#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MPU6050 mpu;

// Define the number of steps per revolution and the pins connected to the stepper motor
const int stepsPerRevolution = 200;
int yawraw;
int pitchraw;
const int vectorYaw; //enter the value of how many steps needed to move 1degree.... store it like =XX;
const int vectorPitch=20; //same stuff here 
int yawF;
int pitchF;
Stepper PitchStepper(stepsPerRevolution, 8, 9, 10, 11);  // Assuming stepper motor is connected to pins 8, 9, 10, and 11
Stepper yawStepper(stepsPerRevolution, 4, 5, 6, 7);
void setup() {
  Serial.begin(9600);  // Initialize serial communication
    Wire.begin();

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Initialize MPU6050 sensor
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // Calibrate gyro
  mpu.calibrateGyro();
  // Set the speed of the stepper motor
  myStepper1.setSpeed(10);  // Set speed to 10 steps per second
  myStepper2.setSpeed(10);
}

void loop() {
    gyrodisplay();
    readSerialInput();
    yawF=vectoryaw*yawraw;
    pitchF=vectorPitch*pitchraw;

    // Move the stepper motor to the desired number of steps
    yawStepper.step(yawF);
    pitchStepper.step(pitchF);
    // Optional: You might want to add a delay or perform other actions after the motor has moved
    delay(1000);  // Adjust delay as needed

}
void readSerialInput() {
  Serial.println("Hi, welcome to the Arduino Based star and planet tracker. Please enter the coordinates in form x,y in the serial input.")
  // Check if data is available to read from serial port
  if (Serial.available() > 0) {
    // Read the incoming data until newline character is received
    String data = Serial.readStringUntil('\n');
    
    // Find the position of the comma
    int commaPosition = data.indexOf(',');
    
    // Check if comma exists in the received data
    if (commaPosition != -1) {
      // Extract x and y values from the received data
      String x_str = data.substring(0, commaPosition);
      String y_str = data.substring(commaPosition + 1);
      
      // Convert the string values to integers
      yawraw = x_str.toInt();
      pitchraw = y_str.toInt();
      
      // Print the received values for testing
      Serial.print(" Given Yaw: ");
      Serial.println(yawraw);
      Serial.print(" Given Pitch: ");
      Serial.println(pitchraw);
    }
  }
}
void gyrodisplay(){
  // Read accelerometer and gyroscope data
  Vector rawAccel = mpu.readRawAccel();
  Vector rawGyro = mpu.readNormalizeGyro();

  // Calculate pitch
  float pitch = atan2(-rawAccel.YAxis, sqrt(rawAccel.XAxis * rawAccel.XAxis + rawAccel.ZAxis * rawAccel.ZAxis)) * 180 / PI;

  // Calculate yaw
  float yaw = atan2(rawAccel.XAxis, sqrt(rawAccel.YAxis * rawAccel.YAxis + rawAccel.ZAxis * rawAccel.ZAxis)) * 180 / PI;

  // Clear previous values on the display
  display.clearDisplay();

  // Print yaw and pitch values on the display
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Yaw: ");
  display.print(yaw);
  display.println(" degrees");

  display.setCursor(0, 10);
  display.print("Pitch: ");
  display.print(pitch);
  display.println(" degrees");

  // Display the updated information
  display.display();

  // Print yaw and pitch values on serial monitor
  Serial.print("Yaw: ");
  Serial.print(yaw);
  Serial.print(" degrees, Pitch: ");
  Serial.print(pitch);
  Serial.println(" degrees");

  delay(100);
}