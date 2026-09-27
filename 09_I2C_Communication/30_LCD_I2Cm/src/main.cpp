#include <Arduino.h>
#include "Arduino.h"
#include <LiquidCrystal_PCF8574.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
	// initialize the LCD
	lcd.begin(16, 2);

	// Turn on the blacklight and print a message.
	lcd.clear();
	lcd.setBacklight(128);
	lcd.print("Hello, world!");
}

void loop()
{
	// Do nothing here...
}
