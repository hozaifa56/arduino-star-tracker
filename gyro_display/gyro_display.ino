#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

MPU6050 mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Initialize MPU6050 sensor
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // Calibrate gyro
  mpu.calibrateGyro();
}

void loop() {
  // Read accelerometer and gyroscope data
  Vector rawAccel = mpu.readRawAccel();
  Vector rawGyro = mpu.readNormalizeGyro();

  // Calculate pitch
  float pitch = atan2(-rawAccel.YAxis, sqrt(rawAccel.XAxis * rawAccel.XAxis + rawAccel.ZAxis * rawAccel.ZAxis)) * 180 / PI;

  // Calculate yaw
  float yaw = atan2(rawAccel.XAxis, sqrt(rawAccel.YAxis * rawAccel.YAxis + rawAccel.ZAxis * rawAccel.ZAxis)) * 180 / PI;

  // Clear previous values on the display
  display.clearDisplay();

  // Print yaw and pitch values on the display
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Yaw: ");
  display.print(yaw);
  display.println(" degrees");

  display.setCursor(0, 10);
  display.print("Pitch: ");
  display.print(pitch);
  display.println(" degrees");

  // Display the updated information
  display.display();

  // Print yaw and pitch values on serial monitor
  Serial.print("Yaw: ");
  Serial.print(yaw);
  Serial.print(" degrees, Pitch: ");
  Serial.print(pitch);
  Serial.println(" degrees");

  delay(100); // Adjust delay as needed
}
