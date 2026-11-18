
# Day 7: Thermistor Temperature Sensor

An Arduino project that reads temperature using a thermistor and a fixed resistor, turning raw analog voltage into an accurate Celsius readout using the Beta equation.

## What it does

Reads a voltage divider into A0, averages 64 rapid readings to eliminate noise, calculates the thermistor's current resistance, runs it through the Beta equation to find absolute temperature in Kelvin, converts it to Celsius, and prints it every 500 ms using `millis()`.

## Wiring

**5V** -> 10 kΩ Resistor -> **A0** -> 10 kΩ Thermistor -> **GND**.

## How it works

* **The Seesaw Analogy (`1023.0 - raw`):** The Arduino reads voltage from 0 to 1023. Because the fixed resistor and thermistor share the 5V line, whatever voltage the thermistor takes (`raw`), the *remaining* voltage left over on the fixed resistor side must be `1023.0 - raw`. Comparing these two shares lets us calculate the thermistor's true resistance.
* **Noise Reduction:** Taking 64 readings in a loop and dividing by 64 (`sum / 64.0`) smooths out erratic electrical noise so the temperature doesn't jump around wildly.
* **The Beta Equation:** Thermistors don't change resistance in a straight line; they follow a steep curve. The Beta equation uses logarithms and a factory coefficient (`BETA = 3950.0`) to straighten out that curve and find the temperature in Kelvin.
* **Celsius Conversion:** Subtracting `273.15` from Kelvin converts it into Celsius (since 0 Kelvin is absolute zero, which equals -273.15 °C).

## Results

| Test Condition | Arduino Reading |
| --- | --- |
| Room temperature (desk) | 28.7 °C |
| Body temperature (holding with fingers) | 36.4 °C |

## What broke (and what I learned)

* **The Absolute Zero Trap:** Early on, the code spat out `-273.1 °C` because a typo or bad calculation caused the denominator to hit zero, triggering a division by zero crash that plunged the math straight into absolute zero. Using `1023.0 - raw` with a floating-point number fixed it.
* **Variable Mix up:** Accidentally typed `1 / T` instead of `1 / T0` inside the Beta equation formula, which broke the baseline reference point (`T0 = 298.15` for 25 °C).
* **Logarithmic Reality:** Learned that you can't just use simple multiplication for a thermistor because its resistance changes exponentially, which is why the natural logarithm (`log()`) is required to make sense of the curve.

## Files

* `day_7.ino`
