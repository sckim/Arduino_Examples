volatile byte changed = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), toggle, CHANGE);
}

void loop() {
  if (changed == 1) {
    // toggle() has been called from interrupts!

    // Reset changed to 0
    changed = 0;

    // Blink LED for 200 ms
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void toggle() {
  changed = 1;
}

