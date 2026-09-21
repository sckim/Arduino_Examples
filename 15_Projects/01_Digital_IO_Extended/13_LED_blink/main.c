/*
 * main.c
 *
 *  Created on: 2020. 4. 27.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>

int cLED = 13;

void setup()
{
#ifdef Arduino
 	pinMode(cLED, OUTPUT);
#else
    DDRB = (1 << PB5);
#endif
}


void loop()
{
#ifdef Arduino
  digitalWrite(cLED, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(cLED, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
#else
  PORTB |= (1<<PB5);
  _delay_ms(200);
  PORTB &= ~(1<<PB5);
  _delay_ms(200);
#endif
}

int main(void)
{
	setup();

	while(1){
		loop();
	}
}
