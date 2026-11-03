const int BTN_PIN = 2;
volatile unsigned int edgeCount = 0;   // needs volatile since it changes inside an ISR
unsigned long lastTime = 0;
const unsigned long CHECKEVERY = 1000; // print every 1 second

// keep track of time for debounce inside the interrupt
volatile unsigned long lastInterruptTime = 0; 
const unsigned long DEBOUNCE_DELAY = 20; // ignore bounces under 20ms

void onEdge() {
  unsigned long interruptTime = millis();
  
  // simple debounce check so one press doesn't count as 5
  if (interruptTime - lastInterruptTime > DEBOUNCE_DELAY) {
    edgeCount++;
    lastInterruptTime = interruptTime;
  }
}

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  
  // trigger on the falling edge (when button goes from HIGH to LOW)
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), onEdge, FALLING); 
}

void loop() {
  unsigned long now = millis();
  
  // every second, print the count and reset
  if (now - lastTime >= CHECKEVERY) {
    lastTime = now;
  
    if (edgeCount > 0) {
      Serial.print("edges: ");
      Serial.println(edgeCount);
      edgeCount = 0; 
    }
  }
}