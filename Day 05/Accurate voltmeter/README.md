# Day 5: Accurate voltmeter

An Arduino voltmeter that reads up to about 12 V, using a voltage divider and 64-sample averaging.

## What it does
Reads a voltage through a divider into A0, averages 64 readings, converts it to volts, and
prints it with 2 decimals every 500 ms.

## Wiring
Source **positive (+)** (A 9V battery for example) -> 10 kΩ -> A0 -> 5.1 kΩ -> GND. Source **−** to Arduino GND (common ground).

<img width="1017" height="520" alt="Screenshot 2026-11-08 211150" src="https://github.com/user-attachments/assets/55ec085f-434e-44ea-8636-65fc2ef80212" />
Divider ratio: `Vin = Vout × (10 + 5.1) / 5.1` (about × 2.96). Safe up to about 14.8 V at the input;
I only test at 12 V or less.

## How it works
- The Arduino can only read up to 5 V, so the divider shrinks the voltage by a known ratio and the
  code multiplies it back (like drawing a triangle at 1/5 scale and multiplying the result by 5).
- Each reading has random noise. Averaging 64 readings cancels most of it (about 8× smaller).
- `sum` is `unsigned long`: 64 × 1023 = 65,472 is bigger than an `int` can hold (32,767).
- `float` maths with `5.0` and `1023.0` (not `5` and `1023`), because integer division drops the decimals.

## Results
| Source | Arduino reading |
| --- | --- |
| Arduino 5 V pin | 5.02 V |
|9V battery | 9.0 V |
| ESP32 3V3 pin | 3.23 V |

**Calibration: PENDING.** My multimeter's battery died, so I can't compare against a reference yet.
Status: half done. I'll add the calibration factor when I have a meter.

## What broke (and what I learned)
- First reading was 0.7 V instead of 5 V: I had used a **100 kΩ** resistor instead of 10 kΩ
  (brown-black-yellow vs brown-black-orange).
- `sum` was never reset each loop, so the average kept growing.
- `sum / 64` is integer division and drops decimals; use `sum / 64.0`.
- The Arduino's 3.3 V pin read only about 34 counts instead of about 675. That pin seems faulty,
  so I used the ESP32's 3V3 pin instead (with a shared ground).

## Files
- `Day_5.ino`
