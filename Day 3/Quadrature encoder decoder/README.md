# Day 3: Rotary encoder

Today I wanted to figure out how a rotary encoder works. Instead of just pressing a button, this gives you rotation and a click.

## What I learned

* **How encoders work:** They use two pins (A and B) that go high and low in a specific sequence depending on which way you turn the knob.
* **Reading the pins:** I had to check the state changes to figure out if it was turning clockwise or counter-clockwise.

## Files

* `Day_3.ino`

## Wiring

* Connect the encoder's ground pin to GND.
* Connect the power pin to 5V.
* Connect pin A and pin B to digital pins on the board.
* Connect the switch pin if you want to use the push button.
