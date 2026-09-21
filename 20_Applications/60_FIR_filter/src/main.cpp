#include <Arduino.h>

// FIR filter coefficients (replace these with your actual coefficients)
const int numtaps = 6;
const float fir_coeff[numtaps] = {0.04658291, 0.23346962, 0.46791587, 0.23346962, 0.04658291};

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
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // Wait for Serial to initialize
  }
  Serial.println("FIR Filter Example");
}

void loop() {
  // Read the analog input from A0
  int analogValue = analogRead(A0);
  
  // Convert to voltage
  float voltage = analogValue * (5.0 / 1023.0);

  // Apply the FIR filter
  float filteredValue = applyFIR(voltage);

  // Print the filtered value
  Serial.println(filteredValue);

  // Sample at 100Hz
  delay(10);
}