#include "Arduino.h"
#include "SevSeg.h"

#define trigPin 13
#define echoPin 12

SevSeg sevseg; //Instantiate a seven segment controller object

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {11, 10, 9, 8};
  byte segmentPins[] = {0, 1, 2, 3, 4, 5, 6, 7};

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(100);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  sevseg.setNumber(distance*10, 1);
  sevseg.refreshDisplay(); // Must run repeatedly
}
