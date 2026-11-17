const int LED_PIN = 9;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

// XOR every character together — the result is the checksum.
// If even one character changed in transit, the number comes out different.
byte calcChecksum(String s) {
  byte x = 0;
  for (int i = 0; i < s.length(); i++) {
    x ^= s[i];
  }
  return x;
}

void handleCommand(String raw) {
  // Split at '*' to separate the command from its checksum
  int starIndex = raw.indexOf('*');
  if (starIndex == -1) {
    Serial.println("ERR");
    return;
  }

  String command = raw.substring(0, starIndex);
  String checksumStr = raw.substring(starIndex + 1);

  // Reject the command if the checksum does not match
  byte expected = calcChecksum(command);
  int received = checksumStr.toInt();
  if (expected != received) {
    Serial.println("ERR");
    return;
  }

  // Parse and execute — substring(4) strips the command name and space,
  // leaving just the value
  if (command.startsWith("LED")) {
    digitalWrite(LED_PIN, command.substring(4).toInt());
  } else if (command.startsWith("PWM")) {
    analogWrite(LED_PIN, command.substring(4).toInt());
  } else if (command.startsWith("READ A0")) {
    Serial.print("Potentiometer value: ");
    Serial.println(analogRead(A0));
  } else {
    Serial.println("ERR");
    return;
  }

  Serial.println("OK");
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();
    handleCommand(line);
  }
}