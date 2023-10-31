#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(6, 7, 8);

void setup() {
  // Initialize the serial communication for debugging
  Serial.begin(9600);

  // Set the initial time and date
  myRTC.setDS1302Time(00,02, 12,2, 31, 1,2023); // (minutes, hours, day of the month, month, day of the week, year)
}

void loop() {
  // Update the RTC's time and date
  myRTC.updateTime();

  // Print the current date and time
  Serial.print("Current date/time: ");
  Serial.print(myRTC.dayofmonth); // Use correct variable name
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.print(myRTC.seconds);
  Serial.println(); // Print a newline for readability

  delay(1000); // Delay for 1 second
}
