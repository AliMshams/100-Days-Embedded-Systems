const float R_FIXED = 10000.0;   // fixed resistor value
const float R0 = 10000.0;        // thermistor resistance at 25°C
const float T0 = 298.15;         // 25°C in Kelvin
const float BETA = 3950.0;       // beta coefficient
float raw = 0;

unsigned long lastPrint = 0;
const unsigned long EVERY_PRINT = 500;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Average 64 readings to cut out electrical noise
  unsigned long sum = 0;
  for (int i = 0; i < 64; i++) {
    sum = sum + analogRead(A0);
  }
  raw = sum / 64.0;

  // Calculate thermistor resistance using the voltage divider ratio
  float R = R_FIXED * raw / (1023.0 - raw);

  // Beta equation to find temperature in Kelvin
  float T = 1.0 / ((1.0 / T0) + (1.0 / BETA) * log(R / R0));

  // Print temperature every 500ms without blocking code execution
  unsigned long now = millis();
  if (now - lastPrint > EVERY_PRINT) {
    lastPrint = now;
    float Celsius = T - 273.15;  // * This 273.15 subtraction is to turn Kelvin to Celsius
    Serial.print("Temperature in Celsius: ");
    Serial.println(Celsius, 1);
  }
}