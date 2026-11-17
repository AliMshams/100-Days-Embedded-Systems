# Day 11: Serial Command Protocol

## What it does
You type a command into Serial Monitor and the Arduino reads it, 
verifies it is not corrupted, and acts on it.

Supported commands:
- LED 1*XX  — turn the LED on or off (1 or 0)
- PWM 128*XX — set LED brightness (0 to 255)
- READ A0*XX — read and print the analog pin value

Replace XX with the correct checksum (XOR of all characters before the asterisk).
The Arduino replies OK if everything worked, or ERR if something was wrong.

## The checksum idea
Think of it like a secret code. Before sending a command, you calculate
a number by XOR-ing every character together. The Arduino does the same
calculation when it receives the message. If the numbers match, the message
arrived clean. If not, something got flipped somewhere and the command is rejected.

This matters a lot in real systems. A robotic arm in a factory, a drone flight
controller, a CNC machine — a single flipped bit in the wrong command could
cause serious damage. The checksum is a simple way to catch corrupted messages
before they cause problems.

## What I learned
- String.startsWith() to identify which command arrived
- String.substring() to slice out just the part you need, like stripping
  the command name to get the value that follows it
- String.toInt() to convert that slice into a usable number
- XOR checksums and why they are used as a safety measure in real protocols
- How to structure a simple text-based command parser

## Wiring
LED - Pin 9 (with 220 ohm resistor to GND)
Pot (optional) - A0, used by the READ A0 command

## Files
Day_11.ino
