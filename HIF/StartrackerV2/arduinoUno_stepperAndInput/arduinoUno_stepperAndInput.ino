#include <Stepper.h>

// Define the number of steps per revolution and the pins connected to the stepper motor
const int stepsPerRevolution = 200;
int yawraw;
int pitchraw;
const int vectorYaw; //enter the value of how many steps needed to move 1degree.... store it like =XX;
const int vectorPitch; //same stuff here 
int yawF;
int pitchF;
Stepper PitchStepper(stepsPerRevolution, 8, 9, 10, 11);  // Assuming stepper motor is connected to pins 8, 9, 10, and 11
Stepper yawStepper(stepsPerRevolution, 4, 5, 6, 7);
void setup() {
  Serial.begin(9600);  // Initialize serial communication
  // Set the speed of the stepper motor
  myStepper1.setSpeed(10);  // Set speed to 10 steps per second
  myStepper2.setSpeed(10);
}

void loop() {

    readSerialInput();
    yawF=vectoryaw*yawraw;
    pitchF=vectorPitch*pitchraw;

    // Move the stepper motor to the desired number of steps
    yawStepper.step(yawF);
    pitchStepper.step(pitchF);
    // Optional: You might want to add a delay or perform other actions after the motor has moved
    delay(1000);  // Adjust delay as needed
  }
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