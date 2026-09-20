#include <EEPROM.h>

byte FreqIndex=6;
byte AmpIndex=7;
byte irunning=8;

int	add=0;

void load_data(void) {
	add = 10;
	FreqIndex = EEPROM.read(add++);
	delay(100);
	AmpIndex = EEPROM.read(add++);
	//	VoltageIndex = EEPROM.read(2);
	delay(100);
	irunning = EEPROM.read(add++);

	Serial.println("Load data");
	Serial.println(FreqIndex);
	Serial.println(AmpIndex);
	Serial.println(irunning);
}

void save_data(void) {
	add = 10;
	EEPROM.write(add++, FreqIndex);
	delay(100);
	EEPROM.write(add++, AmpIndex);
	delay(100);
	//	EEPROM.write(2, VoltageIndex);
	EEPROM.write(add++, irunning);
	delay(100);

	Serial.println("Save data");
	Serial.println(FreqIndex);
	Serial.println(AmpIndex);
	Serial.println(irunning);
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  Serial.begin(9600);
  save_data();
  load_data();
}

// the loop function runs over and over again forever
void loop() {

}
