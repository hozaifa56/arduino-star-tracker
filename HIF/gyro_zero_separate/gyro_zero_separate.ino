#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

MPU6050 mpu;
int pitchOffset = 0;
int yawOffset = 0;
bool calibrated = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Initialize MPU6050");
  
  while (!mpu.begin(MPU6050_SCALE_250DPS, MPU6050_RANGE_16G)) {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(2000);
  }
  
  // Calibration process
  Serial.println("Calibrating...");
  calibrateGyro();
  Serial.println("Calibration complete.");
}

void calibrateGyro() {
  const int numReadings = 100; // Number of readings for calibration
  int pitchTotal = 0;
  int yawTotal = 0;

  for (int i = 0; i < numReadings; ++i) {
    Vector normAccel = mpu.readNormalizeAccel();

    // Calculate pitch and yaw angles in radians
    float pitch = atan(normAccel.XAxis/sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis));
    float yaw = atan(normAccel.YAxis/sqrt(normAccel.XAxis * normAccel.XAxis + normAccel.ZAxis * normAccel.ZAxis));

    // Convert radians to degrees
    pitch = pitch * (1/(3.142/180));
    yaw = yaw * (1/(3.142/180));

    pitchTotal += pitch;
    yawTotal += yaw;
    delay(10); // Delay between readings
  }

  // Calculate averages
  pitchOffset = pitchTotal / numReadings;
  yawOffset = yawTotal / numReadings;
  calibrated = true;
}

void loop() {
  if (calibrated) {
    Vector normAccel = mpu.readNormalizeAccel();

    // Calculate pitch and yaw angles in radians
    float pitch = atan(normAccel.XAxis/sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis));
    float yaw = atan(normAccel.YAxis/sqrt(normAccel.XAxis * normAccel.XAxis + normAccel.ZAxis * normAccel.ZAxis));

    // Convert radians to degrees and subtract offsets, then cast to integer
    pitch = (pitch * (1/(3.142/180))) - pitchOffset;
    yaw = (yaw * (1/(3.142/180))) - yawOffset;

    int intPitch = static_cast<int>(pitch);
    int intYaw = static_cast<int>(yaw);

    Serial.print("Calibrated Pitch: ");
    Serial.print(intPitch);
    Serial.print(" degrees, Calibrated Yaw: ");
    Serial.print(intYaw);
    Serial.println(" degrees");
  }

  delay(500);
}
//yaw value -79 to 87
//pitch value -85 to 80 