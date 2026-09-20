#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the built-in LED pin as an output
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on (HIGH is the voltage level)
  delay(1000); // Wait for a second
  digitalWrite(LED_BUILTIN, LOW);
  // Turn the LED off by making the voltage LOW
  delay(1000); // Wait for a second  
}
