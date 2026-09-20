#include <util/delay.h>

void setup() {
  // put your setup code here, to run once:
  DDRB = 0xFF;
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB = 0xFF;
  _delay_ms(1000);
  PORTB = 0x00;
  _delay_ms(1000);
}
