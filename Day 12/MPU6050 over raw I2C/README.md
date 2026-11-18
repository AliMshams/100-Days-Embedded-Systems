# Day 12 - MPU6050 over Raw I2C

## What it does
Reads acceleration data from an MPU6050 sensor using only Wire.h,
no external library. Prints X, Y, Z acceleration in g-force to Serial Monitor.
Lying flat, Z should read about +1.0 g. Flip it over and it reads about -1.0 g.

## How it works
Every I2C sensor has a register map — a numbered table of memory slots.
You write to some to configure the sensor, and read from others to get data.

For the MPU6050:
- Register 0x6B controls sleep mode — writing 0 wakes it up
- Register 0x3B is where acceleration data starts
- Reading 14 bytes from there gives you accel X, Y, Z, temperature, and gyro X, Y, Z in order

Each value is 16 bits but arrives as two separate 8-bit bytes.
To reassemble them into one number, the high byte gets shifted left 8 positions
to make room, then the low byte is OR-ed in to fill the right side:

    int16_t ax = Wire.read() << 8 | Wire.read();

At the default sensitivity setting, the sensor outputs 16384 raw units per g,
so dividing by 16384.0 converts the raw number into actual g-force.

## What I learned
- How to read a sensor's register map and talk to it without a library
- High byte and low byte , how a 16-bit value is split across two bytes
  and how to reassemble it with bit shifting and OR
- I2C transaction flow: beginTransmission, write the register address,
  endTransmission(false) to keep the connection, then requestFrom to pull the data
- How raw ADC values map to physical units (16384 = 1g at +-2g range)

## Wiring
 VCC - 3.3V (or 5V if your module has an onboard regulator like mine)
 GND - GND
 SCL - A5
 SDA - A4

## Files
Day_12.ino
