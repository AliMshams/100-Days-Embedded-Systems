# Day 8 · Ultrasonic rangefinder with temperature correction

An Arduino project using the HC-SR04 ultrasonic sensor to measure distance, combining it with the Day 7 thermistor to dynamically correct for the speed of sound based on air temperature, backed by a median filter to eliminate erratic noise spikes.

## What it does

Sends an ultrasonic pulse via the HC-SR04, measures how long the echo takes to return using `pulseIn()`, reads the ambient temperature from the thermistor to calculate the exact real-time speed of sound, filters out outlier noise using a 5-reading median sort, and calculates the precise distance.

## Wiring

* **HC-SR04 Ultrasonic Sensor:**
* `VCC` → 5V
* `GND` → GND
* `TRIG` → Pin 9
* `ECHO` → Pin 10


* **Thermistor Circuit (from Day 7):** Keep it connected (`5V` → 10 kΩ resistor → `A0` → thermistor → `GND`).

## How it works

* **The Canyon Echo:** Just like shouting into a canyon and timing the echo, the sensor emits an ultrasonic burst, waits for it to bounce back, and counts the microseconds. Distance is calculated as `(duration × speed_of_sound) / 2` (since the sound has to travel there and back).
* **Temperature Correction:** Sound doesn't travel at a fixed speed—it moves faster in warm air and slower in cold air ($speed \approx 331.3 + 0.606 \times T$). Feeding our real-time Celsius reading from the thermistor into this formula adjusts the math so our distance calculations stay accurate regardless of room temperature.
* **Median Filter:** Instead of taking a simple average, the code takes 5 rapid distance readings, sorts them in order, and grabs the middle value. This completely bypasses occasional glitchy spikes (like a stray echo or a missed pulse).

## What broke (and what I learned)

* **Median vs. Average for Noise:** Learned firsthand why medians are better for dealing with sensor glitches. If you get a set of readings like `10, 11, 10, 12, 30`, a standard average gets heavily dragged up by that random 30. A median filter ignores the outlier entirely and locks onto the true value.
* **The Speed of Sound Changes:** Discovered that the speed of sound isn't a static universal constant in practical electronics—air temperature alters it enough to throw off high-precision distance measurements, making the integration with our Day 7 thermistor a crucial upgrade.

## Files

* `day_8.ino`
