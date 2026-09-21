void setup() {
  // put your setup code here, to run once:
  //DDRB |= (1<<5);
  DDRB = DDRB | (1<<5);
  //DDRB = DDRB | (0B00100000);
}

void loop() {
  // put your main code here, to run repeatedly:
  PORTB = PORTB | (1<<5);
  _delay_ms(100);
  PORTB = PORTB & ~(1<<5);
  //PORTB = PORTB & ~(0B00100000);
  //PORTB = PORTB & (0B11011111);
  _delay_ms(100);
}
