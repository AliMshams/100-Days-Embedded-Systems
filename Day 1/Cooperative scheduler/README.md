# Day 1: Cooperative scheduler with `millis()`

Four jobs running at the same time on an Arduino Uno, with no `delay()` anywhere.

## What it does
| Job | Runs every | What it does |
| --- | --- | --- |
| A | 500 ms | Blinks an LED |
| B | 20 ms | Reads a button and counts each press once |
| C | 2000 ms | Prints `Alive, counter : N` to the Serial Monitor |
| D | 5000 ms | Prints `Tick` (my own addition) |

## Wiring
- LED + 220 Ω resistor on pin 8 (long leg towards the resistor, short leg to GND)
- Button between pin 2 and GND, using `INPUT_PULLUP` (pressed = `LOW`)

**FILL IN: add a photo of your wiring here:** `![wiring](wiring.jpg)`

## How it works
Each job remembers the last time it ran. On every pass through `loop()`, it checks
`now - lastRun >= interval`. If so, it runs and updates `lastRun = now`.
`delay()` freezes the whole chip, while `millis()` is like a stopwatch that lets many
jobs share one loop.

**Counting a press once:** the button is read every 20 ms. A press is counted only when
`pressed && !lastPressed`, meaning it is pressed now but was not pressed last time.
`lastPressed = pressed;` runs on every check (even when released), so the program always
knows the button's previous state. Holding the button for 3 seconds counts as 1 press, not 150.

## What broke (and what I learned)
- **LED connected backwards.** I thought it was a code bug and nearly went down a rabbit hole.
  It was only the polarity. Lesson: check the hardware before the code.
- `BTN_PIN == LOW` compares the pin *number* (2) with 0, so it is always false.
  I need `digitalRead(BTN_PIN)` to read the pin.
- Without `{ }`, an `if` controls only the next line, so `pressCount++` ran every time.
- Forgot `Serial.` before `print` and `println`.
- Forgot `lastAlive = now;`, so it would print on every loop.

## `delay()` experiment
**FILL IN: add `delay(1000);` to the top of `loop()`. What happened to the LED and to quick taps?**

## Practice questions
A job runs every 500 ms and last ran at 1000 ms.
- At 1230 ms: **no** (1230 − 1000 = 230, which is under 500).
- At 1510 ms: **yes** (510 is 500 or more), and "last ran" becomes 1510.

## Files
- `day01.ino`
