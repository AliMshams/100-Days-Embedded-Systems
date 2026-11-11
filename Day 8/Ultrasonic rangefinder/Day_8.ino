const float R_FIXED = 10000.0;   
const float R0 = 10000.0;        
const float T0 = 298.15;           //Variables from day 7
const float BETA = 3950.0;       
float raw = 0;
unsigned long lastPrint = 0;
const unsigned long EVERY_PRINT = 500;

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const int NUM_SAMPLES = 5;

float readDistanceOnce(float speedCmPerUs) {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  
  float distance = duration * speedCmPerUs / 2.0;
  return distance;
}

// Thermistor code from Day 7
float getTempC() { 
  unsigned long sum = 0;
  for (int i = 0; i < 64; i++) {
    sum = sum + analogRead(A0);
  }
  raw = sum / 64.0;

  float R = R_FIXED * raw / (1023.0 - raw);
  float T = 1.0 / ((1.0 / T0) + (1.0 / BETA) * log(R / R0));
  float Celsius = T - 273.15;
  return Celsius;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  float tempC = getTempC();   

  // Adjust speed of sound based on real-time temperature (m/s converted to cm/µs)
  float speedCmPerUs = (331.3 + 0.606 * tempC) / 10000.0;

  float samples[NUM_SAMPLES];
  for (int i = 0; i < NUM_SAMPLES; i++) {
    samples[i] = readDistanceOnce(speedCmPerUs);
    delay(10);
  }

  // Bubble sort to filter out noise spikes
  for (int i = 0; i < NUM_SAMPLES - 1; i++) {
    bool swapped = false;
    for (int j = 0; j < NUM_SAMPLES - i - 1; j++) {
      if (samples[j] > samples[j + 1]) {
        float temp = samples[j];
        samples[j] = samples[j + 1];
        samples[j + 1] = temp;
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }

  // Print the median value (middle element)
  Serial.print("Distance: ");
  Serial.print(samples[2]);
  Serial.println(" cm");
  }