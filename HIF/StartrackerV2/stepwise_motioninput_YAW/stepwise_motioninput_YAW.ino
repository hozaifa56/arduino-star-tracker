#include <Stepper.h>

// Define the number of steps per revolution and the pins connected to the stepper motor
const int stepsPerRevolution = 1000;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);  // Assuming stepper motor is connected to pins 8, 9, 10, and 11

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  // Set the speed of the stepper motor
  myStepper.setSpeed(10);  // Set speed to 10 steps per second
}

void loop() {
  // Check if there's data available to read from the serial port
  if (Serial.available() > 0) {
    // Read the number of steps from the serial input
    int desiredSteps = Serial.parseInt();

    // Move the stepper motor to the desired number of steps
    myStepper.step(desiredSteps);

    // Optional: You might want to add a delay or perform other actions after the motor has moved
    delay(1000);  // Adjust delay as needed
  }
}
