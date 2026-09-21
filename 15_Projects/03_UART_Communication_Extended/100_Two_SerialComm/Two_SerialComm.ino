#include <Arduino.h>
#include <SPI.h>

void setup() {
  // Initialize Serial (USB)
  Serial.begin(115200);
  while (!Serial) {
    ;  // Wait for Serial to be ready
  }

  // Initialize Serial1
  Serial1.begin(115200);

  delay(1000);
  Serial.println("Serial and Serial1 Communication Example");
}

void loop() {
  char str[80];

  // Read data from Serial and send it to Serial1
  while (Serial.available() > 0) {
    int incomingByte = Serial.read();
    if (incomingByte != -1) {
      Serial1.write(incomingByte);
    }
  }

  // Read data from Serial1 and send it to Serial
  while (Serial1.available() > 0) {
    int incomingByte = Serial1.read();
    if (incomingByte != -1) {
      sprintf(str, "Serial1 input = 0x%0X\r\n", incomingByte);
      Serial.print(str);
    }
  }
}
