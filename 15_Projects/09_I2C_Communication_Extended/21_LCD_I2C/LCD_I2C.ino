#include "Arduino.h"
#include "LiquidCrystal_I2C.h"

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// Proteus 0x20
// real 0x27
LiquidCrystal_I2C lcd(0x20, 16, 2);

void setup()
{
	// initialize the LCD
	lcd.begin();
}

void loop()
{
	bool blinking = true;
	lcd.cursor();

	while (1) {
		if (blinking) {
			lcd.clear();
			lcd.print("No cursor blink");
			lcd.noBlink();
			blinking = false;
		} else {
			lcd.clear();
			lcd.print("Cursor blink");
			lcd.blink();
			blinking = true;
		}
		delay(1000);
	}
}
