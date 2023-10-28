const int pirSensorPin = 2; // Define the pin connected to the PIR sensor
int motionDetected = 0;    // Initialize a variable to store motion detection status

void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(9600);
  pinMode(pirSensorPin, INPUT);
  pinMode(9,OUTPUT); // Set the PIR sensor pin as an input
}

void loop() {
  // Read the PIR sensor input

  motionDetected = digitalRead(pirSensorPin);
   if(motionDetected==0){
    digitalWrite(9, HIGH); 
  }
  else{
     digitalWrite(9, LOW);
  }

  // Send the motion detection status (0 or 1) to the Serial monitor
  Serial.println(motionDetected);
  
  // Delay for a moment to avoid rapid serial output
}
