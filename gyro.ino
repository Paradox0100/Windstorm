#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// bug chatching arrays

const int bufferSize = 5;
float roll_bug[bufferSize];
float pitch_bug[bufferSize];
int currentIndex = 0;
bool repeating = false;

float roll = 0.0;
float pitch = 0.0;
float yaw = 0.0;
int dt = 250;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize MPU6050
  mpu.initialize();
  
  // Check if MPU6050 is connected
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully!");
  } else {
    Serial.println("MPU6050 connection failed. Check wiring!");
  }
}

void loop() {
  // Read sensor data and print to serial monitor

  gyro();
  delay(dt);
}
void gyro() {
  // raw data
  int16_t accelerometerX = mpu.getAccelerationX();
  int16_t accelerometerY = mpu.getAccelerationY();
  int16_t accelerometerZ = mpu.getAccelerationZ();

  // calculate for g-force values
  float accelX = accelerometerX / 16384.0;
  float accelY = accelerometerY / 16384.0;
  float accelZ = accelerometerZ / 16384.0;

  // calculate for roll pich and yaw
  roll = atan2(accelY, accelZ) * 180.0 / PI;
  pitch = atan2(-accelX, sqrt(accelY * accelY + accelZ * accelZ)) * 180.0 / PI;
  // Read gyroscope data
  int16_t gyroZ = mpu.getRotationZ();

  // Calculate yaw angle
  yaw += (gyroZ / 131.0) * (dt / 1000.0); // Convert dt to seconds

  // Normalize yaw angle to the range of 0-360 degrees
  if (yaw < 0) {
    yaw += 360.0;
  } else if (yaw >= 360.0) {
    yaw -= 360.0;
  }
  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print(" Pitch: ");
  Serial.print(pitch);
  Serial.print(" Yaw: ");
  Serial.println(yaw);
  addToCircularBuffer(roll, pitch);
  mpu_restart();
  delay(dt);
}
void addToCircularBuffer(float roll, float pitch) {
  roll_bug[currentIndex] = roll;
  pitch_bug[currentIndex] = pitch;
  currentIndex = (currentIndex + 1) % bufferSize;
}
bool check_buffer() {
  for (int i = 1; i < 5; i++) {
    if ((roll_bug[i] != roll_bug[0]) && (pitch_bug[i] != pitch_bug[0])) {
      return(false);
    }
  }
  return(true);
}
void mpu_restart() {
  // checks if a restart is required
  if (check_buffer()) {
    Serial.println("restarting gyroscope...");
    delay(200);
    mpu.initialize();
    if (mpu.testConnection()) {
      Serial.println("MPU6050 connected successfully!");
    } else {
      Serial.println("MPU6050 connection failed. Check wiring!");
      delay(200);
    }
  }
}


