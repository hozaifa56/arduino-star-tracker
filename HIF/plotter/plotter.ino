#define echoPin 2
#define trigPin 3
const float Speed=0.0343;
long duration, distance;
void setup() {

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin,LOW);
  delay(200);

  digitalWrite(trigPin, HIGH);
  delay(200);

  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin,HIGH);

  distance=Speed*duration/2;
  Serial.println(distance);


}
