const int PIN_A = 2;
const int PIN_B = 3;
const unsigned long EVERY_PRINT = 200;
unsigned long lastPrint = 0;
unsigned long lastPrintedPos = 0;

// look up table for decoding the encoder steps
const int8_t TABLE[16] = { 0,-1, 1, 0,
                           1, 0, 0,-1,
                          -1, 0, 0, 1,
                           0, 1,-1, 0 };

volatile long position = 0;
volatile uint8_t prevState = 0;

void onChange() {
  // read both pins to get the current state
  uint8_t currentState = (digitalRead(PIN_A) << 1) | digitalRead(PIN_B);  
  
  // figure out the index based on old state and new state
  uint8_t index = (prevState << 2) | currentState;
  
  // update position and save current state for next time
  position += TABLE[index];
  prevState = currentState;
}

void setup() {
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  Serial.begin(9600);
  
  // get the starting state before turning on interrupts
  prevState = (digitalRead(PIN_A) << 1) | digitalRead(PIN_B);
  
  // listen for changes on both pins
  attachInterrupt(digitalPinToInterrupt(PIN_A), onChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_B), onChange, CHANGE);
}

void loop() {
  unsigned long now = millis();
  
  // check if it's time to print
  if (now - lastPrint > EVERY_PRINT) {
    lastPrint = now;

    // only print if the position actually changed
    if (lastPrintedPos != position) {
      Serial.println(position / 2);
      lastPrintedPos = position;
    }
  }
}