#include "Arduino.h"

char LED_pins[] = {8, 9, 2, 3, 4, 5, 6, 7};
int curVoltage = 0;
int preVoltage = 0;

void setup()
{
  for(int i=0; i<sizeof(LED_pins)/sizeof(int); i++ ){
	  pinMode(LED_pins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop()
{
  int temp = analogRead(A0);

  if( curVoltage!=preVoltage ){
	  curVoltage = map(temp, 0, 1023, 0, 8);

	  Serial.println("Voltage = " + String(curVoltage));
    for(int i=0; i<curVoltage; i++)
		digitalWrite(LED_pins[i], HIGH);
    for(int i=curVoltage; i<8; i++)
      	digitalWrite(LED_pins[i], LOW);

    preVoltage = curVoltage;
  }
}
