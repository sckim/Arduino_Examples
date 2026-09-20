/*
 KeyPressed on PIN1
 by Mischianti Renzo <http://www.mischianti.org>
 https://www.mischianti.org/2019/01/02/pcf8575-i2c-digital-i-o-expander-fast-easy-usage/
*/

#include "PCF8575.h"

// Set i2c address
PCF8575 pcf8575_A(0x22);
PCF8575 pcf8575_B(0x23);

void setup()
{
	Serial.begin(115200);

	for(int i=0; i<16; i++) {
		pcf8575_A.pinMode(i, INPUT);
		pcf8575_B.pinMode(i, INPUT);
	}

	pcf8575_A.begin();
	pcf8575_B.begin();
}

void loop()
{
	for( int i=0; i<16; i++) {
		uint8_t val = pcf8575_A.digitalRead(i);
		if (val==HIGH)
			Serial.print("1");
		else
			Serial.print("0");
	}
	Serial.print("     ");
	for( int i=0; i<16; i++) {
			uint8_t val = pcf8575_B.digitalRead(i);
			if (val==HIGH)
				Serial.print("1");
			else
				Serial.print("0");
	}
	Serial.println("");
	delay(1000);
}
