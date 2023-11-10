#include<Stepper.h>
// Motor pin definitions
#define motorPin1  2
#define motorPin2  3
#define motorPin3  4
#define motorPin4  5

#define motorPin5  A0
#define motorPin6  A1
#define motorPin7  A2
#define motorPin8  A3

// Number of steps per revolution for your stepper motors
#define STEPS_PER_REVOLUTION 2048

// Define the stepper motors without AccelStepper
Stepper stepper1(STEPS_PER_REVOLUTION, motorPin1, motorPin2, motorPin3, motorPin4);
Stepper stepper2(STEPS_PER_REVOLUTION, motorPin5, motorPin6, motorPin7, motorPin8);

int stahp = 7, stahp2 = 10;
int cw = 6, cw2 = 11;
int ccw = 8, ccw2 = 9;

boolean stopped = true;
boolean stopped2 = true;

void setup() {
    stepper1.setSpeed(8);
    stepper2.setSpeed(8);
    pinMode(stahp, INPUT);
    pinMode(cw, INPUT);
    pinMode(ccw, INPUT);
    pinMode(stahp2, INPUT);
    pinMode(cw2, INPUT);
    pinMode(ccw2, INPUT);
    Serial.begin(9600); // Initialize serial communication
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read(); // Read the command from the serial monitor
        handleCommand(command);
    }
}

void handleCommand(char command) {
    int steps = 2048; // Number of steps to move

    switch (command) {
        case 'R': // Rotate Right
            stopped = false;
            stepper1.step(steps);
            Serial.println("R command");
            break;
        case 'L': // Rotate Left
            stopped = false;
            stepper1.step(-steps);
            Serial.println("L command");
            break;
        case 'P': // Pitch
            stopped2 = false;
            stepper2.step(steps);
            Serial.println("P command");
            break;
        case 'N': // Pitch Negative
            stopped2 = false;
            stepper2.step(-steps);
            break;
        case 'S': // Stop
            stopped = true;
            stopped2 = true;
            Serial.println("S command");
            break;
        default:
            // Invalid command, do nothing
            break;
    }
}
