const int trigPin = 3;    // Define the pins that you will work with
const int echoPin = 2;
const int LEDR = 12;
const float Speed = 0.0343;  // Sound speed at cm/us
long duration, distance;

void setup()
{
   pinMode(trigPin, OUTPUT);  // Define digital pin 3 as an output
   pinMode(echoPin, INPUT);   // Define digital pin 2 as an input
   pinMode(LEDR, OUTPUT);     // Define digital pin 12 as an output

   // Initialize the serial communication at a baud rate of 9600
   Serial.begin(9600);
}

void loop()
{
   digitalWrite(trigPin, LOW);        // Make sure that the TRIG is deactivated
   delayMicroseconds(2);
   
   digitalWrite(trigPin, HIGH);       // Activate the output pulse
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);        // Stop the pulse and wait for ECHO

   duration = pulseIn(echoPin, HIGH);  // Measure the time since the echoPin went HIGH

   // Calculate the distance based on the time and speed of sound
   distance = Speed * duration / 2;

   // Print the distance to the Serial Monitor
   Serial.print("Distance: ");
   Serial.print(distance);
   Serial.println(" cm");

  -

   // Add a delay to control the update rate (e.g., every 1 second)
   delay(500);
}
