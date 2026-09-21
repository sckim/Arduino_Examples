#include "Arduino.h"
#include <SPI.h>

const int CS = 10;
int PotWiperVoltage = 1;
int RawVoltage = 0;
float Voltage = 0;

#define MCP41601_add	0x00

#define MCP41010_add	0x11
//C1C0 (5:4)
// 00 : None
// 01 : Write the data
// 10 : Shutdown
// 11 : None

//P1P0 (1:0)
// 00 : Dummy code
// 01 : Potentiometer 0
// 10 : Potentiometer 1
// 11 : Command executed on both Potentiometer


void MCP41010Write(byte value) {
	// Note that the integer value passed to this subroutine
	// is cast to a byte
	digitalWrite(CS, LOW);
	SPI.transfer(MCP41010_add); // This tells the chip to set the pot
	//SPI.transfer(B00000000); // This tells the chip to set the pot
	SPI.transfer(value);     // This tells it the pot position
	digitalWrite(CS, HIGH);
}

void setup() {
	pinMode(CS, OUTPUT);
	Serial.begin(9600);
	SPI.begin();
}

void loop() {

	// move the potentiometer in one direction
	for (int level = 0; level < 255; level++) {
		MCP41010Write(level);
		delay(100);
		RawVoltage = analogRead(PotWiperVoltage);
		Voltage = (RawVoltage * 5.0) / 1024.0;
		Serial.print("Level = ");
		Serial.print(level);
		Serial.print("\t Voltage = ");
		Serial.println(Voltage, 3);
	}
	delay(2000);  // wait a couple seconds

	// Now mover potentiometer in other directions
	for (int level = 255; level > 0; level--) {
		MCP41010Write(level);
		delay(100);
		RawVoltage = analogRead(PotWiperVoltage);
		Voltage = (RawVoltage * 5.0) / 1024.0;
		Serial.print("Level = ");
		Serial.print(level);
		Serial.print("\t Voltage = ");
		Serial.println(Voltage, 3);
	}
	delay(2000);
}

