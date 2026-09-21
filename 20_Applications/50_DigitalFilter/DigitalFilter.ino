#include <Arduino.h>
#include <Adafruit_TinyUSB.h> // for Serial

// FIR filter coefficients (replace these with your actual coefficients)
const int numtaps = 30;
const float fir_coeff[numtaps] = {
  0.00141791,  0.00065991, -0.00311351,  0.00148353,  0.00592811, -0.00877933,
 -0.00481508,  0.02181708, -0.00927905, -0.03318823,  0.04558239,  0.02451176,
 -0.11869931,  0.06386679,  0.51260703,  0.51260703,  0.06386679, -0.11869931,
  0.02451176,  0.04558239, -0.03318823, -0.00927905,  0.02181708, -0.00481508,
 -0.00877933,  0.00592811,  0.00148353, -0.00311351,  0.00065991,  0.00141791};

// Buffer to hold input samples
float buffer[numtaps] = {0};

// Function to apply the FIR filter
float applyFIR(float input) {
  // Shift buffer values
  for (int i = numtaps - 1; i > 0; i--) {
    buffer[i] = buffer[i - 1];
  }
  // Add new input value to the buffer
  buffer[0] = input;

  // Apply the filter
  float output = 0;
  for (int i = 0; i < numtaps; i++) {
    output += fir_coeff[i] * buffer[i];
  }

  return output;
}

void setup() {
  Serial.begin(1000000);
  while (!Serial) {
    delay(10); // Wait for Serial to initialize
  }
  Serial.println("FIR Filter Example");
}

void loop() {
  // Read the analog input from A0
  int analogValue = analogRead(A1);
  
  // Convert to voltage
  float voltage = analogValue * (5.0 / 1023.0);

  // Apply the FIR filter
  float filteredValue = applyFIR(voltage);

  Serial.print(voltage);
  Serial.print(", ");
  // Print the filtered value
  Serial.println(filteredValue);

  // Sample at 100Hz
  delay(10);
}