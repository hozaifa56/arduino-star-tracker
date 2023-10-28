int potentiometerPIN = 2;      
// It select the input pin connected to the middle terminal of the potentiometer  
int LEDpin = 13;   // It selects the LED pin  
int value = 0;       // value initialized to store the coming value from the sensor  
void setup()   
{  
  pinMode(LEDpin, OUTPUT);  // The LED pin is declared as the output pin  
  Serial.begin(9600);
}  
void loop()   
{  
  value = analogRead(potentiometerPIN);    // It reads the value from the sensor  
  digitalWrite(LEDpin, HIGH);  // turn the LEDpin ON  
  delay(value);                  // delay time in milliseconds  
  digitalWrite(LEDpin, LOW);   // turn the LEDpin OFF  
  delay(value);    
  Serial.println(value);               
  // the delay time depends on the value stored from the sensor  
}  