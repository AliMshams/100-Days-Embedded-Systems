// Wiring: source + -> 10k -> A0 -> 5.1k -> GND, and source - to Arduino GND
// Safe input: 12 V or less

float average = 0;                          // average of 64 raw readings (0 to 1023)
unsigned long lastPrint = 0;                // last time we printed (ms)
const unsigned long EVERY_PRINT = 500;      // print every 500 ms

void setup() {
  Serial.begin(9600);                       // start the Serial Monitor at 9600 baud
}

void loop() {
  unsigned long sum = 0;                    // restart the total every loop (unsigned long: 64 x 1023 doesn't fit in an int)

  for (int i = 0; i < 64; i++) {            // take 64 readings
    sum = sum + analogRead(A0);             // add each raw reading to the total
  }
  average = sum / 64.0;                     // average (64.0 so decimals are kept)

  float volts = average * 5.0 / 1023.0;     // Vout: the voltage at the pin (0 to 5 V)
  float value = volts * ((10.0 + 5.1) / 5.1);  // Vin: undo the divider, Vin = Vout x (R1 + R2) / R2

  unsigned long now = millis();             // current time in ms
  if (now - lastPrint > EVERY_PRINT) {      // has 500 ms passed? (same pattern as Day 1)
    Serial.println(value, 2);               // print the real voltage with 2 decimals
    lastPrint = now;                        // remember when we printed
  }
}