const int LED_PIN = 8;
const int BTN_PIN = 2;

// Timers for non blocking execution (using millis)
unsigned long lastBlink = 0;
unsigned long lastButton = 0;
unsigned long lastAlive = 0;
unsigned long lastTick = 0;

// Timing intervals in milliseconds
const unsigned long BLINK_EVERY = 500;   // Toggle LED every 0.5s
const unsigned long BUTTON_EVERY = 20;   // Debounce interval
const unsigned long ALIVE_EVERY = 2000;  // Status print every 2s
const unsigned long TICK_EVERY = 5000;   // Periodic tick every 5s

// State variables
bool ledState = false;
bool lastPressed = false;
int pressCount = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP); // Use internal pull-up for the button
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  // 1. Non blocking LED blinker (toggles every 500ms)
  if (now - lastBlink >= BLINK_EVERY) {
    lastBlink = now;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }

  // 2. Button check with software debounce (every 20ms)
  if (now - lastButton >= BUTTON_EVERY) {
    lastButton = now;
    bool pressed = (digitalRead(BTN_PIN) == LOW); // LOW means pressed with INPUT_PULLUP
    
    // Detect rising edge: trigger only on the exact transition from unpressed to pressed
    if (pressed && !lastPressed) {
      pressCount++;
    }
    lastPressed = pressed; // Save state for next check
  }

  // 3. Periodic status printout (every 2 seconds)
  if (now - lastAlive >= ALIVE_EVERY) {
    lastAlive = now;
    Serial.print("Alive, counter : ");
    Serial.println(pressCount);
  }
  
  // 4. Background heartbeat ticker (every 5 seconds)
  if (now - lastTick >= TICK_EVERY) {
    lastTick = now;
    Serial.println("Tick");
  }
}