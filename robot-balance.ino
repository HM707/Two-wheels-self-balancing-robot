#include <Wire.h>

// MPU6050 I2C address
#define MPU6050_ADDR 0x68

// L298N Motor Driver Pins
#define ENA 5  // Enable A (PWM)
#define IN1 3   // Input 1
#define IN2 9   // Input 2
#define IN3 10   // Input 3
#define IN4 11  // Input 4
#define ENB 6  // Enable B (PWM)

// PID Constants
float Kp = 40;	// Proportional gain
float Ki = 0.05;  // Integral gain
float Kd = 0.8;   // Derivative gain

// Variables for PID
float error = 0;
float lastError = 0;
float integral = 0;
float derivative = 0;
float output = 0;

// Target angle (upright position)
float targetAngle = 0;

// Timing variables
unsigned long currentTime, previousTime;
float elapsedTime;

// Complementary filter variables
float gyroAngle = 0;
float accelAngle = 0;
float currentAngle = 0;
float alpha = 0.96;  // Complementary filter constant

void setup() {
  Serial.begin(9600);
 
  // Initialize motor driver pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
 
  // Initialize I2C communication
  Wire.begin();
 
  // Initialize MPU6050
  initMPU6050();
 
  // Calibrate gyroscope
  Serial.println("Calibrating gyroscope...");
  delay(2000);
  calibrateGyro();
  Serial.println("Calibration complete!");
 
  previousTime = millis();
}

void loop() {
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000.0;
 
  // Read sensor data
  readMPU6050();
 
  // Calculate angle using complementary filter
  calculateAngle();
 
  // Calculate PID
  calculatePID();
 
  // Control motors
  controlMotors();
 
  // Debug output
  if (currentTime - previousTime >= 50) {  // Print every 50ms
	Serial.print("Angle: ");
	Serial.print(currentAngle);
	Serial.print(" | Output: ");
	Serial.println(output);
  }
 
  previousTime = currentTime;
  delay(10);  // Small delay for stability
}

void initMPU6050() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0); 	// Set to zero (wakes up the MPU6050)
  Wire.endTransmission(true);
 
  // Configure accelerometer (+/- 2g)
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x1C);  // ACCEL_CONFIG register
  Wire.write(0x00);  // Set accelerometer to +/- 2g
  Wire.endTransmission(true);
 
  // Configure gyroscope (+/- 250 degrees/sec)
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x1B);  // GYRO_CONFIG register
  Wire.write(0x00);  // Set gyroscope to +/- 250 degrees/sec
  Wire.endTransmission(true);
}

float gyroXOffset = 0;

void calibrateGyro() {
  float sum = 0;
  int samples = 1000;
 
  for (int i = 0; i < samples; i++) {
	Wire.beginTransmission(MPU6050_ADDR);
	Wire.write(0x43);  // Starting register for gyro readings
	Wire.endTransmission(false);
	Wire.requestFrom(MPU6050_ADDR, 6, true);
	
	int16_t gyroX = Wire.read() << 8 | Wire.read();
	sum += gyroX;
	delay(2);
  }
 
  gyroXOffset = sum / samples;
}

void readMPU6050() {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);  // Starting register for accelerometer readings
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR, 14, true);
 
  // Read accelerometer data
  int16_t accelX = Wire.read() << 8 | Wire.read();
  int16_t accelY = Wire.read() << 8 | Wire.read();
  int16_t accelZ = Wire.read() << 8 | Wire.read();
 
  // Skip temperature readings
  Wire.read(); Wire.read();
 
  // Read gyroscope data
  int16_t gyroX = Wire.read() << 8 | Wire.read();
  int16_t gyroY = Wire.read() << 8 | Wire.read();
  int16_t gyroZ = Wire.read() << 8 | Wire.read();
 
  // Convert to meaningful units
  float accelXg = accelX / 16384.0;
  float accelYg = accelY / 16384.0;
  float accelZg = accelZ / 16384.0;
 
  float gyroXrate = (gyroX - gyroXOffset) / 131.0;  // degrees/second
 
  // Calculate angle from accelerometer
  accelAngle = atan2(accelYg, accelZg) * 180 / PI;
 
  // Calculate angle from gyroscope
  gyroAngle += gyroXrate * elapsedTime;
}
void calculateAngle() {
  // Complementary filter
  currentAngle = alpha * (currentAngle + (gyroAngle - currentAngle)) + 
                 (1 - alpha) * accelAngle;
}

void calculatePID() {
  error = targetAngle - currentAngle;
  
  integral += error * elapsedTime;
  
  // Prevent integral windup
  if (integral > 400) integral = 400;
  else if (integral < -400) integral = -400;
  
  derivative = (error - lastError) / elapsedTime;
  
  output = Kp * error + Ki * integral + Kd * derivative;
  
  lastError = error;
  
  // Limit output
  if (output > 255) output = 255;
  else if (output < -255) output = -255;
}

void controlMotors() {
  // If robot is too tilted, stop motors to prevent damage
  if (abs(currentAngle) > 45) {
    stopMotors();
    return;
  }
  
  int motorSpeed = abs(output);
  
  if (output > 0) {
    // Move forward
    moveForward(motorSpeed);
  } else if (output < 0) {
    // Move backward
    moveBackward(motorSpeed);
  } else {
    // Stop
    stopMotors();
  }
}

void moveForward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveBackward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}