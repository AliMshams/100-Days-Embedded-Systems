const int MEASURE_PIN = 2; // Wire from pin 9 to pin 2 to measure frequency
const int LEDPIN = 9;

// Frequency measurement variables
unsigned long lastTime = 0;
unsigned long edgeCount = 0;
unsigned long lastInterruptTime = 0;

void onEdge() {
  // Simple software debounce/edge counter for measuring frequency
  unsigned long now = millis();
  if (now - lastInterruptTime > 1) { // Noise filter
    edgeCount++;
    lastInterruptTime = now;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(MEASURE_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(MEASURE_PIN), onEdge, RISING);

  pinMode(LEDPIN, OUTPUT);

  // Clear Timer1 control registers to start fresh
  TCCR1A = 0;
  TCCR1B = 0;

  // Set ICR1 (TOP value) for 1 kHz frequency with prescaler 8
  ICR1 = 1999; 

  // Set initial duty cycle to 50%
  OCR1A = ICR1 / 2;

  // Set up TCCR1A and TCCR1B for Fast PWM mode 14 with prescaler 8
  TCCR1A = (1 << COM1A1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
}

void loop() {
  // Map potentiometer to initial OCR1A
  OCR1A = map(analogRead(A0), 0, 1023, 0, ICR1);
  
  // Read the potentiometer on A0 and map it to OCR1A (from 0 to ICR1)
  int raw = analogRead(A0);
  OCR1A = map(raw, 0, 1023, 0, ICR1);

  // Print out the measured frequency every 1 second using our Pin 2 counter
  unsigned long now = millis();
  if (now - lastTime >= 1000) {
    lastTime = now;
    Serial.print("Measured Frequency (Hz): ");
    Serial.println(edgeCount);
    edgeCount = 0; // Reset for next second
  }
}