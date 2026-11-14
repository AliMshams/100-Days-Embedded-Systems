# Day 09 - Servo with Eased Motion

## What it does
A potentiometer controls where the servo points (0 to 180 degrees).
Turn the pot and the servo follows smoothly instead of snapping straight to the new position.

## The key idea
Every loop the servo closes 5% of the remaining gap to the target angle:

    currentAngle = currentAngle + (targetAngle - currentAngle) * 0.05;

When it is far away the steps are big. When it is close they get tiny.
That is what gives it the smooth feel without any math library.

If you replace that line with My_servo.write(targetAngle) directly, 
the servo teleports. The difference is obvious immediately.

## Wiring
Servo signal - D9
Pot wiper - A0
Servo and pot power - 5V and GND

## What I learned
- map() converts the raw potentiometer reading into a 0 to 180 degree range
- Lerp (linear interpolation) makes any value chase a target gradually,
  useful for motors, animations, anything that should not snap instantly
- A small delay(10) gives the servo time to physically move between updates

## Files
Day_9.ino
