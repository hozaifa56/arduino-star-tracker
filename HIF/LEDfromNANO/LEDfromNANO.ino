const int ledPin = 12; // Change this to the pin connected to your LED


void setup() {
  pinMode(stopPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int stopValue = digitalRead(stopPin);

  if (stopValue == LOW) { // Assuming LOW means stop is activated
    digitalWrite(ledPin, LOW); 
    Serial.println("LED OFF");
  } else {
    digitalWrite(ledPin, HIGH); 
    Serial.println("LED ON");
  }

  delay(1000);
}
