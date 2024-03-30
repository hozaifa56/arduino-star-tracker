int val = 0;//variable to store the user input DEC
int val2 = 0;//variable to store the user input RA

bool receivedCoordinates = false; // Flag to track if coordinates are received
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
    if (!receivedCoordinates) {
        recvdata(); // Receive coordinates only once
        receivedCoordinates = true; // Set the flag to true after receiving coordinates
    }

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