#include <Wire.h>

const byte MPU = 0x68;  // MPU6050 default I2C address

void setup() {
  Wire.begin();
  Serial.begin(9600);

  // Wake the sensor by clearing the sleep bit in register 0x6B
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  // Point to the first data register (0x3B = accel X high byte)
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

  // Each axis is 16 bits split across two bytes: shift the high byte left 8,
  // then OR in the low byte to combine them into one number
  int16_t ax = Wire.read() << 8 | Wire.read();
  int16_t ay = Wire.read() << 8 | Wire.read();
  int16_t az = Wire.read() << 8 | Wire.read();
  int16_t temp = Wire.read() << 8 | Wire.read();  // skipped, keeps the read order intact
  int16_t gx = Wire.read() << 8 | Wire.read();
  int16_t gy = Wire.read() << 8 | Wire.read();
  int16_t gz = Wire.read() << 8 | Wire.read();

  // At default sensitivity (+-2g), 16384 raw units = 1g
  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  Serial.print("X: "); Serial.print(ax_g);
  Serial.print(" | Y: "); Serial.print(ay_g);
  Serial.print(" | Z: "); Serial.println(az_g);

  delay(200);
}