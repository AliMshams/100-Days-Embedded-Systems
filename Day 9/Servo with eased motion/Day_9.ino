#include <Servo.h>

Servo My_servo;
float currentAngle = 90;  // start in the middle

void setup() {
  My_servo.attach(9);
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(A0);
  float targetAngle = map(raw, 0, 1023, 0, 180);

  // Lerp: instead of jumping to the target , close 5 % of the remaining gap each loop
  // The closer we get the smaller the steps , like chasing something that slows you down
  currentAngle = currentAngle + (targetAngle - currentAngle) * 0.05;

  My_servo.write(currentAngle);
  delay(10);
  Serial.println(currentAngle);
}