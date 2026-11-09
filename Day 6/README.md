# Day 6: Timer1 PWM by registers
An Arduino project that uncovers what standard analogWrite() hides by configuring Timer1 hardware registers directly, generating a clean 1 kHz square wave, a potentiometer dimmer, and a loopback frequency counter.

##What it does
Bypasses default PWM behavior to generate a precise 1 kHz PWM signal on Pin 9 through direct register manipulation, reads a potentiometer on A0 to adjust LED brightness dynamically, and uses a jumper wire to Pin 2 to count its own pulses and print the measured frequency every second.

##Wiring
Potentiometer: Outer pin one to 5V, outer pin two to GND, middle wiper pin to Analog Pin A0.

Loopback: A single jumper wire connecting Digital Pin 9 directly to Digital Pin 2.

## How it works
Timer1 registers (TCCR1A, TCCR1B, and ICR1 = 1999) are configured directly for Fast PWM Mode 14 with a prescaler of 8, shifting the default frequency away from 490 Hz to avoid audible motor or buzzer whines.

Potentiometer inputs (0 to 1023) are mapped directly to the timer's top limit (0 to 1999) to dynamically change the pulse width and control brightness.

Pin 2 is set up with an external hardware interrupt (attachInterrupt) to catch every rising edge coming from Pin 9 and count them over a one second window.

## Results
The LED dims smoothly across a wide range.

The Serial Monitor reads around 492 to 493 Hz because the 1 kHz pulse speed interacts with millis() timing limits in the software counter, highlighting how low level hardware timing meets software constraints.

## What broke (and what I learned)

Register bit shifting (COM1A1, WGM11, CS11) looks intimidating at first, but breaking it down into setting the speed limit, shifting control panels, and setting the top value makes the hardware logic much clearer.

## Files
`Day_6.ino`
